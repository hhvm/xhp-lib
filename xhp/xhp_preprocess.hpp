#pragma once
#include <iostream>
#include <string>
#include <stdint.h>

enum XHPResult {
  XHPDidNothing,
  XHPRewrote,
  XHPErred
};

struct xhp_flags_t {
  bool asp_tags;
  bool short_tags;
  bool idx_expr;
  bool include_debug;
  bool eval;
};

XHPResult xhp_preprocess(std::istream &in, std::string &out, bool isEval,
                         std::string &errDescription, uint32_t &errLineno);

XHPResult xhp_preprocess(std::string &in, std::string &out, bool isEval,
                         std::string &errDescription, uint32_t &errLineno);

XHPResult xhp_preprocess(std::string &in, std::string &out,
                         std::string &errDescription, uint32_t &errLineno,
                         const xhp_flags_t &flags);
