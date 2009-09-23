%{
#include "xhp.hpp"
#define YY_USER_ACTION \
  if (!yyg->yy_more_len) \
    yyextra->first_lineno = yyextra->lineno;
#define tok(t) \
  if (yyextra->has_doc_block) { \
    *yylval = yyextra->doc_block + code_rope(yytext, yyextra->first_lineno, yyextra->lineno - yyextra->first_lineno); \
    yyextra->has_doc_block = false; \
  } else { \
    *yylval = code_rope(yytext, yyextra->first_lineno, yyextra->lineno - yyextra->first_lineno); \
  } \
  return yy_token(t, yyg)
#ifdef DEBUG
  static void yy_log_token(int tok);
  #define tokt(t) *yylval = t; BEGIN(XHP_AFTER_ENT); yy_log_token(T_XHP_TEXT); return yyextra->last_token = T_XHP_TEXT;
#else
  #define tokt(t) *yylval = t; BEGIN(XHP_AFTER_ENT); return yyextra->last_token = T_XHP_TEXT;
#endif
#define YY_USER_INIT \
  if (yyextra->insert_token) { \
    yyg->yy_init = 0; \
    int ft = yyextra->insert_token; \
    yyextra->insert_token = 0; \
    return yy_token(ft, yyg); \
  }
#define push_state(s) xhp_new_push_state(s, yyg)
#define pop_state() xhp_new_pop_state(yyg)
#define set_state(s) xhp_set_state(s, yyg)
#define last_curly_token() (yyextra->curly_stack.empty() ? 0 : yyextra->curly_stack.top())
#define last_token() yyextra->last_token

using namespace std;

const char* yytokname(int tok);
static int yy_token(int tok, struct yyguts_t* yyg);
static void yy_scan_newlines(const char* text, struct yyguts_t* yyg);

static bool utf8ize(uint32_t v, char* buf /* [5] */) {
  if (v <= 0x7f) { // 0xxxxxxx
    buf[0] = v;
    buf[1] = 0;
  } else if (v <= 0x7ff) { // 110yyyxx 10xxxxxx
    buf[0] = 0xc0 | (v >> 6);
    buf[1] = 0x80 | (v & 0x3f);
    buf[2] = 0;
  } else if (v <= 0xffff) { // 1110yyyy 10yyyyxx 10xxxxxx
    buf[0] = 0xe0 | (v >> 12);
    buf[1] = 0x80 | ((v >> 6) & 0x3f);
    buf[2] = 0x80 | (v & 0x3f);
    buf[3] = 0;
  } else if (v <= 0x1fffff) { // 11110zzz 10zzyyyy 10yyyyxx 10xxxxxx
    buf[0] = 0xf0 | (v >> 18);
    buf[1] = 0x80 | ((v >> 12) & 0x3f);
    buf[2] = 0x80 | ((v >> 6) & 0x3f);
    buf[3] = 0x80 | (v & 0x3f);
    buf[4] = 0;
  } else {
    return false;
  }
  return true;
}

%}

%option prefix="xhp"
%option reentrant
%option case-insensitive
%option noyywrap nodefault
%option stack
%option bison-bridge
%option 8bit

 /* I think an interactive scanner is required because of the bison state 
  * pushing we do. I'm putting an explicit interactive declaration here in case
  * someone tries adding -CF or whatever to the make flags. */
%option interactive

%s PHP
%s PHP_COMMENT
%s PHP_EOL_COMMENT
%s PHP_DOC_COMMENT
%s PHP_HEREDOC_START
%s PHP_HEREDOC_NSTART
%s PHP_HEREDOC_NEWLINE
%s PHP_HEREDOC_DATA
%s PHP_NO_RESERVED_WORDS
%s PHP_NO_RESERVED_WORDS_STATEMENT
%s XHP_LABEL
%s XHP_LABEL_WHITESPACE
%s XHP_ATTRS
%s XHP_ATTR_VAL
%s XHP_AFTER_ENT
%s XHP_CHILD
%s XHP_CHILD_START
%s XHP_INVALID_ENTITY
%s XHP_CHILDREN_DECL

LNUM [0-9]+
DNUM ([0-9]*"."[0-9]+)|([0-9]+"."[0-9]*)
EXPONENT_DNUM (({LNUM}|{DNUM})[eE][+-]?{LNUM})
HNUM "0x"[0-9a-fA-F]+

LABEL [a-zA-Z_\x7f-\xff][a-zA-Z0-9_\x7f-\xff]*
BYTE (.|\n)

WHITESPACE [ \n\r\t]+
TABS_AND_SPACES [ \t]*
NEWLINE ("\r\n"|"\n"|"\r")

%%

 /* Open / close PHP + inline HTML */
<INITIAL>{
  "<?php"([ \t]|{NEWLINE}) {
    yy_scan_newlines(yytext + 5, yyg);
    tok(T_OPEN_TAG);
  }
  "<?" {
    if (yyextra->short_tags) {
      tok(T_OPEN_TAG);
    } else {
      tok(T_INLINE_HTML);
    }
  }
  "<?=" {
    if (yyextra->short_tags) {
      tok(T_OPEN_TAG_WITH_ECHO);
    } else {
      tok(T_INLINE_HTML);
    }
  }
  "<%" {
    if (yyextra->asp_tags) {
      tok(T_OPEN_TAG);
    } else {
      tok(T_INLINE_HTML);
    }
  }
  "<%=" {
    if (yyextra->asp_tags) {
      tok(T_OPEN_TAG_WITH_ECHO);
    } else {
      tok(T_INLINE_HTML);
    }
  }
  "<"|[^<]* {
    yy_scan_newlines(yytext, yyg);
    tok(T_INLINE_HTML);
  }
}
<PHP,PHP_NO_RESERVED_WORDS,PHP_NO_RESERVED_WORDS_STATEMENT>{
  ("?>"|"</script"{WHITESPACE}*">"){NEWLINE}? {
    yy_scan_newlines(yytext + 3, yyg);
    tok(T_CLOSE_TAG);
  }
  "%>" {
    if (yyextra->asp_tags) {
      tok(T_CLOSE_TAG);
    } else {
      yyless(1);
      tok(yytext[0]);
    }
  }
}

 /* Comments and whitespace */
<PHP,PHP_NO_RESERVED_WORDS,PHP_NO_RESERVED_WORDS_STATEMENT>{
  "#"|"//" {
    push_state(PHP_EOL_COMMENT);
    yymore();
  }
  "/**"{WHITESPACE} {
    yy_scan_newlines(yytext + 3, yyg);
    push_state(PHP_DOC_COMMENT);
    yymore();
  }
  "/*" {
    push_state(PHP_COMMENT);
    yymore();
  }
  {WHITESPACE}+ yy_scan_newlines(yytext, yyg);
}
<PHP_EOL_COMMENT>{
  {NEWLINE} {
    ++yyextra->lineno;
    pop_state();
  }
  [^\r\n?]+ yymore();
  "?>" yyless(2);
  . yymore();
}
<PHP_DOC_COMMENT,PHP_COMMENT>{
  {NEWLINE} {
    ++yyextra->lineno;
    yymore();
  }
  [^*\r\n]+|"*" yymore();
}
<PHP_DOC_COMMENT>"*/" {
  yyextra->doc_block = code_rope(yytext, yyextra->first_lineno, yyextra->lineno - yyextra->first_lineno);
  yyextra->has_doc_block = true;
  pop_state();
}
<PHP_COMMENT>"*/" pop_state();

 /* Reserved words */
<PHP>{
  include tok(T_INCLUDE);
  include_once tok(T_INCLUDE_ONCE);
  eval tok(T_EVAL);
  require tok(T_REQUIRE);
  require_once tok(T_REQUIRE_ONCE);
  or tok(T_LOGICAL_OR);
  xor tok(T_LOGICAL_XOR);
  and tok(T_LOGICAL_AND);
  print tok(T_PRINT);
  instanceof tok(T_INSTANCEOF);
  new tok(T_NEW);
  clone tok(T_CLONE);
  exit tok(T_EXIT);
  if tok(T_IF);
  elseif tok(T_ELSEIF);
  else tok(T_ELSE);
  endif tok(T_ENDIF);
  echo tok(T_ECHO);
  do tok(T_DO);
  while tok(T_WHILE);
  endwhile tok(T_ENDWHILE);
  for tok(T_FOR);
  endfor tok(T_ENDFOR);
  foreach tok(T_FOREACH);
  endforeach tok(T_ENDFOREACH);
  declare tok(T_DECLARE);
  enddeclare tok(T_ENDDECLARE);
  as tok(T_AS);
  switch tok(T_SWITCH);
  endswitch tok(T_ENDSWITCH);
  case tok(T_CASE);
  default tok(T_DEFAULT);
  break tok(T_BREAK);
  continue tok(T_CONTINUE);
  goto tok(T_GOTO);
  function tok(T_FUNCTION);
  const tok(T_CONST);
  return tok(T_RETURN);
  try tok(T_TRY);
  catch tok(T_CATCH);
  throw tok(T_THROW);
  use tok(T_USE);
  global tok(T_GLOBAL);
  static tok(T_STATIC);
  abstract tok(T_ABSTRACT);
  final tok(T_FINAL);
  private tok(T_PRIVATE);
  protected tok(T_PROTECTED);
  public tok(T_PUBLIC);
  var tok(T_VAR);
  unset tok(T_UNSET);
  isset tok(T_ISSET);
  empty tok(T_EMPTY);
  __halt_compiler tok(T_HALT_COMPILER);
  class tok(T_CLASS);
  interface tok(T_INTERFACE);
  extends tok(T_EXTENDS);
  implements tok(T_IMPLEMENTS);
  list tok(T_LIST);
  array tok(T_ARRAY);
  __class__ tok(T_CLASS_C);
  __method__ tok(T_METHOD_C);
  __function__ tok(T_FUNC_C);
  __line__ tok(T_LINE);
  __file__ tok(T_FILE);
  namespace tok(T_NAMESPACE);
  __namespace__ tok(T_NS_C);
  __dir__ tok(T_DIR);
  element tok(T_XHP_ELEMENT);
  attribute {
    tok(T_STRING);
  }
  children {
    if ((last_token() == '{' || last_token() == '}' || last_token() == ';') &&
        (yyextra->class_statement_list)) {
      push_state(PHP_NO_RESERVED_WORDS_STATEMENT);
      tok(T_XHP_CHILDREN);
    } else {
      tok(T_STRING);
    }
  }
}

 /* Operators */
<PHP,PHP_NO_RESERVED_WORDS,PHP_NO_RESERVED_WORDS_STATEMENT>{
  "+=" tok(T_PLUS_EQUAL);
  "-=" tok(T_MINUS_EQUAL);
  "*=" tok(T_MUL_EQUAL);
  "/=" tok(T_DIV_EQUAL);
  ".=" tok(T_CONCAT_EQUAL);
  "%=" tok(T_MOD_EQUAL);
  "&=" tok(T_AND_EQUAL);
  "|=" tok(T_OR_EQUAL);
  "^=" tok(T_XOR_EQUAL);
  "<<=" tok(T_SL_EQUAL);
  ">>=" tok(T_SR_EQUAL);
  "||" tok(T_BOOLEAN_OR);
  "&&" tok(T_BOOLEAN_AND);
  "==" tok(T_IS_EQUAL);
  "!="|"<>" tok(T_IS_NOT_EQUAL);
  "===" tok(T_IS_IDENTICAL);
  "!==" tok(T_IS_NOT_IDENTICAL);
  "<=" tok(T_IS_SMALLER_OR_EQUAL);
  ">=" tok(T_IS_GREATER_OR_EQUAL);
  "<<" tok(T_SL);
  ">>" tok(T_SR);
  "++" tok(T_INC);
  "--" tok(T_DEC);
  "->" tok(T_OBJECT_OPERATOR);
  "=>" tok(T_DOUBLE_ARROW);
  "::" tok(T_PAAMAYIM_NEKUDOTAYIM);
  "\\" tok(T_NS_SEPARATOR);
}

 /* Casts */
<PHP,PHP_NO_RESERVED_WORDS,PHP_NO_RESERVED_WORDS_STATEMENT>{
  "("{TABS_AND_SPACES}(int|integer){TABS_AND_SPACES}")" tok(T_INT_CAST);
  "("{TABS_AND_SPACES}(real|double|float){TABS_AND_SPACES}")" tok(T_DOUBLE_CAST);
  "("{TABS_AND_SPACES}string{TABS_AND_SPACES}")" tok(T_STRING_CAST);
  "("{TABS_AND_SPACES}unicode{TABS_AND_SPACES}")" tok(T_UNICODE_CAST);
  "("{TABS_AND_SPACES}binary{TABS_AND_SPACES}")" tok(T_BINARY_CAST);
  "("{TABS_AND_SPACES}array{TABS_AND_SPACES}")" tok(T_ARRAY_CAST);
  "("{TABS_AND_SPACES}object{TABS_AND_SPACES}")" tok(T_OBJECT_CAST);
  "("{TABS_AND_SPACES}(bool|boolean){TABS_AND_SPACES}")" tok(T_BOOL_CAST);
  "("{TABS_AND_SPACES}unset{TABS_AND_SPACES}")" tok(T_UNSET_CAST);
}

 /* Scalars (parsing these doesn't really matter since we just pass them through literally) */
<PHP,PHP_NO_RESERVED_WORDS,PHP_NO_RESERVED_WORDS_STATEMENT>{
  {LNUM}|{HNUM} tok(T_LNUMBER);
  {DNUM}|{EXPONENT_DNUM} tok(T_DNUMBER);
  {LABEL} tok(T_STRING);
  "$"{LABEL} tok(T_VARIABLE);
  b?'(\\.|\\\n|[^\\']+)*'|b?\"(\\.|\\\n|[^\\\"]+)*\" {
    yy_scan_newlines(yytext, yyg);
    tok(T_CONSTANT_ENCAPSED_STRING);
  }
  `[^`]*` {
    yy_scan_newlines(yytext, yyg);
    tok(T_BACKTICKS_EXPR);
  }
}

 /* (HERE|NOW)DOC's */
<PHP,PHP_NO_RESERVED_WORDS,PHP_NO_RESERVED_WORDS_STATEMENT>b?"<<<"{TABS_AND_SPACES} {
  push_state(PHP_HEREDOC_START);
  yyextra->heredoc_yyleng = yyleng;
  yymore();
}
<PHP_HEREDOC_START>{
  "'"{LABEL}"'"|\"{LABEL}\" {
    yyextra->heredoc_label = string(yytext + yyextra->heredoc_yyleng, yyleng - 1);
    set_state(PHP_HEREDOC_NSTART);
    yyextra->heredoc_yyleng = yyleng;
    yymore();
  }
  {LABEL} {
    yyextra->heredoc_label = string(yytext + yyextra->heredoc_yyleng);
    set_state(PHP_HEREDOC_NSTART);
    yyextra->heredoc_yyleng = yyleng;
    yymore();
  }
}
<PHP_HEREDOC_NSTART>{NEWLINE} {
  ++yyextra->lineno;
  yyextra->heredoc_data = yytext + yyleng;
  set_state(PHP_HEREDOC_DATA);
  yymore();
}
<PHP_HEREDOC_DATA>{
  [^\r\n]*{NEWLINE} {
    ++yyextra->lineno;
    set_state(PHP_HEREDOC_NEWLINE);
    yyextra->heredoc_yyleng = yyleng;
    yymore();
  }
}
<PHP_HEREDOC_NEWLINE>{
  {LABEL};?{NEWLINE} {
    if (strncmp(yyextra->heredoc_label.c_str(), yytext + yyextra->heredoc_yyleng, yyextra->heredoc_label.size()) == 0) {
      switch (yytext[yyextra->heredoc_yyleng + yyextra->heredoc_label.size()]) {
        case ';': case '\n': case '\r':
          yyless(yyleng - (yyleng - yyextra->heredoc_yyleng - yyextra->heredoc_label.size()));
          pop_state();
          tok(T_HEREDOC);
      }
    }
    ++yyextra->lineno;
    yyextra->heredoc_yyleng = yyleng;
  }
  [^\r\n]+ {
    set_state(PHP_HEREDOC_DATA);
    yyextra->heredoc_yyleng = yyleng;
    yymore();
  }
  {NEWLINE} {
    ++yyextra->lineno;
    yyextra->heredoc_yyleng = yyleng;
    yymore();
  }
}

 /* XHP */
<XHP_LABEL_WHITESPACE>{
  {WHITESPACE}+ yy_scan_newlines(yytext, yyg);
}
<XHP_LABEL,XHP_LABEL_WHITESPACE>{
  ":"|"-" tok(yytext[0]);
  {WHITESPACE} {
    yy_scan_newlines(yytext, yyg);
    pop_state();
    tok(T_XHP_WHITESPACE);
  }
  {LABEL} tok(T_STRING);
  . {
    pop_state();
    tok(yytext[0]);
  }
}

<XHP_ATTRS>{
  "="|"/"|">" tok(yytext[0]);
  {WHITESPACE}+ yy_scan_newlines(yytext, yyg);
  {LABEL} tok(T_STRING);
}

<XHP_ATTR_VAL>{
  [^&'\\"]+ tok(T_XHP_TEXT);
  \" {
    pop_state();
    tok('"');
  }
}

<XHP_CHILD_START>{
  {WHITESPACE}+ {
    /* ignore whitespace at the start */
    yy_scan_newlines(yytext, yyg);
    unput(' ');
    set_state(XHP_CHILD);
  }
  . {
    yyless(0);
    set_state(XHP_CHILD);
  }
}

<XHP_CHILD,XHP_AFTER_ENT,XHP_ATTR_VAL>{
  &amp; tokt("&");
  &quot; tokt("\"");
  &lt; tokt("<")
  &gt; tokt(">");
  &middot; tokt("\u00B7");
  &laquo; tokt("\u00AB");
  &raquo; tokt("\u00BB");
  &lsaquo; tokt("\u2039");
  &rsaquo; tokt("\u203A");
  &lsquo; tokt("\u2018");
  &rsquo; tokt("\u2019");
  &ldquo; tokt("\u201C");
  &rdquo; tokt("\u201D");
  &hellip; tokt("\u2026");
  &mdash; tokt("\u2014");
  &hearts; tokt("\u2665");
  &cloud; tokt("\u2601");
  &umbrella; tokt("\u2602");
  &snowman; tokt("\u2603");
  &snowflake; tokt("\u2745");
  &comet; tokt("\u2604");
  &thunderstorm; tokt("\u2608");
  &whiteking; tokt("\u2654");
  &whitequeen; tokt("\u2655");
  &whiterook; tokt("\u2656");
  &whitebishop; tokt("\u2657");
  &whiteknight; tokt("\u2658");
  &whitepawn; tokt("\u2659");
  &blackking; tokt("\u265A");
  &blackqueen; tokt("\u265B");
  &blackrook; tokt("\u265C");
  &blackbishop; tokt("\u265D");
  &blackknight; tokt("\u265E");
  &blackpawn; tokt("\u265F");
  &bull; tokt("\u2022");
  &times; tokt("\u00D7");
  ' tokt("\\'");
  "\\" tokt("\\\\");

  &#[0-9]+; {
    char buf[5];
    utf8ize(atoi(yytext + 2), buf);
    tokt(buf);
  }

  & {
    yymore();
    BEGIN(XHP_INVALID_ENTITY);
  }
}

<XHP_INVALID_ENTITY>{
  {BYTE}{1,10} {
    yyextra->error = string("Invalid entity: (") + yytext + ")";
    yyextra->terminated = true;
  }
}

<XHP_AFTER_ENT>{
  [ \t\x0b\x0c\xa0\r\n]|\r\n {
    if (*yytext == '\r' || *yytext == '\n') {
      ++yyextra->lineno;
    }
    set_state(XHP_CHILD);
    yytext[0] = ' ';
    yytext[1] = 0;
    tok(T_XHP_TEXT);
  }
  . {
    set_state(XHP_CHILD);
    yyless(0);
  }
}

<XHP_CHILD>{
  [^&'<>\\{ \t\x0b\x0c\xa0\r\n]+{WHITESPACE}{0,1} {
    yy_scan_newlines(yytext, yyg);
    tok(T_XHP_TEXT);
  }
  {WHITESPACE}* {
    yy_scan_newlines(yytext, yyg);
    tok(T_XHP_TEXT);
  }
  {WHITESPACE}*"{" {
    yy_scan_newlines(yytext, yyg);
    tok('{');
  }
  {WHITESPACE}*"<" {
    yy_scan_newlines(yytext, yyg);
    tok('<');
  }
  {WHITESPACE}*"</" {
    yy_scan_newlines(yytext, yyg);
    tok(T_XHP_LESS_THAN_DIV);
  }
}

<XHP_CHILDREN_DECL>{
  {WHITESPACE}* yy_scan_newlines(yytext, yyg);
  any tok(T_XHP_ANY);
  empty tok(T_XHP_EMPTY);
  {LABEL} tok(T_STRING);
  ";" {
    pop_state();
    tok(';');
  }
}

 /* Other */
<*>{BYTE} {
  tok(yytext[0]);
  // fix unused function warnings
  yy_top_state(NULL);
  yyunput(0, 0, NULL);
}

%%

#ifdef DEBUG
static const char* yy_state_name(int state) {
  switch (state) {
    case INITIAL:
      return "INITIAL";
    case PHP:
      return "PHP";
    case PHP_COMMENT:
      return "PHP_COMMENT";
    case PHP_EOL_COMMENT:
      return "PHP_EOL_COMMENT";
    case PHP_DOC_COMMENT:
      return "PHP_DOC_COMMENT";
    case PHP_HEREDOC_START:
      return "PHP_HEREDOC_START";
    case PHP_HEREDOC_NSTART:
      return "PHP_HEREDOC_NSTART";
    case PHP_HEREDOC_NEWLINE:
      return "PHP_HEREDOC_NEWLINE";
    case PHP_HEREDOC_DATA:
      return "PHP_HEREDOC_DATA";
    case PHP_NO_RESERVED_WORDS:
      return "PHP_NO_RESERVED_WORDS";
    case PHP_NO_RESERVED_WORDS_STATEMENT:
      return "PHP_NO_RESERVED_WORDS_STATEMENT";
    case XHP_LABEL:
      return "XHP_LABEL";
    case XHP_LABEL_WHITESPACE:
      return "XHP_LABEL_WHITESPACE";
    case XHP_ATTRS:
      return "XHP_ATTRS";
    case XHP_ATTR_VAL:
      return "XHP_ATTR_VAL";
    case XHP_AFTER_ENT:
      return "XHP_AFTER_ENT";
    case XHP_CHILD:
      return "XHP_CHILD";
    case XHP_CHILD_START:
      return "XHP_CHILD_START";
    case XHP_INVALID_ENTITY:
      return "XHP_INVALID_ENTITY";
    case XHP_CHILDREN_DECL:
      return "XHP_CHILDREN_DECL";
    default:
      return "???";
  }
}

static void yy_log_token(int tok) {
  const char* tokname = yytokname(tok);
  if (tokname) {
    fprintf(stderr, "--> %s\n", tokname);
  } else {
    fprintf(stderr, "--> '%c'\n", tok);
  }
}
#endif

static int yy_token(int tok, yyguts_t* yyg) {
  if (YY_START == PHP_NO_RESERVED_WORDS) {
    pop_state();
  }

  switch (tok) {
    case T_OPEN_TAG:
    case T_OPEN_TAG_WITH_ECHO:
    case T_OPEN_TAG_FAKE:
      push_state(PHP);
      break;

    case T_CLOSE_TAG:
      pop_state();
      return ';';

    case T_OBJECT_OPERATOR:
    case T_XHP_ELEMENT:
      push_state(PHP_NO_RESERVED_WORDS);
      break;

    case '{':
      yyextra->curly_stack.push(tok);
      break;

    case ';':
      if (YY_START == PHP_NO_RESERVED_WORDS_STATEMENT) {
        pop_state();
      }
  }
#ifdef DEBUG
  yy_log_token(tok);
#endif
  return yyextra->last_token = tok;
}

static inline void yy_scan_newlines(const char* text, struct yyguts_t* yyg) {
  for (; *text; ++text) {
    if (*text == '\r') {
      if (text[1] == '\n') {
        ++text;
      }
      ++yyextra->lineno;
    } else if (*text == '\n') {
      ++yyextra->lineno;
    }
  }
}

void xhp_new_push_state(int s, struct yyguts_t* yyg) {
#ifdef DEBUG
  fprintf(stderr, "--> PUSH(%s -> %s)\n", yy_state_name(YY_START), yy_state_name(s));
#endif
  yy_push_state(s, yyg);
}

void xhp_new_pop_state(struct yyguts_t* yyg) {
#ifdef DEBUG
  int s = YY_START;
#endif
  yy_pop_state(yyg);
#ifdef DEBUG
  fprintf(stderr, "--> POP(%s -> %s)\n", yy_state_name(s), yy_state_name(YY_START));
#endif
}

void xhp_set_state(int s, struct yyguts_t* yyg) {
#ifdef DEBUG
  fprintf(stderr, "--> SET(%s)\n", yy_state_name(s));
#endif
  BEGIN(s);
}
