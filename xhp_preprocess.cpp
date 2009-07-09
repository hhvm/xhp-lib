#include "xhp_preprocess.hpp"
#include "xhp_parser.hpp"
#include <sstream>
using namespace std;

XHPResult xhp_preprocess(istream &in, string &out, string &errDescription,
                         uint32_t &errLineno) {
  // Does this maybe contain XHP?
  bool maybe_xhp = false;
  stringbuf sb;
  in >> &sb;
  string bufferS = sb.str();
  const char* buffer = bufferS.c_str();
  for (const char* jj = buffer; *jj; ++jj) {
    if (*jj == '<') { // </a>
      if (jj[1] == '/') {
        maybe_xhp = 1;
        break;
      }
    } else if (*jj == '/') { // <a />
      if (jj[1] == '>') {
        maybe_xhp = 1;
        break;
      }
    } else if (!memcmp(jj, "element", 7)) {
      maybe_xhp = 1;
      break;
    }
  }

  XHPResult result = XHPDidNothing;
  if (maybe_xhp) {
    int ret;
    void* scanner;
    code_rope buf;
    xhp_extra_type extra;
    extra.firsttoken = 0;
    extra.xhp_tag_stack = new stack<string>();
    extra.terminated = false;
    extra.used = false;
    xhplex_init(&scanner);
    xhpset_extra(&extra, scanner);

    // Parse the in-memory string
    xhp_scan_string(buffer, scanner);
    ret = xhpparse(scanner, "", &buf);
    xhplex_destroy(scanner);
    delete extra.xhp_tag_stack;
    if (!ret && extra.used) {
      result = XHPRewrote;
      out = buf.c_str();
    } else if (ret) {
      result = XHPErred;
      // TODO
      errDescription = "Unknown parse error.";
      errLineno = 1;
    }
  }
  return result;
}
