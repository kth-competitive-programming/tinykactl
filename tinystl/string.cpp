/* KTH ACM Contest Template Library
 *
 * tinystl/string
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By Per Austrin
 */


#include <ctype.h>
#include <string.h>
#include <iostream>
#include "vector.cpp"

template <class T>
struct _string: public vector<T> {
  _string(int i = 0): vector<T>(i) {}
  _string(const char* s): vector<T>(strlen(s)) { copy(s, s+n, b); }

  int length() { return n; }

  char* c_str() {
    reserve(n+1);
    b[n] = 0;
    return b;
  }

  istream& read(istream& i, char* delims = "\n") {
    char c;
    clear();
    while ((c = i.get()) != EOF && !strchr(delims, c)) push_back(c);
    return i;
  }

  int cmp(const _string &s) const {
    for (int i = 0; i < (n < s.n ? n : s.n); ++i)
      if (b[i] != s.b[i])
	return b[i] - s.b[i];
    return n - s.n;
  }

  bool operator<(const _string& s) const { return cmp(s) < 0; }
  bool operator==(const _string& s) const { return !cmp(s); }

  _string operator+(const _string& s) {
    _string r(n + s.n);
    copy(b, b+n, r.b);
    copy(s.b, s.b+s.n, r.b+n);
    return r;
  }
};

typedef _string<char> string;


template <class T>
ostream& operator<<(ostream& o, const _string<T>& s) {
  // String is not necessarily null-terminated.
  for (T* i = s.b; i < s.b + s.n; ++i)
    o << *i;
}


template <class T>
istream& operator>>(istream& i, _string<T>& s) { return s.read(i, " \t\n"); }

template<class T>
istream& getline(istream& i, _string<T>& s) { return s.read(i); }
