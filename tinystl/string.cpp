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
  // Substring: create a copy of the range (f,l]
  _string(const_iterator f, const_iterator l):vector<T>(l-f) { copy(f, l, b); }

  int length() const { return n; }

  char* c_str() {
    reserve(n+1);
    b[n] = 0;
    return b;
  }

  istream& read(istream& i, char* delims = " \t\n") {
    char c;
    clear();
    while ((c = i.peek()) != EOF && !strchr(delims, c)) push_back(i.get());
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

  _string substr(int s, int l=-1) { return _string(b+s, (l==-1 ? b+n : b+s+l)); }
};

typedef _string<char> string;


template <class T>
ostream& operator<<(ostream& o, const _string<T>& s) {
  // String is not necessarily null-terminated.
  for (T* i = s.b; i < s.b + s.n; ++i)
    o << *i;
  return o;
}


template <class T>
istream& operator>>(istream& i, _string<T>& s) { i >> ws; return s.read(i); }

template<class T>
istream& getline(istream& i, _string<T>& s) { return s.read(i, "\n").ignore();}
