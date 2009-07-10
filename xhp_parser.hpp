#pragma once

#include <stdint.h>
#include <stdio.h>
#include <string>
#include <stack>
#include "code_rope.hpp"

#define YYSTYPE code_rope

#define YY_HEADER_EXPORT_START_CONDITIONS

typedef struct {
  int firsttoken;
  char* heredoc_eom;
  size_t heredoc_eom_len;
  char* heredoc_data_start;
  char* heredoc_data_last;
  bool terminated;
  bool used;
  std::stack<std::string>* xhp_tag_stack;
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
void* xhp_scan_string(const char *yy_str, void* yyscanner);
#endif
