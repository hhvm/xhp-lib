#include <iostream>
#include <string>
#include <stdint.h>

enum XHPResult {
  XHPDidNothing,
  XHPRewrote,
  XHPErred
};

XHPResult xhp_preprocess(std::istream &in, std::string &out, bool isEval,
                         std::string &errDescription, uint32_t &errLineno);
