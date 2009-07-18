#pragma once

#include <stdint.h>
#include <stdio.h>
#include <string>
#include <stack>
#include "code_rope.hpp"

#define YYSTYPE code_rope

#define YY_HEADER_EXPORT_START_CONDITIONS

typedef struct {
  // internal book-keeping
  char* heredoc_eom;
  size_t heredoc_eom_len;
  char* heredoc_data_start;
  char* heredoc_data_last;
  std::stack<std::string>* xhp_tag_stack;
  // public
  int firsttoken; // first token to return to parser. use t_PHP_FAKE_OPEN_TAG for eval'd code.
  bool terminated; // becomes true when the parser terminates with an error
  int lineno; // line number (used for early termination)
  std::string error; // description of error
  bool used; // was any xhp even used in this code?
} xhp_extra_type;
#define YY_EXTRA_TYPE xhp_extra_type*

#define YYLTYPE_IS_DECLARED
typedef struct YYLTYPE {
  int internal_line;
  int actual_line_offset;
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;


void flexBEGIN(int, void*);
void flex_push_state(int, void*);
void flex_pop_state(void*);

#include "xhp_parser.yacc.hpp"
#ifndef FLEX_SCANNER
// You can't include flex's header from within flex or shit goes to hell
#include "xhp_scanner.lex.hpp"
#define yy_push_state(a) flex_push_state(a, yyscanner);
#define yy_pop_state() flex_pop_state(yyscanner);
#define yy_begin(a) flexBEGIN(a, yyscanner);
#endif

extern int xhpdebug;
int xhpparse(void*, const char*, code_rope*);
YY_EXTRA_TYPE xhpget_extra(void* scanner);
#ifndef FLEX_SCANNER
void* xhp_scan_string(const char *yy_str, void* yyscanner); // will scan a copy of the string
void* xhp_scan_buffer(char *yy_str, yy_size_t size, void* yyscanner); // will modify yy_str, but avoids a strcpy
#endif
