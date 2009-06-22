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

static int flex_tok(int t, void* y);
%}

%option stack
%option noyywrap
%option reentrant
%option bison-bridge
%option bison-locations

%s PHP
%s PHP_NO_RESERVED_WORDS
%s HEREDOC_LINE_START
%s HEREDOC_DATA
%s XHP
%s XHP_ATTR

%%
<INITIAL>{
  (?i:"<?php") return tok(t_PHP_OPEN_TAG);
  "<?" return tok(t_PHP_OPEN_TAG);
  "<?=" return tok(t_PHP_OPEN_TAG_WITH_ECHO);
  "<" *yylval = yytext; return tok(t_INLINE_HTML);
  [^<]* *yylval = yytext; return tok(t_INLINE_HTML);
}
<PHP,PHP_NO_RESERVED_WORDS>{
  "?>"\r?\n {
    ++yylloc->internal_line;
    flex_pop_state(yyg);
    return tok(t_PHP_CLOSE_TAG);
  }
  "?>" flex_pop_state(yyg); return tok(t_PHP_CLOSE_TAG);
}
<PHP,PHP_NO_RESERVED_WORDS,XHP_ATTR>{
  ("//"|"#").*  |
  [ \t\x0b\x0c\xa0\r]+ /* eat it up */
  \n {
    ++yylloc->internal_line;
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
  (?i:do) return tok(t_DO);
  (?i:while) return tok(t_WHILE);
  (?i:for) return tok(t_FOR);
  (?i:foreach) return tok(t_FOREACH);
  (?i:as) return tok(t_AS);
  (?i:switch) return tok(t_SWITCH);
  (?i:case) return tok(t_CASE);
  (?i:default) return tok(t_DEFAULT);
  (?i:break) return tok(t_BREAK);
  (?i:continue) return tok(t_CONTINUE);
  (?i:function) return tok(t_FUNCTION);
  (?i:const) return tok(t_CONST);
  (?i:instanceof) return tok(t_INSTANCEOF);
  (?i:return) return tok(t_RETURN);
  (?i:try) return tok(t_TRY);
  (?i:catch) return tok(t_CATCH);
  (?i:finally) return tok(t_CATCH);
  (?i:throw) return tok(t_THROW);
  (?i:global) return tok(t_GLOBAL);
  (?i:static) return tok(t_STATIC);
  (?i:abstract) return tok(t_ABSTRACT);
  (?i:final) return tok(t_FINAL);
  (?i:private) return tok(t_PRIVATE);
  (?i:protected) return tok(t_PROTECTED);
  (?i:public) return tok(t_PUBLIC);
  (?i:class) return tok(t_CLASS);
  (?i:interface) return tok(t_INTERFACE);
  (?i:extends) return tok(t_EXTENDS);
  (?i:implements) return tok(t_IMPLEMENTS);
  (?i:require_once) return tok(t_REQ_ONCE);
  (?i:include_once) return tok(t_INC_ONCE);
  (?i:require) return tok(t_REQ);
  (?i:include) return tok(t_INC);
}
<PHP,PHP_NO_RESERVED_WORDS,XHP_ATTR>{
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
  (?i:or) return tok(t_LOGICAL_OR);
  (?i:and) return tok(t_LOGICAL_AND);
  (?i:xor) return tok(t_LOGICAL_XOR);
  ".=" return tok(t_APPEND);
  "&&" return tok(t_AND);
  "||" return tok(t_OR);
  "->" {
    int tt = tok(t_ARROW);
    flex_push_state(PHP_NO_RESERVED_WORDS, yyg);
    return tt;
  }
  "=>" return tok(t_DOUBLE_ARROW);
  "::" return tok(t_HEBREW_THING);
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
  "=" return tok(t_ASSIGN);
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
<XHP_ATTR>{
  "/" return tok(t_XHP_DIV);
  ">" return tok(t_XHP_GREATER_THAN);
}
<PHP,PHP_NO_RESERVED_WORDS>{
  '(\\.|\\\n|[^\\']+)*' {
    *yylval = yytext;
    for (char* ii = yytext; *ii; ++ii) {
      if (*ii == '\n') {
        ++yylloc->actual_line_offset;
      }
    }
    return tok(t_LITERAL_STRING);
  }
  \"(\\.|\\\n|[^\\\"]+)*\" {
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
  [0-9]*\.?[0-9]+[eE]-?[0-9]{1,3}  {
    *yylval = yytext;
    return tok(t_NUMBER);
  }
  [0-9]+ |
  [0-9]*\.[0-9]+ {
    *yylval = yytext;
    return tok(t_NUMBER);
  }
}
<PHP,PHP_NO_RESERVED_WORDS,XHP_ATTR>{
  [a-zA-Z_$][a-zA-Z_$0-9]* {
    *yylval = yytext;
    return tok(t_IDENTIFIER);
  }
}
<XHP>{
  [^<"{]+ {
    *yylval = yytext;
    return tok(t_XHP_TEXT);
  }
  "{" {
    return tok(t_LCURLY);
  }
  \" {
    return tok(t_DOUBLE_QUOTE);
  }
  "<" {
    return tok(t_LESS_THAN);
  }
  "</" {
    return tok(t_XHP_LESS_THAN_DIV);
  }
}

<PHP,PHP_NO_RESERVED_WORDS>{
  "<<<".+\n {
    yyextra->heredoc_eom = yytext + 3;
    yyextra->heredoc_eom_len = strlen(yyextra->heredoc_eom) - 1;
    yyextra->heredoc_data_last = yyextra->heredoc_data_start = yyextra->heredoc_eom + yyextra->heredoc_eom_len + 1;
    if (yyextra->heredoc_eom[yyextra->heredoc_eom_len - 1] == '\r') {
      --yyextra->heredoc_eom_len;
    }
    ++yylloc->actual_line_offset;
    yymore();
    flex_push_state(HEREDOC_LINE_START, yyg);
    BEGIN(HEREDOC_LINE_START);
  }
}
<HEREDOC_LINE_START>{
  [a-zA-Z0-9]+$ {
    // copy-pasted below.
    if (yyextra->heredoc_eom_len <= strlen(yyextra->heredoc_data_last)
      && strncmp(yyextra->heredoc_eom, yyextra->heredoc_data_last, yyextra->heredoc_eom_len) == 0) {
      *yylval = yytext;
      *yylval = code_rope("<<<") + yyextra->heredoc_eom + "\n";
      flex_pop_state(yyg);
      return tok(t_HEREDOC);
    } else {
      yymore();
      BEGIN(HEREDOC_DATA);
    }
  }
  [a-zA-Z0-9]+/; {
    // copy-pasted from above.
    if (yyextra->heredoc_eom_len <= strlen(yyextra->heredoc_data_last)
      && strncmp(yyextra->heredoc_eom, yyextra->heredoc_data_last, yyextra->heredoc_eom_len) == 0) {
      *yylval = yytext;
      *yylval = code_rope("<<<") + yyextra->heredoc_eom + "\n";
      flex_pop_state(yyg);
      return tok(t_HEREDOC);
    } else {
      yymore();
      BEGIN(HEREDOC_DATA);
    }
  }
  . {
    yymore();
    BEGIN(HEREDOC_DATA);
  }
  \r?\n {
    ++yylloc->actual_line_offset;
    ++yyextra->heredoc_data_last;
    if (*yyextra->heredoc_data_last == '\n') {
      ++yyextra->heredoc_data_last;
    }
    yymore();
    BEGIN(HEREDOC_LINE_START);
  }
}
<HEREDOC_DATA>{
  .*\r?\n {
    ++yylloc->actual_line_offset;
    yyextra->heredoc_data_last += strlen(yyextra->heredoc_data_last);
    yymore();
    BEGIN(HEREDOC_LINE_START);
  }
}

<*>{
  .|\n  {
    fprintf(stderr,"Unknown text: (%s)\n", yytext);
    return tok(t_IDK);
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
    case XHP:
      return "XHP";
    case XHP_ATTR:
      return "XHP_ATTR";
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
  int o = (yyg->yy_start-1)/2;
  yy_pop_state(yyg);
//  fprintf(stderr, "--> POP(%s -> %s)\n", findstate(o), findstate((yyg->yy_start-1)/2));
}

static int flex_tok(int t, void* y) {
  yyguts_t* yyg = (yyguts_t*)y;
  if (YY_START == PHP_NO_RESERVED_WORDS) {
    flex_pop_state(yyg);
  }
//printf("\ntok:%d\n", YY_START);
  return t;
}
