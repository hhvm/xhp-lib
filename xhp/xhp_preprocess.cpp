#include "xhp.hpp"
#include "xhp_preprocess.hpp"
#include <sstream>
using namespace std;
extern int xhpdebug;
#include <iostream>
XHPResult xhp_preprocess(istream &in, string &out, bool isEval, string &errDescription, uint32_t &errLineno) {

  // Read stream to string
  stringbuf sb;
  in >> noskipws >> &sb;
  string buffer = sb.str();
  return xhp_preprocess(buffer, out, isEval, errDescription, errLineno);
}

XHPResult xhp_preprocess(string &in, string &out, bool isEval, string &errDescription, uint32_t &errLineno) {

  // Create a flex buffer
  in.reserve(in.size() + 1);
  char* buffer = const_cast<char*>(in.c_str());
  buffer[in.size() + 1] = 0; // need double NULL for scan_buffer

  // Does this maybe contain XHP?
/*
  bool maybe_xhp = false;
  for (const char* jj = buffer; *jj; ++jj) {
    if (*jj == '<') { // </a>
      if (jj[1] == '/') {
        maybe_xhp = true;
        break;
      }
    } else if (*jj == '/') { // <a />
      if (jj[1] == '>') {
        maybe_xhp = true;
        break;
      }
    } else if (!memcmp(jj, "element", 7)) {
      maybe_xhp = true;
      break;
    }
  }
*/
  bool maybe_xhp = true;

  // Early bail
  if (!maybe_xhp) {
    return XHPDidNothing;
  }

  // Parse the PHP
  void* scanner;
  code_rope new_code;
  yy_extra_type extra;
  extra.insert_token = isEval ? T_OPEN_TAG_FAKE : 0;
  xhplex_init(&scanner);
  xhpset_extra(&extra, scanner);
  xhp_scan_buffer(buffer, in.size() + 2, scanner);
#ifdef DEBUG
  xhpdebug = 1;
#endif
  xhpparse(scanner, &new_code);
  xhplex_destroy(scanner);

  // Check to see what happened
  if (extra.terminated) {
    errDescription = extra.error;
    errLineno = extra.lineno;
    return XHPErred;
  } else if (!extra.used) {
    return XHPDidNothing;
  } else {
    out = new_code.c_str();
    return XHPRewrote;
  }
}
