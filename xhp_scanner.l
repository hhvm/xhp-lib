%{
#include "xhp_parser.hpp"
#define YY_USER_INIT \
  if (yyextra->firsttoken) { \
    yyg->yy_init = 0; \
    int ft = yyextra->firsttoken; \
    yyextra->firsttoken = 0; \
    return ft; \
  }
#define tok(t) flex_tok(t, yyg);
#define tokent(s) *yylval = s; BEGIN(XHP_AFTER_ENT); return tok(t_XHP_TEXT);

static int flex_tok(int t, void* y);
const char* yytokname(int tok);

bool utf8ize(uint32_t v, char* buf /* [5] */) {
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

%option stack
%option noyywrap
%option reentrant
%option bison-bridge
%option bison-locations

%s TERMINATE
%s PHP
%s PHP_NO_RESERVED_WORDS
%s HEREDOC_LINE_START
%s HEREDOC_DATA
%s XHP_CHILD
%s XHP_CHILD_START
%s XHP_AFTER_ENT
%s XHP_LABEL
%s XHP_ATTR
%s XHP_ATTR_VAL

NEWLINE ("\r"|"\n"|"\r\n")
LABEL [a-zA-Z_\x7f-\xff][0-9a-zA-Z_\x7f-\xff]*
WHITESPACE [ \t\x0b\x0c\xa0\r\n]
B b?

%%
<TERMINATE>{
  .|\n {
    return 0;
  }
}
<INITIAL>{
  (?i:"<?php") return tok(t_PHP_OPEN_TAG);
  "<?" return tok(t_PHP_OPEN_TAG);
  "<?=" return tok(t_PHP_OPEN_TAG_WITH_ECHO);
  "<" *yylval = yytext; return tok(t_INLINE_HTML);
  [^<]* *yylval = yytext; return tok(t_INLINE_HTML);
}
<PHP,PHP_NO_RESERVED_WORDS>{
  "?>"{NEWLINE} {
    ++yylloc->internal_line;
    flex_pop_state(yyg);
    return tok(t_PHP_CLOSE_TAG);
  }
  "?>" flex_pop_state(yyg); return tok(t_PHP_CLOSE_TAG);
}
<PHP,PHP_NO_RESERVED_WORDS,XHP_ATTR>{
  [ \t\x0b\x0c\xa0]+ /* eat it up */
  {NEWLINE} {
    ++yylloc->internal_line;
  }
  "//"|"#" {
    char c;
    for (;;) {
      while ((c = yyinput(yyscanner)) != '?' && c != '\r' && c != '\n' && c != EOF);
      honk:
      if (c == '\r') {
        ++yylloc->internal_line;
        c = yyinput(yyscanner);
        if (c != '\n') {
          unput(c);
          break;
        }
      } else if (c == '\n') {
        ++yylloc->internal_line;
        break;
      }
      if (c == '?') {
        c = yyinput(yyscanner);
        if (c == '>') {
          unput('>');
          unput('?');
          break;
        }
        goto honk;
      }
      if (c == EOF) {
        return tok(0);
      }
    }
  }
  "/*" {
    char c;
    for (;;) {
      while ((c = yyinput(yyscanner)) != '*' && c != EOF) {
        if (c == '\n') {
          ++yylloc->internal_line;
        }
      }
      if (c == '*') {
        while ((c = yyinput(yyscanner)) == '*');
        if (c == '/') {
          break;
        } else if (c == '\n') {
          ++yylloc->internal_line;
        }
      }
      if (c == EOF) {
        return tok(0);
        break;
      }
    }
  }
}
<PHP>{
  (?i:new) return tok(t_NEW);
  (?i:clone) return tok(t_CLONE);
  (?i:echo) return tok(t_ECHO);
  (?i:print) return tok(t_PRINT);
  (?i:if) return tok(t_IF);
  (?i:else) return tok(t_ELSE);
  (?i:elseif) return tok(t_ELSEIF);
  (?i:endif) return tok(t_ENDIF);
  (?i:do) return tok(t_DO);
  (?i:while) return tok(t_WHILE);
  (?i:endwhile) return tok(t_ENDWHILE);
  (?i:for) return tok(t_FOR);
  (?i:endfor) return tok(t_ENDFOR);
  (?i:foreach) return tok(t_FOREACH);
  (?i:endforeach) return tok(t_ENDFOREACH);
  (?i:as) return tok(t_AS);
  (?i:switch) return tok(t_SWITCH);
  (?i:endswitch) return tok(t_ENDSWITCH);
  (?i:case) return tok(t_CASE);
  (?i:default) return tok(t_DEFAULT);
  (?i:break) return tok(t_BREAK);
  (?i:continue) return tok(t_CONTINUE);
  (?i:function) {
    int tt = tok(t_FUNCTION);
    // needed so you can say function element(){}
    // this only works on objects, though.
    flex_push_state(PHP_NO_RESERVED_WORDS, yyg);
    return tt;
  }
  (?i:const) return tok(t_CONST);
  (?i:instanceof) return tok(t_INSTANCEOF);
  (?i:return) return tok(t_RETURN);
  (?i:try) return tok(t_TRY);
  (?i:catch) return tok(t_CATCH);
  (?i:throw) return tok(t_THROW);
  (?i:global) return tok(t_GLOBAL);
  (?i:static) return tok(t_STATIC);
  (?i:abstract) return tok(t_ABSTRACT);
  (?i:final) return tok(t_FINAL);
  (?i:private) return tok(t_PRIVATE);
  (?i:protected) return tok(t_PROTECTED);
  (?i:public) return tok(t_PUBLIC);
  (?i:var) return tok(t_VAR);
  (?i:class) return tok(t_CLASS);
  (?i:element) return tok(t_ELEMENT);
  (?i:interface) return tok(t_INTERFACE);
  (?i:extends) return tok(t_EXTENDS);
  (?i:implements) return tok(t_IMPLEMENTS);
  (?i:require_once) return tok(t_REQ_ONCE);
  (?i:include_once) return tok(t_INC_ONCE);
  (?i:require) return tok(t_REQ);
  (?i:include) return tok(t_INC);
  (?i:array) return tok(t_ARRAY);
  (?i:or) return tok(t_LOGICAL_OR);
  (?i:and) return tok(t_LOGICAL_AND);
  (?i:xor) return tok(t_LOGICAL_XOR);
}
<PHP,PHP_NO_RESERVED_WORDS>{
  "=" return tok(t_ASSIGN);
}
<PHP,PHP_NO_RESERVED_WORDS,XHP_ATTR,XHP_LABEL>{
  "===" return tok(t_STRICT_EQUAL);
  "!==" return tok(t_STRICT_NOT_EQUAL);
  "<<=" return tok(t_LSHIFT_ASSIGN);
  ">>=" return tok(t_RSHIFT_ASSIGN);
  "<=" return tok(t_LESS_THAN_EQUAL);
  ">=" return tok(t_GREATER_THAN_EQUAL);
  "==" return tok(t_EQUAL);
  "!="|"<>" return tok(t_NOT_EQUAL);
  "++" return tok(t_INCR);
  "--" return tok(t_DECR);
  "<<" return tok(t_LSHIFT);
  ">>" return tok(t_RSHIFT);
  "+=" return tok(t_PLUS_ASSIGN);
  "-=" return tok(t_MINUS_ASSIGN);
  "/=" return tok(t_DIV_ASSIGN);
  "*=" return tok(t_MULT_ASSIGN);
  "%=" return tok(t_MOD_ASSIGN);
  "&=" return tok(t_BIT_AND_ASSIGN);
  "|=" return tok(t_BIT_OR_ASSIGN);
  "^=" return tok(t_BIT_XOR_ASSIGN);
  ".=" return tok(t_APPEND);
  "&&" return tok(t_AND);
  "||" return tok(t_OR);
  "->" {
    int tt = tok(t_ARROW);
    flex_push_state(PHP_NO_RESERVED_WORDS, yyg);
    return tt;
  }
  "=>" return tok(t_DOUBLE_ARROW);
  "::" {
    int tt = tok(t_HEBREW_THING);
    flex_push_state(PHP_NO_RESERVED_WORDS, yyg);
    return tt;
  }
  "." return tok(t_CONCAT);
  "," return tok(t_COMMA);
  ";" return tok(t_SEMICOLON);
  "?" return tok(t_PLING);
  ":" return tok(t_COLON);
  "<" return tok(t_LESS_THAN);
  "+" return tok(t_PLUS);
  "-" return tok(t_MINUS);
  "*" return tok(t_MULT);
  "%" return tok(t_MOD);
  "|" return tok(t_BIT_OR);
  "&" return tok(t_BIT_AND);
  "^" return tok(t_BIT_XOR);
  "!" return tok(t_NOT);
  "~" return tok(t_BIT_NOT);
  "$" return tok(t_DOLLAR);
  "@" return tok(t_AT);
  "(" return tok(t_LPAREN);
  ")" return tok(t_RPAREN);
  "{" return tok(t_LCURLY);
  "}" return tok(t_RCURLY);
  "[" return tok(t_LBRACKET);
  "]" return tok(t_RBRACKET);
  "\"" return tok(t_DOUBLE_QUOTE);
  "?>" BEGIN(INITIAL);
}
<PHP,PHP_NO_RESERVED_WORDS>{
  "/" return tok(t_DIV);
  ">" return tok(t_GREATER_THAN);
}
<PHP,PHP_NO_RESERVED_WORDS>{
  {B}'(\\.|\\\n|[^\\']+)*' {
    *yylval = yytext;
    for (char* ii = yytext; *ii; ++ii) {
      if (*ii == '\n') {
        ++yylloc->actual_line_offset;
      }
    }
    return tok(t_LITERAL_STRING);
  }
  {B}\"(\\.|\\\n|[^\\\"]+)*\" {
    *yylval = yytext;
    for (char* ii = yytext; *ii; ++ii) {
      if (*ii == '\n') {
        ++yylloc->actual_line_offset;
      }
    }
    return tok(t_EVALUATED_STRING);
  }
  `[^`]*` {
    *yylval = yytext;
    for (char* ii = yytext; *ii; ++ii) {
      if (*ii == '\n') {
        ++yylloc->actual_line_offset;
      }
    }
    return tok(t_SHELL_EXPRESSION);
  }
  0x[a-fA-F0-9]+ {
    *yylval = yytext;
    return tok(t_NUMBER);
  }
  0[0-7]+ {
    *yylval = yytext;
    return tok(t_NUMBER);
  }
  [0-9]*\.?[0-9]+[eE][\-+]?[0-9]{1,3}  {
    *yylval = yytext;
    return tok(t_NUMBER);
  }
  [0-9]+\.? |
  [0-9]*\.[0-9]+ {
    *yylval = yytext;
    return tok(t_NUMBER);
  }
}
<PHP,PHP_NO_RESERVED_WORDS>{
  {B}"<<<".+{NEWLINE} {
    char* eom = yytext;
    if (*eom == 'b') {
      ++eom;
    }
    eom += 3;
    while (*eom == '\t' || *eom == ' ') ++eom;
    size_t len = yyleng - (eom - yytext) - 1;
    if (eom[len - 1] == '\r') { // windows [\r\n] encoding
      --len;
    }
    yyextra->heredoc_eom = eom;
    yyextra->heredoc_eom_len = len;
    yyextra->heredoc_data_last = yytext + yyleng;
    ++yylloc->actual_line_offset;
    yymore();
    flex_push_state(HEREDOC_LINE_START, yyg);
  }
}
<HEREDOC_LINE_START>{
  {LABEL};?{NEWLINE} {
    size_t len = yyleng - (yyextra->heredoc_data_last - yytext);
    if (yyextra->heredoc_eom_len <= len &&
        strncmp(yyextra->heredoc_eom, yyextra->heredoc_data_last, yyextra->heredoc_eom_len) == 0
      ) {
      char* trailing = yytext + yyleng - 1;
      if (*trailing == '\n') {
        --trailing;
      }
      if (*trailing == '\r') {
        --trailing;
      }
      if (*trailing == ';') {
        yyless(trailing - yytext);
      }
      *yylval = code_rope(yytext) + "\n";
      flex_pop_state(yyg);
      ++yylloc->internal_line;
      return tok(t_HEREDOC);
    } else {
      ++yylloc->actual_line_offset;
      yyextra->heredoc_data_last = yytext + yyleng;
      yymore();
    }
  }
  [^\r\n]+ {
    yymore();
    BEGIN(HEREDOC_DATA);
  }
  {NEWLINE} {
    ++yylloc->actual_line_offset;
    yyextra->heredoc_data_last = yytext + yyleng;
    yymore();
  }
}
<HEREDOC_DATA>{
  .*{NEWLINE} {
    ++yylloc->actual_line_offset;
    yyextra->heredoc_data_last = yytext + yyleng;
    yymore();
    BEGIN(HEREDOC_LINE_START);
  }
}
<PHP,PHP_NO_RESERVED_WORDS,XHP_ATTR,XHP_LABEL>{
  [a-zA-Z_$][a-zA-Z_$0-9]* {
    *yylval = yytext;
    return tok(t_IDENTIFIER);
  }
}

<XHP_ATTR>{
  "/" return tok(t_XHP_DIV);
  ">" return tok(t_XHP_GREATER_THAN);
}
<XHP_LABEL>{
  {WHITESPACE} {
    flex_pop_state(yyg);
    if (*yytext == '\n') {
      ++yylloc->internal_line;
    } else if (*yytext == '\r') {
      yyless(0);
    }
    return tok(t_XHP_WHITESPACE);
  }
  "=" {
    flex_pop_state(yyg);
    return tok(t_ASSIGN);
  }
  "/" {
    flex_pop_state(yyg);
    return tok(t_XHP_DIV);
  }
  ">" {
    flex_pop_state(yyg);
    return tok(t_XHP_GREATER_THAN);
  }
}
<XHP_CHILD_START>{
  {WHITESPACE}+ {
    /* ignore whitespace at the start */
    yytext[0] = ' ';
    yyless(yyleng - 1);
    BEGIN(XHP_CHILD);
  }
  . {
    yyless(0);
    BEGIN(XHP_CHILD);
  }
}
<XHP_CHILD,XHP_AFTER_ENT,XHP_ATTR_VAL>{
  &amp; {
    tokent("&");
  }
  &quot; {
    tokent("\"");
  }
  &lt; {
    tokent("<")
  }
  &gt; {
    tokent(">");
  }
  &middot; {
    tokent("\u00B7");
  }
  &laquo; {
    tokent("\u00AB");
  }
  &raquo; {
    tokent("\u00BB");
  }
  &lsaquo; {
    tokent("\u2039");
  }
  &rsaquo; {
    tokent("\u203A");
  }
  &lsquo; {
    tokent("\u2018");
  }
  &rsquo; {
    tokent("\u2019");
  }
  &ldquo; {
    tokent("\u201C");
  }
  &rdquo; {
    tokent("\u201D");
  }
  &hellip; {
    tokent("\u2026");
  }
  &mdash; {
    tokent("\u2014");
  }
  &hearts; {
    tokent("\u2665");
  }
  &cloud; {
    tokent("\u2601");
  }
  &umbrella; {
    tokent("\u2602");
  }
  &snowman; {
    tokent("\u2603");
  }
  &snowflake; {
    tokent("\u2745");
  }
  &comet; {
    tokent("\u2604");
  }
  &thunderstorm; {
    tokent("\u2608");
  }
  &whiteking; {
    tokent("\u2654");
  }
  &whitequeen; {
    tokent("\u2655");
  }
  &whiterook; {
    tokent("\u2656");
  }
  &whitebishop; {
    tokent("\u2657");
  }
  &whiteknight; {
    tokent("\u2658");
  }
  &whitepawn; {
    tokent("\u2659");
  }
  &blackking; {
    tokent("\u265A");
  }
  &blackqueen; {
    tokent("\u265B");
  }
  &blackrook; {
    tokent("\u265C");
  }
  &blackbishop; {
    tokent("\u265D");
  }
  &blackknight; {
    tokent("\u265E");
  }
  &blackpawn; {
    tokent("\u265F");
  }
  &bull; {
    tokent("\u2022");
  }
  &#[0-9]+; {
    char buf[5];
    utf8ize(atoi(yytext + 2), buf);
    tokent(buf);
  }
  &[^;]{0,5} {
    fprintf(stderr, "Unknown entity: (%s)\n", yytext);
    return 0;
  }
  ' {
    tokent("\\'");
  }
  "\\" {
    tokent("\\\\");
  }
}
<XHP_CHILD,XHP_AFTER_ENT>{
  [^&'<>\\{ \t\x0b\x0c\xa0\r\n]+{WHITESPACE}{0,1} {
    *yylval = yytext;
    BEGIN(XHP_CHILD);
    return tok(t_XHP_TEXT);
  }
  {WHITESPACE}* {
    *yylval = yytext;
    BEGIN(XHP_CHILD);
    return tok(t_XHP_TEXT);
  }
}
<XHP_CHILD>{
  {WHITESPACE}*"{" {
    return tok(t_LCURLY);
  }
  {WHITESPACE}*"<" {
    return tok(t_LESS_THAN);
  }
  {WHITESPACE}*"</" {
    return tok(t_XHP_LESS_THAN_DIV);
  }
}
<XHP_ATTR_VAL>{
  [^&'\\"]+ {
    *yylval = yytext;
    return tok(t_XHP_TEXT);
  }
  \" {
    flex_pop_state(yyg);
    return tok(t_DOUBLE_QUOTE);
  }
}

<*>{
  .|\n  {
    fprintf(stderr, "Unknown text: (%s)\n", yytext);
    return 0;
    if (0) {
      // stop warning me about unused functions!
      yyunput(0, NULL, NULL);
      yy_top_state(NULL);
    }
  }
}

%%

inline char* findstate(int s) {
  switch(s) {
    case INITIAL:
      return "INITIAL";
    case PHP:
      return "PHP";
    case PHP_NO_RESERVED_WORDS:
      return "PHP_NO_RESERVED_WORDS";
    case HEREDOC_LINE_START:
      return "HEREDOC_LINE_START";
    case HEREDOC_DATA:
      return "HEREDOC_DATA";
    case XHP_CHILD:
      return "XHP_CHILD";
    case XHP_CHILD_START:
      return "XHP_CHILD_START";
    case XHP_AFTER_ENT:
      return "XHP_AFTER_ENT";
    case XHP_LABEL:
      return "XHP_LABEL";
    case XHP_ATTR:
      return "XHP_ATTR";
    case XHP_ATTR_VAL:
      return "XHP_ATTR_VAL";
    default:
      char* a = new char[12];
      sprintf(a, "%d", s);
      return a;
  }
}

void flexBEGIN(int s, void* y) {
  yyguts_t* yyg = (yyguts_t*)y;
  BEGIN(s);
}

void flex_push_state(int s, void* y) {
  yyguts_t* yyg = (yyguts_t*)y;
//  fprintf(stderr, "--> PUSH(%s -> %s)\n", findstate((yyg->yy_start-1)/2), findstate(s));
  yy_push_state(s, yyg);
}

void flex_pop_state(void* y) {
  yyguts_t* yyg = (yyguts_t*)y;
//  int o = (yyg->yy_start-1)/2; fprintf(stderr, "--> POP(%s -> %s)\n", findstate(o), findstate((yyg->yy_start-1)/2));
  yy_pop_state(yyg);
}

static int flex_tok(int t, void* y) {
  yyguts_t* yyg = (yyguts_t*)y;
  if (YY_START == PHP_NO_RESERVED_WORDS) {
    flex_pop_state(yyg);
  }
//  fprintf(stderr, "\ntok:%s\n", yytokname(t));
  return t;
}
