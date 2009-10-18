#include "xhp.hpp"
#include "xhp_preprocess.hpp"
#include "fastpath.hpp"
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
  xhp_flags_t flags;
  memset(&flags, 0, sizeof(xhp_flags_t));
  flags.eval = isEval;
  flags.short_tags = true;
  return xhp_preprocess(in, out, errDescription, errLineno, flags);
}

XHPResult xhp_preprocess(std::string &in, std::string &out, std::string &errDescription, uint32_t &errLineno, const xhp_flags_t &flags) {

  // Early bail if the code doesn't contain anything that looks like XHP
  char* buffer = const_cast<char*>(in.c_str());
  if (!xhp_fastpath(buffer, in.length(), flags)) {
    return XHPDidNothing;
  }

  // Create a flex buffer
  in.reserve(in.size() + 1);
  buffer = const_cast<char*>(in.c_str());
  buffer[in.size() + 1] = 0; // need double NULL for scan_buffer

  // Parse the PHP
  void* scanner;
  code_rope new_code;
  yy_extra_type extra;
  extra.idx_expr = flags.idx_expr;
  extra.insert_token = flags.eval ? T_OPEN_TAG_FAKE : 0;
  extra.short_tags = flags.short_tags;
  extra.asp_tags = flags.asp_tags;

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
