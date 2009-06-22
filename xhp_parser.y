%{
  #include "xhp_parser.hpp"
  #include "zend_compile.h"
  #include <sstream>
%}

%{
  #ifdef yylineno
  #undef yylineno
  #endif
  #define yylineno (unsigned int)(yylloc.internal_line)  
  #define cr(s) code_rope(s, yylineno)
  extern int yydebug;
  static void yyerror(YYLTYPE* xhplloc, void* yyscanner, const char* filename, code_rope* str, const char* a) {
    CG(zend_lineno) = xhplloc->internal_line + xhplloc->actual_line_offset;
    zend_set_compiled_filename(const_cast<char*>(filename) TSRMLS_CC);
    *str = a;
    return;

    std::stringstream c;
    c << xhplloc->internal_line + xhplloc->actual_line_offset;
    *str = (std::string(a) + " in " + filename + " on line " + c.str()).c_str();
  }
%}

%locations
%pure-parser
%parse-param { void* yyscanner }
%parse-param { const char* filename }
%parse-param { code_rope* root }
%lex-param { void* yyscanner }
%error-verbose

// Keywords
%token t_IF 
%nonassoc p_IF
%left t_ELSEIF
%left t_ELSE
%token t_DO t_WHILE t_FOR t_FOREACH
%token t_SWITCH t_CASE t_DEFAULT t_BREAK t_CONTINUE
%token t_FUNCTION t_RETURN
%token t_NEW t_CLONE
%token t_TRY
%nonassoc t_CATCH
%nonassoc t_FINALLY
%nonassoc p_CATCH;
%token t_ABSTRACT t_FINAL t_PRIVATE t_PROTECTED t_PUBLIC
%token t_CLASS t_INTERFACE t_EXTENDS t_IMPLEMENTS

// Literals
%token t_LITERAL_STRING t_EVALUATED_STRING t_SHELL_EXPRESSION
%token t_NUMBER
%token t_HEREDOC
%token t_XHP_TEXT
%token t_XHP_DIV t_XHP_LESS_THAN_DIV t_XHP_GREATER_THAN

// Operators
%left t_AS
%left t_COMMA
%left t_LOGICAL_OR
%left t_LOGICAL_XOR
%left t_LOGICAL_AND
%right t_PRINT
%right t_ECHO
%right t_ASSIGN t_APPEND t_PLUS_ASSIGN t_MINUS_ASSIGN t_DIV_ASSIGN t_MULT_ASSIGN t_MOD_ASSIGN t_BIT_AND_ASSIGN t_BIT_OR_ASSIGN t_BIT_XOR_ASSIGN t_LSHIFT_ASSIGN t_RSHIFT_ASSIGN
%left t_PLING t_COLON
%left t_OR
%left t_AND
%left t_BIT_OR
%left t_BIT_XOR
%left t_BIT_AND
%nonassoc t_EQUAL t_NOT_EQUAL t_STRICT_EQUAL t_STRICT_NOT_EQUAL
%nonassoc t_LESS_THAN_EQUAL t_GREATER_THAN_EQUAL t_LESS_THAN t_GREATER_THAN
%left t_LSHIFT t_RSHIFT
%left t_PLUS t_MINUS t_CONCAT
%left t_MULT t_DIV t_MOD
%right t_NOT t_BIT_NOT t_INCR t_DECR // also casting operators and "@"
%right t_INSTANCEOF
%right t_LBRACKET
%token t_RBRACKET
%token t_RCURLY
%nonassoc t_NEW
%nonassoc t_CLONE
%left t_CONST
%left t_GLOBAL
%right t_THROW
%left t_STATIC
%left t_ARROW t_DOUBLE_ARROW
%left t_HEBREW_THING
%left t_LPAREN t_RPAREN
%right t_REQ_ONCE
%right t_INC_ONCE
%right t_REQ
%right t_INC
%right t_DOLLAR
%right t_AT
%right t_LCURLY

// Misc
%token t_SEMICOLON
%token t_IDENTIFIER t_DOUBLE_QUOTE t_PHP_OPEN_TAG t_PHP_FAKE_OPEN_TAG t_PHP_CLOSE_TAG t_PHP_OPEN_TAG_WITH_ECHO
%token t_INLINE_HTML
%token t_IDK

%start program
%initial-action {
  yylloc.internal_line = 1;
  yylloc.actual_line_offset = 0;
}
%%

// Top level
program:
  statement_list {
    *root = $1;
  }
;

statement_list:
  /* empty */ {
    $$ = cr("");
  }
|  statement_list statement {
    $$ = $1 + $2;
  }
;

// Statements
statement:
  t_LCURLY statement_list t_RCURLY {
    $$ = "{" + $2 + "}";
  }
| t_PHP_OPEN_TAG {
    yy_push_state(PHP);
    $$ = cr("<?php ");
  }
| t_PHP_FAKE_OPEN_TAG {
    yy_push_state(PHP);
    $$ = cr("");
  }
| t_PHP_OPEN_TAG_WITH_ECHO {
    yy_push_state(PHP);
    $$ = cr("<?=");
  }
|  expression_statement
|  if_statement
|  for_statement
|  foreach_statement
|  do_statement
|  switch_statement
|  return_statement
|  class_statement
|  try_statement
|  declaration_statement
|  function
| semicolon
| t_INLINE_HTML
;

semicolon:
  t_PHP_CLOSE_TAG {
    $$ = "?>";
  }
| t_SEMICOLON {
    $$ = ";";
  }
;

expression_statement:
  expression_with_comma semicolon {
    $$ = $1 + $2;
  }
;

if_statement:
  t_IF t_LPAREN expression t_RPAREN statement {
    $$ = "if (" + $3 + ") " + $5;
  }
|  statement t_ELSE statement {
    $$ = $1 + " else " + $3;
  }
| statement t_ELSEIF t_LPAREN expression t_RPAREN statement {
    $$ = $1 + "elseif (" + $4 + ") " + $6;
  }
;

for_statement: 
  t_FOR t_LPAREN statement statement expression_with_comma t_RPAREN statement {
    $$ = "for (" + $3 + $4 + $5 + ") " + $7;
  }
|  t_FOR t_LPAREN statement statement t_RPAREN statement {
    $$ = "for (" + $3 + $4 + ") " + $6;
  }
;

foreach_statement: 
  t_FOREACH t_LPAREN expression t_RPAREN statement {
    $$ = "foreach (" + $3 + ") " + $5;
  }
;

do_statement:
  t_DO statement t_WHILE t_LPAREN expression t_RPAREN semicolon {
    $$ = "do " + $2 + " while (" + $5 + ")" + $7;
  }
|  t_WHILE t_LPAREN expression t_RPAREN statement {
    $$ = "while (" + $3 + ") " + $5;
  }
;

switch_statement:
  t_SWITCH t_LPAREN expression t_RPAREN statement {
    $$ = "switch (" + $3 + ") " + $5;
  }
|  t_CASE expression t_COLON {
    $$ = "case " + $2 + ":";
  }
|  t_CASE expression semicolon {
    $$ = "case " + $2 + $3;
  }
|  t_DEFAULT t_COLON {
    $$ = "default:";
  }
|  t_DEFAULT semicolon {
    $$ = "default" + $2;
  }
|  t_BREAK expression semicolon {
    $$ = "break " + $2 + $3;
  }
|  t_BREAK semicolon {
    $$ = "break" + $2;
  }
|  t_CONTINUE expression semicolon {
    $$ = "continue" + $2 + $3;
  }
|  t_CONTINUE semicolon {
    $$ = "continue" + $2;
  }
;

return_statement:
  t_RETURN expression semicolon {
    $$ = "return " + $2 + $3;
  }
|  t_RETURN semicolon {
    $$ = cr("return") + $2;
  }
;

try_statement:
  t_TRY t_LCURLY statement_list t_RCURLY catch_blocks {
    $$ = "try { " + $3 + "} " + $5;
  }
;

catch_blocks:
  catch_blocks catch_blocks %prec p_CATCH {
    $$ = $1 + $2;
  }
|  t_CATCH t_LPAREN identifier expression t_RPAREN t_LCURLY statement_list t_RCURLY {
    $$ = "catch(" + $3 + " " + $4 + ") {" + $7 + "}";
  }
|  t_FINALLY t_LCURLY statement_list t_RCURLY {
    $$ = "finally {" + $3 + "}";
  }
;

// Argument list
argument_list:
  t_LPAREN t_RPAREN {
    $$ = cr("()");
  }
|  t_LPAREN _argument_list t_RPAREN {
    $$ = "(" + $2 + ")";
  }
|  t_LPAREN _argument_list t_COMMA t_RPAREN {
    $$ = "(" + $2 + ",)";
  }
;

_argument_list:
  expression
| t_COMMA {
    $$ = ",";
  }
| t_COMMA expression {
    $$ = "," + $2;
  }
|  _argument_list t_COMMA expression {
    $$ = $1 + "," + $3;
  }
|  _argument_list t_COMMA {
    $$ = $1 + ",";
  }
;

// Literals
numeric_literal:
  t_NUMBER {
    $$ = cr($1);
  }
;

string_literal:
  t_LITERAL_STRING {
    $$ = cr($1);
  }
|  t_EVALUATED_STRING {
    $$ = cr($1);
  }
;

heredoc_literal:
  t_HEREDOC {
    $$ = cr($1);
  }
;

// Expressions
literal_expression:
  numeric_literal
|  string_literal
|  heredoc_literal
;

identifier:
  t_IDENTIFIER {
    $$ = cr($1);
  }
;

// XHP extensions
xhp_expression:
  xhp_singleton
|  xhp_open_tag xhp_children xhp_close_tag {
    $$ = $1 + $2 + $3;
  }
;

xhp_children:
  xhp_children_ {
    if ($1.back() == ',') {
      $1.pop_back();
      $$ = "array(" + $1 + ")";
    } else {
      $$ = "null";
    }
  }
;

xhp_children_:
  /* empty */ {
    $$ = cr("");
  }
|  xhp_children_ xhp_child {
    $$ = $1 + $2 + ",";
  }
;

xhp_child:
  t_XHP_TEXT {
    $$ = "\"" + $1 + "\"";
  }
|  xhp_expression
|  t_LCURLY { yy_push_state(PHP); } expression t_RCURLY { yy_pop_state(); } {
    $$ = $3;
  }
;

xhp_attributes:
  /* empty */ {
    $$ = cr("");
  }
|  xhp_attributes xhp_attribute {
    $$ = $1 + $2 + ",";
  }

xhp_attribute:
  t_IDENTIFIER t_ASSIGN { yy_push_state(XHP); } t_DOUBLE_QUOTE t_XHP_TEXT { yy_pop_state(); } t_DOUBLE_QUOTE {
    $$ = "\"" + $1 + "\" => " + $5;
  }
|  t_IDENTIFIER t_ASSIGN { yy_push_state(PHP); } t_LCURLY expression { yy_pop_state(); } t_RCURLY {
    $$ = "\"" + $1 + "\" => " + $5;
  }
;

xhp_lt:
  t_LESS_THAN {
    $$ = cr("");
    yy_push_state(XHP_ATTR);
  }
;

xhp_tag_name:
  t_IDENTIFIER
|  xhp_tag_name t_COLON t_IDENTIFIER {
    $$ = $1 + "_" + $3;
  }
|  xhp_tag_name t_MINUS t_IDENTIFIER {
    $$ = $1 + "-" + $3;
  }
;

xhp_singleton:
  xhp_lt xhp_tag_name xhp_attributes t_XHP_DIV t_XHP_GREATER_THAN {
    yy_pop_state();
    $$ = $1 + "new xhp_" + $2 + "(array(" + $3 + "), array())";
  }
;

xhp_open_tag:
  xhp_lt xhp_tag_name xhp_attributes t_XHP_GREATER_THAN {
    yy_pop_state();
    yy_push_state(XHP);
    $$ = $1 + "new xhp_" + $2 + "(array(" + $3 + "), ";
  }
;

xhp_close_tag:
  t_XHP_LESS_THAN_DIV { yy_push_state(XHP_ATTR); } t_IDENTIFIER t_XHP_GREATER_THAN {
    yy_pop_state();
    yy_pop_state();
    // TODO: check stack for mismatched tags
    $$ = ")";
  }
;

expression_with_comma:
  expression
|  expression_with_comma t_COMMA expression {
    $$ = $1 + "," + $3;
  }
;

variables_and_stuff:
  literal_expression
| t_SHELL_EXPRESSION
|  identifier
|  xhp_expression
|  expression t_LBRACKET expression t_RBRACKET {
    $$ = $1 + "[" + $3 + "]";
  }
|  expression t_ARROW t_LCURLY expression t_RCURLY {
    $$ = $1 + "->{" + $4 + "}";
  }
;

expression:
  variables_and_stuff
|  variables_and_stuff argument_list {
    $$ = $1 + $2;
  }
| identifier identifier {
    $$ = $1 + " " + $2;
  }
|  t_LPAREN expression t_RPAREN {
    $$ = "(" + $2 + ")";
  }
|  t_LPAREN expression t_RPAREN expression {
    $$ = "(" + $2 + ")" + $4;
  }
|  expression t_LCURLY expression t_RCURLY {
    $$ = $1 + "{" + $3 + "}";
  }
|  expression t_LBRACKET t_RBRACKET {
    $$ = $1 + "[]";
  }
|  expression t_PLING expression t_COLON expression {
    $$ = $1 + " ? " + $3 + " : " + $5;
  }
|  expression t_ASSIGN expression {
    $$ = $1 + "=" + $3;
  }
|  expression t_APPEND expression {
    $$ = $1 + ".=" + $3;
  }
|  expression t_PLUS_ASSIGN expression {
    $$ = $1 + "+=" + $3;
  }
|  expression t_MINUS_ASSIGN expression {
    $$ = $1 + "-=" + $3;
  }
|  expression t_DIV_ASSIGN expression {
    $$ = $1 + "/=" + $3;
  }
|  expression t_MULT_ASSIGN expression {
    $$ = $1 + "*=" + $3;
  }
|  expression t_MOD_ASSIGN expression {
    $$ = $1 + "%=" + $3;
  }
|  expression t_BIT_AND_ASSIGN expression {
    $$ = $1 + "&=" + $3;
  }
|  expression t_BIT_OR_ASSIGN expression {
    $$ = $1 + "|=" + $3;
  }
|  expression t_BIT_XOR_ASSIGN expression {
    $$ = $1 + "^=" + $3;
  }
|  expression t_LSHIFT_ASSIGN expression {
    $$ = $1 + "<<=" + $3;
  }
|  expression t_RSHIFT_ASSIGN expression {
    $$ = $1 + ">>=" + $3;
  }
|  expression t_OR expression {
    $$ = $1 + "||" + $3;
  }
|  expression t_AND expression {
    $$ = $1 + "&&" + $3;
  }
|  expression t_BIT_OR expression {
    $$ = $1 + "|" + $3;
  }
|  expression t_BIT_AND expression {
    $$ = $1 + "&" + $3;
  }
|  expression t_BIT_XOR expression {
    $$ = $1 + "^" + $3;
  }
|  expression t_LOGICAL_OR expression {
    $$ = $1 + " OR " + $3;
  }
|  expression t_LOGICAL_XOR expression {
    $$ = $1 + " XOR " + $3;
  }
|  expression t_LOGICAL_AND expression {
    $$ = $1 + " AND " + $3;
  }
|  expression t_EQUAL expression {
    $$ = $1 + "==" + $3;
  }
|  expression t_NOT_EQUAL expression {
    $$ = $1 + "!=" + $3;
  }
|  expression t_STRICT_EQUAL expression {
    $$ = $1 + "===" + $3;
  }
|  expression t_STRICT_NOT_EQUAL expression {
    $$ = $1 + "!==" + $3;
  }
|  expression t_LESS_THAN_EQUAL expression {
    $$ = $1 + "<=" + $3;
  }
|  expression t_GREATER_THAN_EQUAL expression {
    $$ = $1 + ">=" + $3;
  }
|  expression t_LESS_THAN expression {
    $$ = $1 + "<" + $3;
  }
|  expression t_GREATER_THAN expression {
    $$ = $1 + ">" + $3;
  }
|  expression t_LSHIFT expression {
    $$ = $1 + "<<" + $3;
  }
|  expression t_RSHIFT expression {
    $$ = $1 + ">>" + $3;
  }
|  expression t_PLUS expression {
    $$ = $1 + "+" + $3;
  }
|  expression t_MINUS expression {
    $$ = $1 + "-" + $3;
  }
|  expression t_MULT expression {
    $$ = $1 + "*" + $3;
  }
|  expression t_DIV expression {
    $$ = $1 + "/" + $3;
  }
|  expression t_MOD expression {
    $$ = $1 + "%" + $3;
  }
|  expression t_CONCAT expression {
    $$ = $1 + " . " + $3;
  }
|  expression t_INSTANCEOF expression {
    $$ = $1 + " instanceof " + $3;
  }
|  expression t_AS expression {
    $$ = $1 + " as " + $3;
  }
|  expression t_DOUBLE_ARROW expression {
    $$ = $1 + "=>" + $3;
  }
|  expression t_HEBREW_THING expression {
    $$ = $1 + "::" + $3;
  }
|  expression t_ARROW expression {
    $$ = $1 + "->" + $3;
  }
|  t_INCR expression {
    $$ = "++" + $2;
  }
|  t_DECR expression {
    $$ = "--" + $2;
  }
|  expression t_INCR {
    $$ = $1 + "++";
  }
|  expression t_DECR {
    $$ = $1 + "--";
  }
|  t_PLUS expression {
    $$ = "+" + $2;
  }
|  t_MINUS expression {
    $$ = "-" + $2;
  }
|  t_BIT_NOT expression {
    $$ = "~" + $2;
  }
|  t_NOT expression {
    $$ = "!" + $2;
  }
|  t_BIT_AND expression {
    $$ = "&" + $2;
  }
|  t_AT expression {
    $$ = "@" + $2;
  }
|  t_DOLLAR t_LCURLY expression t_RCURLY {
    $$ = "${" + $3 + "}";
  }
|  t_PRINT expression {
    $$ = "print " + $2;
  }
|  t_ECHO expression {
    $$ = "echo " + $2;
  }
|  t_CLONE expression {
    $$ = "clone " + $2;
  }
|  t_NEW expression {
    $$ = "new " + $2;
  }
|  t_THROW expression {
    $$ = "throw " + $2;
  }
|  t_REQ_ONCE expression {
    $$ = "require_once " + $2;
  }
|  t_REQ expression {
    $$ = "require " + $2;
  }
|  t_INC_ONCE expression {
    $$ = "include_once " + $2;
  }
|  t_INC expression {
    $$ = "include " + $2;
  }
;

// Declarations
many_fancy_delarations:
  fancy_delarations
|  many_fancy_delarations fancy_delarations {
    $$ = $1 + " " + $2;
  }
;

fancy_delarations:
  t_GLOBAL {
    $$ = cr("global");
  }
|  t_CONST {
    $$ = cr("const");
  }
|  t_PUBLIC {
    $$ = cr("public");
  }
|  t_PROTECTED {
    $$ = cr("protected");
  }
|  t_PRIVATE {
    $$ = cr("private");
  }
|  t_STATIC {
    $$ = cr("static");
  }
|  t_ABSTRACT {
    $$ = cr("abstract");
  }
|  t_FINAL {
    $$ = cr("final");
  }
;

declaration_statement:
  many_fancy_delarations expression_with_comma semicolon {
    $$ = $1 + " " + $2 + $3;
  }
;

// Functions
function_name:
  identifier
| t_BIT_AND identifier {
    $$ = "&" + $2;
  }
;

function:
  many_fancy_delarations function {
    $$ = $1 + " " + $2;
  }
|  t_FUNCTION function_name argument_list t_LCURLY statement_list t_RCURLY {
    $$ = "function " + $2 + $3 + " {" + $5 + "}";
  }
|  t_FUNCTION function_name argument_list semicolon {
    $$ = "function " + $2 + $3 + $4;
  }
;

// Classes
class_statement:
  t_CLASS classy_stuff t_LCURLY statement_list t_RCURLY {
    $$ = "class " + $2 + " {" + $4 +  "}";
  }
|  many_fancy_delarations t_CLASS classy_stuff t_LCURLY statement_list t_RCURLY {
    $$ = $1 + " class " + $3 + " {" + $5 +  "}";
  }
|  t_INTERFACE classy_stuff t_LCURLY statement_list t_RCURLY {
    $$ = "interface " + $2 + " {" + $4 +  "}";
  }
;

classy_stuff:
  /* empty */ {
    $$ = "";
  }
|  classy_stuff t_EXTENDS {
    $$ = $1 + cr(" extends ");
  }
|  classy_stuff t_IMPLEMENTS {
    $$ = $1 + cr(" implements ");
  }
|  classy_stuff identifier {
    $$ = $1 + " " + $2;
  }
|  classy_stuff t_COMMA {
    $$ = $1 + cr(", ");
  }
;
