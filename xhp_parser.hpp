#pragma once

#include <stdint.h>
#include <stdio.h>
#include <string>
#include <deque>
#include "code_rope.hpp"

#define YYSTYPE code_rope

#define YY_HEADER_EXPORT_START_CONDITIONS

class xhp_extra_type {
public:
  xhp_extra_type() { pushStack(); }
  // public
  int firsttoken; // first token to return to parser. use t_PHP_FAKE_OPEN_TAG for eval'd code.
  bool terminated; // becomes true when the parser terminates with an error
  int lineno; // line number (used for early termination)
  std::string error; // description of error
  bool used; // was any xhp even used in this code?

  // internal book-keeping
  char* heredoc_eom;
  size_t heredoc_eom_len;
  char* heredoc_data_start;
  char* heredoc_data_last;

  bool haveTag() { return !xhp_tag_stack.front().empty(); }
  const std::string &peekTag() { return xhp_tag_stack.front().front(); }
  void pushTag(const std::string &tag) { xhp_tag_stack.front().push_front(tag); }
  void popTag() {xhp_tag_stack.front().pop_front(); }
  void pushStack() { xhp_tag_stack.push_front(std::deque<std::string>()); }
  void popStack() { xhp_tag_stack.pop_front(); }

private:
  std::deque<std::deque<std::string> > xhp_tag_stack;
};
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
