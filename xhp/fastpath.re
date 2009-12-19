#include "fastpath.hpp"
#include <stdio.h>

bool xhp_fastpath(const char* yy, const size_t len, const xhp_flags_t &flags) {
  const char* YYMARKER = NULL;
  enum {
    HTML,
    PHP,
    COMMENT_EOL,
    COMMENT_BLOCK
  } state = flags.eval ? PHP : HTML;

  #define YYCURSOR yy
  #define YYCTYPE char
  #define YYGETCONDITION() state
  #define YYFILL(ii)
  #define YYDEBUG(s, c) printf("%03d: %c [%d]\n", s, c, c)

  for (;;) {
/*!re2c
    re2c:condenumprefix = "";
    re2c:yyfill:check = 0;

    NEWLINE = ('\r'|'\n'|'\r\n');
    WHITESPACE = [ \n\r\t]+;

    <*> "\x00" { return false; }
    <*> [^\x00] { continue; }

    <HTML> '<?php'([ \t]|NEWLINE) {
      state = PHP;
      continue;
    }
    <HTML> '<?='|'<?' {
      if (flags.short_tags) {
        state = PHP;
      }
      continue;
    }
    <HTML> '<%='|'<%' {
      if (flags.asp_tags) {
        state = PHP;
      }
      continue;
    }

    <PHP> '?>'|'</script'WHITESPACE*'>' {
      state = HTML;
      continue;
    }
    <PHP> '%>' {
      if (flags.asp_tags) {
        state = PHP;
      }
      continue;
    }
    <PHP> 'b'?'\''('\\'.|'\\\n'|[^\x00\\']+)*'\''|
          'b'?'\"'('\\'.|'\\\n'|[^\x00\\"]+)*'\"' { continue; }
    <PHP> '#'|'//' {
      state = COMMENT_EOL;
      continue;
    }
    <PHP> '/*' {
      state = COMMENT_BLOCK;
      continue;
    }
    <PHP> '::' { continue; }
    <PHP> '</'|
          '/>'|
          ':'[a-zA-Z0-9]|
          ')'WHITESPACE*'['|
          '&#' {
      return true;
    }

    <COMMENT_EOL> NEWLINE {
      state = PHP;
      continue;
    }
    <COMMENT_EOL> '?>' {
      state = HTML;
      continue;
    }

    <COMMENT_BLOCK> [^*\x00] { continue; }
    <COMMENT_BLOCK> '*/' {
      state = PHP;
      continue;
    }
*/
  }
  return false;
}
