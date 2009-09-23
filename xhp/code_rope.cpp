#include "code_rope.hpp"
using namespace std;

code_rope::code_rope(const __gnu_cxx::rope<char> str, const size_t no /* = 0 */, const size_t lf /* = 0 */) : str(str), lf(lf), no(no) {}

code_rope::code_rope(const code_rope& str, const size_t no /* = 0 */, const size_t lf /* = 0 */) : str(str.str), lf(lf), no(no) {
  if (str.lf || str.no) {
    if (!no && !lf) {
      this->lf = str.lf;
      this->no = str.no;
    } else {
      throw new std::exception();
    }
  } else {
    this->no = no;
    this->lf = lf;
  }
}

const char* code_rope::c_str() const {
  if (0 && this->no > 1) {
    return NULL;
    // lolololololol
    // this code is clowntown -- returns dealloced memory
    __gnu_cxx::rope<char> whitespace(this->no - 1, '\n');
    whitespace += this->str;
    return whitespace.c_str();
  } else {
    return this->str.c_str();
  }
}

void code_rope::prepend(const char* str) {
  this->str = __gnu_cxx::rope<char>(str) + this->str;
}

const char code_rope::back() const {
  return this->str.empty() ? 0 : this->str.back();
}

void code_rope::pop_back() {
  this->str.pop_back();
}

void code_rope::strip_lines() {
  lf = no = 0;
}

code_rope code_rope::operator+(const code_rope& right) const {
  size_t diff;
  size_t no, lf;
  __gnu_cxx::rope<char> glue;
  if (this->no && right.no) {
    no = this->no;
    if (right.no > this->no + this->lf) {
      diff = right.no - this->no - this->lf;
      lf = this->lf + right.lf + diff;
      glue = __gnu_cxx::rope<char>(diff, '\n');
    } else {
      no = this->no;
      lf = this->lf + right.lf;
    }
  } else if (right.no) {
    no = right.no;
    lf = this->lf + right.lf;
  } else {
    no = this->no;
    lf = this->lf + right.lf;
  }
  return code_rope(this->str + glue + right.str, no, lf);
}

code_rope code_rope::operator+(const char* right) const {
  return code_rope(this->str + right, this->no, this->lf);
}

code_rope& code_rope::operator=(const char* str) {
  this->str = str;
  this->no = this->lf = 0;
  return *this;
}

code_rope operator+(const char* left, const code_rope& right) {
  code_rope ret(right);
  ret.prepend(left);
  return ret;
}
