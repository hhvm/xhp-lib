#include <iostream>
#include <string>

enum XHPResult {
  XHPDidNothing,
  XHPRewrote,
  XHPErred
};

XHPResult xhp_preprocess(std::istream &in, std::string &out,
                         std::string &errDescription, uint32_t &errLineno);
