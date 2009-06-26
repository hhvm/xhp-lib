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
  #define yyterminate(s) yyerror(&yylloc, yyscanner, filename, root, s); yy_begin(TERMINATE);
  #define cr(s) code_rope(s, yylineno)
  extern int yydebug;
  static void yyerror(YYLTYPE* xhplloc, void* yyscanner, const char* filename, code_rope* str, const char* a) {
    xhp_extra_type* ex = static_cast<xhp_extra_type*>(xhpget_extra(yyscanner));
    if (ex->terminated) {
      return;
    }
    ex->terminated = true;

    CG(zend_lineno) = xhplloc->internal_line + xhplloc->actual_line_offset;
    zend_set_compiled_filename(const_cast<char*>(filename) TSRMLS_CC);
    *str = a;
    return;
  }
  void replacestr(std::string &source, const std::string &find, const std::string &rep) {
    size_t j; 
    while ((j = source.find(find)) != std::string::npos) {
      source.replace(j, find.length(), rep);
    }
  }
%}

%locations
%pure-parser
%parse-param { void* yyscanner }
%parse-param { const char* filename }
%parse-param { code_rope* root }
%lex-param { void* yyscanner }
%error-verbose
%expect 2 // i hate php's if syntax

// Keywords
%token BOGUS
%token t_IF t_ENDIF
%nonassoc p_IF
%left t_ELSEIF
%left t_ELSE
%token t_DO t_WHILE t_ENDWHILE t_FOR t_ENDFOR t_FOREACH t_ENDFOREACH
%token t_SWITCH t_ENDSWITCH t_CASE t_DEFAULT t_BREAK t_CONTINUE
%token t_FUNCTION t_RETURN
%token t_NEW t_CLONE
%token t_TRY
%nonassoc t_CATCH
%nonassoc p_CATCH
%token t_ABSTRACT t_FINAL t_PRIVATE t_PROTECTED t_PUBLIC t_VAR
%token t_CLASS t_INTERFACE t_EXTENDS t_IMPLEMENTS t_ELEMENT

// Literals
%token t_LITERAL_STRING t_EVALUATED_STRING t_SHELL_EXPRESSION
%token t_NUMBER
%token t_HEREDOC
%token t_ARRAY
%token t_XHP_TEXT
%token t_XHP_DIV t_XHP_LESS_THAN_DIV t_XHP_GREATER_THAN
%token t_XHP_WHITESPACE

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
| statement_list statement {
    $$ = $1 + $2;
  }
;

// Statements
statement:
  t_PHP_OPEN_TAG {
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
| t_LCURLY statement_list t_RCURLY {
    $$ = "{" + $2 + cr("}");
  }
| function_declaration
| if_statement
| while_statement
| for_statement
| foreach_statement
| switch_statement
| break_statement
| continue_statement
| return_statement
// TODO: global, static
| echo_statement
| t_INLINE_HTML
| expression_statement
| class_declaration
| try_statement

| declaration_statement
| semicolon
| xhp_element_declaration
;

semicolon:
  t_PHP_CLOSE_TAG {
    $$ = "?>";
  }
| t_SEMICOLON {
    $$ = ";";
  }
;

if_statement:
  t_IF t_LPAREN expression t_RPAREN statement {
    $$ = "if (" + $3 + ") " + $5;
  }
| if_statement t_ELSE statement {
    $$ = $1 + " else " + $3;
  }
| if_statement t_ELSEIF t_LPAREN expression t_RPAREN statement {
    $$ = $1 + " elseif (" + $4 + ") " + $6;
  }
| t_IF t_LPAREN expression t_RPAREN t_COLON statement_list elseif_list else_single t_ENDIF semicolon {
    $$ = "if (" + $3 + "): " + $6 + $7 + $8 + " endif" + $10;
  }
;

elseif_list:
  /* empty */ {
    $$ = "";
  }
| elseif_list t_ELSEIF t_LPAREN expression t_RPAREN t_COLON statement_list {
    $$ = $1 + " elseif(" + $4 + "):" + $7;
  }
;

else_single:
  /* empty */ {
    $$ = "";
  }
| t_ELSE statement_list {
    $$ = " else: " + $2;
  }
;

while_statement:
  t_WHILE t_LPAREN expression t_RPAREN statement {
    $$ = "while (" + $3 + ") " + $5;
  }
| t_WHILE t_LPAREN expression t_RPAREN t_COLON statement_list t_ENDWHILE {
    $$ = "while (" + $3 + ") {" + $6 + "}";
  }
| t_DO statement t_WHILE t_LPAREN expression t_RPAREN semicolon {
    $$ = "do " + $2 + " while (" + $5 + ")" + $7;
  }
;

for_statement: 
  t_FOR t_LPAREN for_expression t_SEMICOLON for_expression t_SEMICOLON for_expression t_RPAREN statement {
    $$ = "for (" + $3 + ";" + $5 + ";" + $7 + ") " + $9;
  }
| t_FOR t_LPAREN for_expression t_SEMICOLON for_expression t_SEMICOLON for_expression t_RPAREN t_COLON statement t_ENDFOR {
    $$ = "for (" + $3 + ";" + $5 + ";" + $7 + ") {" + $10 + "}";
  }
;

for_expression:
  /* empty */ {
    $$ = cr("");
  }
| expression_with_comma
;

foreach_statement: 
  t_FOREACH t_LPAREN expression t_AS expression foreach_optional_arg t_RPAREN statement {
    $$ = "foreach (" + $3 + " AS " + $5 + $6 + ") " + $8;
  }
| t_FOREACH t_LPAREN expression t_AS expression foreach_optional_arg t_RPAREN t_COLON statement_list t_ENDFOREACH {
    $$ = "foreach (" + $3 + " AS " + $5 + $6 + ") {" + $9 + "}";
  }
;

foreach_optional_arg:
  /* empty */ {
    $$ = cr("");
  }
| t_DOUBLE_ARROW expression {
    $$ = "=>" + $2;
  }
;

switch_statement:
  t_SWITCH t_LPAREN expression t_RPAREN switch_case_list {
    $$ = "switch (" + $3 + ") " + $5;
  }
;

switch_case_list:
  t_LCURLY case_list t_RCURLY {
    $$ = "{" + $2 + cr("}");
  }
| t_LCURLY semicolon case_list t_RCURLY {
    $$ = "{" + $2 + $3 + cr("}");
  }
| t_COLON case_list t_ENDSWITCH {
    $$ = "{" + $2 + "}";
  }
| t_COLON semicolon case_list t_ENDSWITCH {
    $$ = "{" + $2 + $3 + "}";
  }
;

case_list:
  /* empty */ {
    $$ = cr("");
  }
| case_list t_CASE expression case_separator statement_list {
    $$ = $1 + " case " + $3 + $4 + $5;
  }
| case_list t_DEFAULT case_separator statement_list {
    $$ = $1 + " default" + $3 + $4;
  }
;

case_separator:
  semicolon
| t_COLON {
    $$ = cr(":");
  }
;

break_statement:
  t_BREAK expression semicolon {
    $$ = "break " + $2 + $3;
  }
| t_BREAK semicolon {
    $$ = "break" + $2;
  }
;

continue_statement:
  t_CONTINUE expression semicolon {
    $$ = "continue" + $2 + $3;
  }
| t_CONTINUE semicolon {
    $$ = "continue" + $2;
  }
;

return_statement:
  t_RETURN expression semicolon {
    $$ = "return " + $2 + $3;
  }
| t_RETURN semicolon {
    $$ = cr("return") + $2;
  }
;

echo_statement:
  t_ECHO expression_with_comma semicolon {
    $$ = "echo " + $2 + $3;
  }
;

expression_statement:
  expression semicolon {
    $$ = $1 + $2;
  }
;

try_statement:
  t_TRY t_LCURLY statement_list t_RCURLY t_CATCH t_LPAREN identifier expression t_RPAREN t_LCURLY statement_list t_RCURLY additional_catches {
    $$ = "try { " + $3 + "} catch(" + $7 + " " + $8 + ") {" + $11 + "}" + $13;
  }
;

additional_catches:
  /* empty */ {
    $$ = "";
  }
| additional_catches t_CATCH t_LPAREN identifier expression t_RPAREN t_LCURLY statement_list t_RCURLY {
    $$ = $1 + "catch(" + $4 + " " + $5 + ") {" + $8 + cr("}");
  }
;

// Argument list
argument_list:
  t_LPAREN t_RPAREN {
    $$ = cr("()");
  }
| t_LPAREN _argument_list t_RPAREN {
    $$ = "(" + $2 + ")";
  }
| t_LPAREN _argument_list t_COMMA t_RPAREN {
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
| _argument_list t_COMMA expression {
    $$ = $1 + "," + $3;
  }
| _argument_list t_COMMA {
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
| t_EVALUATED_STRING {
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
| string_literal
| heredoc_literal
;

identifier:
  t_IDENTIFIER {
    $$ = cr($1);
  }
;

expression_with_comma:
  expression
| expression_with_comma t_COMMA expression {
    $$ = $1 + "," + $3;
  }
;

variables_and_stuff:
  literal_expression
| t_SHELL_EXPRESSION
| identifier
| xhp_expression
| expression t_LBRACKET expression t_RBRACKET {
    $$ = $1 + "[" + $3 + "]";
  }
| expression t_ARROW t_LCURLY expression t_RCURLY {
    $$ = $1 + "->{" + $4 + "}";
  }
;

expression:
  variables_and_stuff
| variables_and_stuff argument_list {
    $$ = $1 + $2;
  }
| identifier identifier {
    $$ = $1 + " " + $2;
  }
| t_ARRAY identifier {
    $$ = "array " + $2;
  }
| t_ARRAY t_BIT_AND identifier {
    // handles function foo(array &bar){}
    $$ = "array &" + $3;
  }
| t_ARRAY t_LPAREN array_pair_list t_RPAREN {
    $$ = "array(" + $3 + ")";
  }
| t_LPAREN expression t_RPAREN {
    $$ = "(" + $2 + ")";
  }
| t_LPAREN expression t_RPAREN expression {
    $$ = "(" + $2 + ")" + $4;
  }
| t_LPAREN t_ARRAY t_RPAREN expression {
    $$ = "(array)" + $4;
  }
| expression t_LCURLY expression t_RCURLY {
    $$ = $1 + "{" + $3 + "}";
  }
| expression t_LBRACKET t_RBRACKET {
    $$ = $1 + "[]";
  }
| expression t_PLING expression t_COLON expression {
    $$ = $1 + " ? " + $3 + " : " + $5;
  }
| expression t_ASSIGN expression {
    $$ = $1 + "=" + $3;
  }
| expression t_APPEND expression {
    $$ = $1 + ".=" + $3;
  }
| expression t_PLUS_ASSIGN expression {
    $$ = $1 + "+=" + $3;
  }
| expression t_MINUS_ASSIGN expression {
    $$ = $1 + "-=" + $3;
  }
| expression t_DIV_ASSIGN expression {
    $$ = $1 + "/=" + $3;
  }
| expression t_MULT_ASSIGN expression {
    $$ = $1 + "*=" + $3;
  }
| expression t_MOD_ASSIGN expression {
    $$ = $1 + "%=" + $3;
  }
| expression t_BIT_AND_ASSIGN expression {
    $$ = $1 + "&=" + $3;
  }
| expression t_BIT_OR_ASSIGN expression {
    $$ = $1 + "|=" + $3;
  }
| expression t_BIT_XOR_ASSIGN expression {
    $$ = $1 + "^=" + $3;
  }
| expression t_LSHIFT_ASSIGN expression {
    $$ = $1 + "<<=" + $3;
  }
| expression t_RSHIFT_ASSIGN expression {
    $$ = $1 + ">>=" + $3;
  }
| expression t_OR expression {
    $$ = $1 + "||" + $3;
  }
| expression t_AND expression {
    $$ = $1 + "&&" + $3;
  }
| expression t_BIT_OR expression {
    $$ = $1 + "|" + $3;
  }
| expression t_BIT_AND expression {
    $$ = $1 + "&" + $3;
  }
| expression t_BIT_XOR expression {
    $$ = $1 + "^" + $3;
  }
| expression t_LOGICAL_OR expression {
    $$ = $1 + " OR " + $3;
  }
| expression t_LOGICAL_XOR expression {
    $$ = $1 + " XOR " + $3;
  }
| expression t_LOGICAL_AND expression {
    $$ = $1 + " AND " + $3;
  }
| expression t_EQUAL expression {
    $$ = $1 + "==" + $3;
  }
| expression t_NOT_EQUAL expression {
    $$ = $1 + "!=" + $3;
  }
| expression t_STRICT_EQUAL expression {
    $$ = $1 + "===" + $3;
  }
| expression t_STRICT_NOT_EQUAL expression {
    $$ = $1 + "!==" + $3;
  }
| expression t_LESS_THAN_EQUAL expression {
    $$ = $1 + "<=" + $3;
  }
| expression t_GREATER_THAN_EQUAL expression {
    $$ = $1 + ">=" + $3;
  }
| expression t_LESS_THAN expression {
    $$ = $1 + "<" + $3;
  }
| expression t_GREATER_THAN expression {
    $$ = $1 + ">" + $3;
  }
| expression t_LSHIFT expression {
    $$ = $1 + "<<" + $3;
  }
| expression t_RSHIFT expression {
    $$ = $1 + ">>" + $3;
  }
| expression t_PLUS expression {
    $$ = $1 + "+" + $3;
  }
| expression t_MINUS expression {
    $$ = $1 + "-" + $3;
  }
| expression t_MULT expression {
    $$ = $1 + "*" + $3;
  }
| expression t_DIV expression {
    $$ = $1 + "/" + $3;
  }
| expression t_MOD expression {
    $$ = $1 + "%" + $3;
  }
| expression t_CONCAT expression {
    $$ = $1 + " . " + $3;
  }
| expression t_INSTANCEOF expression {
    $$ = $1 + " instanceof " + $3;
  }
| expression t_HEBREW_THING expression {
    $$ = $1 + "::" + $3;
  }
| expression t_ARROW expression {
    // Need -> in the rope because "$foo-> if()" is a syntax error, but if you remove the space it's not.
    $$ = $1 + cr("->") + $3;
  }
| t_INCR expression {
    $$ = "++" + $2;
  }
| t_DECR expression {
    $$ = "--" + $2;
  }
| expression t_INCR {
    $$ = $1 + "++";
  }
| expression t_DECR {
    $$ = $1 + "--";
  }
| t_PLUS expression {
    $$ = "+" + $2;
  }
| t_MINUS expression {
    $$ = "-" + $2;
  }
| t_BIT_NOT expression {
    $$ = "~" + $2;
  }
| t_NOT expression {
    $$ = "!" + $2;
  }
| t_BIT_AND expression {
    $$ = "&" + $2;
  }
| t_AT expression {
    $$ = "@" + $2;
  }
| t_DOLLAR t_LCURLY expression t_RCURLY {
    $$ = "${" + $3 + "}";
  }
| t_PRINT expression {
    $$ = "print " + $2;
  }
| t_CLONE expression {
    $$ = "clone " + $2;
  }
| t_NEW expression {
    $$ = "new " + $2;
  }
| t_THROW expression {
    $$ = "throw " + $2;
  }
| t_REQ_ONCE expression {
    $$ = "require_once " + $2;
  }
| t_REQ expression {
    $$ = "require " + $2;
  }
| t_INC_ONCE expression {
    $$ = "include_once " + $2;
  }
| t_INC expression {
    $$ = "include " + $2;
  }
;

array_pair_list:
  /* empty */ {
    $$ = cr("");
  }
| array_pair_list_real
| array_pair_list_real t_COMMA
;

array_pair_list_real:
  array_pair_list_real t_COMMA expression t_DOUBLE_ARROW expression {
    $$ = $1 + "," + $3 + "=>" + $5;
  }
| array_pair_list_real t_COMMA expression {
    $$ = $1 + "," + $3;
  }
| expression t_DOUBLE_ARROW expression {
    $$ = $1 + "=>" + $3;
  }
| expression
;

// Declarations
many_fancy_delarations:
  fancy_delarations
| many_fancy_delarations fancy_delarations {
    $$ = $1 + " " + $2;
  }
;

fancy_delarations:
  t_GLOBAL {
    $$ = cr("global");
  }
| t_CONST {
    $$ = cr("const");
  }
| t_PUBLIC {
    $$ = cr("public");
  }
| t_PROTECTED {
    $$ = cr("protected");
  }
| t_PRIVATE {
    $$ = cr("private");
  }
| t_STATIC {
    $$ = cr("static");
  }
| t_ABSTRACT {
    $$ = cr("abstract");
  }
| t_FINAL {
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

function_declaration:
  t_FUNCTION function_name argument_list t_LCURLY statement_list t_RCURLY {
    $$ = "function " + $2 + $3 + " {" + $5 + cr("}");
  }
| t_FUNCTION function_name argument_list semicolon {
    $$ = "function " + $2 + $3 + $4;
  }
;

// Classes
class_declaration:
  class_entry identifier class_extends class_implements t_LCURLY class_statement_list t_RCURLY {
    $$ = $1 + " " + $2 + " " + $3 + " " + $4 + "{" + $6 + cr("}");
  }
| t_INTERFACE identifier interface_extends t_LCURLY class_statement_list t_RCURLY {
    $$ = "interface " + $2 + " " + $3 + "{" + $5 + cr("}");
  }
;

class_entry:
  t_CLASS {
    $$ = cr("class");
  }
| t_ABSTRACT t_CLASS {
    $$ = cr("abstract class");
  }
| t_FINAL t_CLASS {
    $$ = cr("final class");
  }
;

class_extends:
  /* empty */ {
    $$ = "";
  }
| t_EXTENDS identifier {
    $$ = "extends " + $2;
  }
;

interface_extends:
  /* empty */ {
    $$ = "";
  }
| t_EXTENDS class_implements_list {
    $$ = "extends " + $2;
  }
;

class_implements:
  /* empty */ {
    $$ = "";
  }
| t_IMPLEMENTS class_implements_list {
    $$ = "implements " + $2;
  }
;

class_implements_list:
  identifier
| class_implements_list t_COMMA identifier {
    $$ = $1 + "," + $3;
  }
;

class_statement_list:
  /* empty */ {
    $$ = "";
  }
| class_statement_list class_statement {
    $$ = $1 + $2;
  }
;

class_statement:
  class_variable_modifier expression_with_comma semicolon {
    $$ = $1 + " " + $2 + $3;
  }
| t_CONST expression_with_comma semicolon {
    $$ = "const " + $2 + $3;
  }
| class_member_modifiers function_declaration {
    $$ = $1 + " " + $2;
  }
| function_declaration
;

class_variable_modifier:
  t_VAR {
    $$ = cr("var");
  }
| class_member_modifiers
;

class_member_modifiers:
  class_member_modifier
| class_member_modifiers class_member_modifier {
    $$ = $1 + " " + $2;
  }
;

class_member_modifier:
  t_PUBLIC {
    $$ = cr("public");
  }
| t_PROTECTED {
    $$ = cr("protected");
  }
| t_PRIVATE {
    $$ = cr("private");
  }
| t_STATIC {
    $$ = cr("static");
  }
| t_ABSTRACT {
    $$ = cr("abstract");
  }
| t_FINAL {
    $$ = cr("final");
  }
;

//
// XHP extensions

// high-level expressions
xhp_expression:
  xhp_singleton
| xhp_open_tag xhp_children xhp_close_tag {
    $$ = $1 + $2 + $3;
  }
;

xhp_children:
  xhp_children_ {
    if ($1.back() == ',') {
      $$ = "array(" + $1 + ")";
    } else {
      $$ = "array()";
    }
  }
;

xhp_children_:
  /* empty */ {
    $$ = cr("");
  }
| xhp_literal_text {
    yy_begin(XHP_CHILD_START);
    $$ = "'" + $1 + "',";
  }
| xhp_children_ xhp_child {
    yy_begin(XHP_CHILD_START);
    $$ = $1 + $2 + ",";
  }
| xhp_children_ xhp_child xhp_literal_text {
    yy_begin(XHP_CHILD_START);
    $$ = $1 + $2 + ",'" + $3 + "',";
  }
;

xhp_child:
  xhp_expression
| t_LCURLY { yy_push_state(PHP); } expression t_RCURLY { yy_pop_state(); } {
    $$ = $3;
  }
;

// attributes
xhp_attributes:
  /* empty */ {
    $$ = cr("");
    yy_push_state(XHP_ATTR);
  }
| xhp_attributes xhp_attribute {
    $$ = $1 + $2 + ",";
  }
;

xhp_attribute:
  xhp_label xhp_whitespace_hack t_ASSIGN xhp_attribute_value {
    $$ = "'" + $1 + "' => " + $4;
  }
;

xhp_attribute_value:
  t_DOUBLE_QUOTE { yy_push_state(XHP_ATTR_VAL); /* pop'd in the scanner on double quote */ } xhp_literal_text t_DOUBLE_QUOTE {
    $$ = "'" + $3 + "'";
  }
| t_LCURLY { yy_push_state(PHP); } expression { yy_pop_state(); } t_RCURLY {
    $$ = $3;
  }
;

// tags
xhp_tag_start:
  xhp_lt xhp_label xhp_whitespace_hack {
    yy_pop_state();
    $$ = $2;
  }
;

xhp_singleton:
  xhp_tag_start xhp_attributes t_XHP_DIV t_XHP_GREATER_THAN {
    yy_pop_state(); // XHP_ATTR
    $$ = "new xhp_" + $1 + "(array(" + $2 + "), array())";
  }
;

xhp_open_tag:
  xhp_tag_start xhp_attributes t_XHP_GREATER_THAN {
    yy_pop_state(); // XHP_ATTR
    yy_push_state(XHP_CHILD_START);
    static_cast<xhp_extra_type*>(xhpget_extra(yyscanner))->xhp_tag_stack->push($1.c_str());
    $$ = "new xhp_" + $1 + "(array(" + $2 + "), ";
  }
;

xhp_close_tag:
  t_XHP_LESS_THAN_DIV { yy_push_state(XHP_LABEL); } xhp_label t_XHP_GREATER_THAN {
    yy_pop_state(); // XHP_LABEL
    yy_pop_state(); // XHP_CHILD_START
    xhp_extra_type* ex = static_cast<xhp_extra_type*>(xhpget_extra(yyscanner));
    if (ex->xhp_tag_stack->top() != $3.c_str()) {
      std::string e1 = $3.c_str();
      std::string e2 = ex->xhp_tag_stack->top();
      replacestr(e1, "__", ":");
      replacestr(e1, "_", "-");
      replacestr(e2, "__", ":");
      replacestr(e2, "_", "-");
      std::string e = std::string("mismatched tag </") + e1 + ">; expecting </" + e2 +">";
      yyterminate(e.c_str());
    }
    ex->xhp_tag_stack->pop();
    $$ = ")";
  }
;

// misc
xhp_literal_text:
  t_XHP_TEXT
| xhp_literal_text t_XHP_TEXT {
    $$ = $1 + $2;
  }
;

xhp_label:
  t_IDENTIFIER {
    // this gets pop'd in the scanner on " ", ">", "/>", or "="
    yy_push_state(XHP_LABEL);
    $$ = $1;
  }
| xhp_label t_COLON t_IDENTIFIER {
    $$ = $1 + "__" + $3;
  }
| xhp_label t_MINUS t_IDENTIFIER {
    $$ = $1 + "_" + $3;
  }
;

xhp_lt:
  t_LESS_THAN {
    $$ = cr("");
    yy_push_state(XHP_LABEL);
  }
;

xhp_whitespace_hack:
  /* empty */
| t_XHP_WHITESPACE
;

// element declarations
xhp_element_declaration:
  xhp_element_entry { yy_push_state(PHP_NO_RESERVED_WORDS); } xhp_label xhp_whitespace_hack xhp_element_extends xhp_element_implements t_LCURLY class_statement_list t_RCURLY {
    $$ = $1 + $3 + " " + $5 + " " + $6 + "{" + $8 + cr("}");
  }
;

xhp_element_entry:
  t_ELEMENT {
    $$ = cr("class xhp_");
  }
| t_ABSTRACT t_ELEMENT {
    $$ = cr("abstract class xhp_");
  }
;

xhp_element_extends:
  /* empty */ {
    $$ = "extends XHPCore";
  }
| t_EXTENDS xhp_label xhp_whitespace_hack {
    $$ = "extends xhp_" + $2;
  }
;

xhp_element_implements:
  /* empty */ {
    $$ = "";
  }
| t_IMPLEMENTS xhp_element_implements_list {
    $$ = "implements " + $2;
  }
;

xhp_element_implements_list:
  xhp_label xhp_whitespace_hack
| xhp_element_implements_list t_COMMA xhp_label xhp_whitespace_hack {
    $$ = $1 + "," + $3;
  }
;

%%

const char* yytokname(int tok) {
  if (tok < 255) {
    return "?";
  }
  return yytname[tok - 255];
}
