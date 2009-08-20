#include "xhp_preprocess.hpp"
#include "xhp_parser.hpp"
#include <sstream>
using namespace std;

XHPResult xhp_preprocess(istream &in, string &out, bool isEval,
                         string &errDescription, uint32_t &errLineno) {

  // Does this maybe contain XHP?
  bool maybe_xhp = false;
  stringbuf sb;
  in >> &sb;
  string bufferS = sb.str();
  // need to end in double NULL for flex scan_buffer
  bufferS.reserve(bufferS.size() + 1);
  const char* buffer = bufferS.c_str();
  const_cast<char*>(buffer)[bufferS.size() + 1] = 0;
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

  // Early bail
  if (!maybe_xhp) {
    return XHPDidNothing;
  }

  // Run it through XHP parser
  int ret;
  void* scanner;
  code_rope buf;
  xhp_extra_type extra;
  extra.firsttoken = isEval ? t_PHP_FAKE_OPEN_TAG : 0;
  extra.terminated = false;
  extra.used = false;
  extra.docblock = NULL;
  xhplex_init(&scanner);
  xhpset_extra(&extra, scanner);

  // Parse the in-memory string
  XHPResult result;
  xhp_scan_buffer(const_cast<char*>(buffer), bufferS.size() + 2, scanner);
  ret = xhpparse(scanner, "", &buf);
  xhplex_destroy(scanner);
  extra.freeDocblock();
  if (!ret && extra.used) {
    result = XHPRewrote;
    out = buf.c_str();
  } else if (ret) {
    result = XHPErred;
    errDescription = extra.error;
    errLineno = extra.lineno;
  } else {
    result = XHPDidNothing;
  }
  return result;
}
