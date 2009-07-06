#include "xhp_parser.hpp"
#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <stdio.h>
using namespace std;

int main(int argc, char* argv[]) {
  bool in_place = false;
  vector<string> files;

  // Parse args
  for (int ii = 1; ii < argc; ++ii) {
    if (strcmp(argv[ii], "-i") == 0) {
      in_place = true;
    } else if (strcmp(argv[ii], "-h") == 0 || strcmp(argv[ii], "-?") == 0) {
      cerr<< argv[0] << " -i [files] | " << argv[0] << " [file]\n";
      return 1;
    } else {
      files.push_back(argv[ii]);
    }
  }

  // Sanity checking
  if (in_place && files.size() == 0) {
    cerr<< "In place mode must be used with at least one file.\n";
    return 1;
  } else if (!in_place && files.size() > 1) {
    cerr<< "Multiple files must be used with in place mode.\n";
    return 1;
  } else if (files.size() == 0) {
    files.push_back("-");
  }

  // Parse
  for (vector<string>::iterator ii = files.begin(); ii != files.end(); ++ii) {

    // Open this file
    // TODO: mmap would be much faster, i'm sure
    FILE* file = *ii == "-" ? stdin : fopen((*ii).c_str(), "r");

    // Read stream into memory
    std::string str;
    char buf[4096];
    size_t len;
    while ((len = fread(&buf, 1, 4095, file))) {
      buf[len] = 0;
      str += buf;
    }

    // Close the file
    if (*ii != "-") {
      fclose(file);
    }

    // Does this maybe contain XHP?
    bool maybe_xhp = false;
    const char* cstr = str.c_str();
    for (const char* jj = cstr; *jj; ++jj) {
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

    // Parse for XHP
    if (maybe_xhp) {

      // Init parser
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
      xhp_scan_string(cstr, scanner);
      int ret = xhpparse(scanner, (*ii).c_str(), &buf);

      // Free up memory
      xhplex_destroy(scanner);
      delete extra.xhp_tag_stack;

      // Results...
      if (ret) {
        cerr<< "Error parsing file `"<<(*ii)<<"`!!\n";
      } else if (extra.used) {
        FILE* output = in_place ? fopen((*ii).c_str(), "w") : stdout;
        const char* code = buf.c_str();
        fwrite(buf.c_str(), 1, strlen(code), output);
        if (in_place) {
          fclose(output);
        }
        cerr<< "File `"<<(*ii)<<"` xhpized.\n";
      }
    }
  }
  return 0;
}
