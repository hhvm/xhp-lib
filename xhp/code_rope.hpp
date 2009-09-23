#include <string>
#include <ext/rope>

class code_rope {
  protected:
    __gnu_cxx::rope<char> str;
    size_t lf; /* how many line breaks this code contains */
    size_t no; /* line number this code starts on */
  
  public:
    code_rope(const __gnu_cxx::rope<char> = "", const size_t = 0, const size_t = 0);
    code_rope(const code_rope&, const size_t = 0, const size_t = 0);
    const char* c_str() const;
    void prepend(const char* str);
    const char back() const;
    void pop_back();
    void strip_lines();
    code_rope operator+(const code_rope& right) const;
    code_rope operator+(const char*) const;
    code_rope& operator=(const char*);
};
code_rope operator+(const char*, const code_rope&);
