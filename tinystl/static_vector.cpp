/* KTH ACM Contest Template Library
 *
 * tinystl/static vector
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By Per Austrin
 */

#include "copy.cpp"

template<class T, int M>
struct vector {
  T b[M]; int n;

  typedef T value_type;
  typedef T *iterator;
  typedef const T *const_iterator;
  typedef vector S;
  
  vector(int _n=0, const T &val=T()): n(_n) { fill(b, b+n, val); }
  
  T *begin() { return b; }
  T *end() { return b+n; }
  const T *begin() const { return b; }
  const T *end() const { return b+n; }
  int size() { return n; }
  
  T &front() { return b[0]; }
  const T &front() const { return b[0]; }
  T &back() { return b[n-1]; }
  const T &back() const { return b[n-1]; }
  
  T &operator[](int k) { return b[k]; }
  const T &operator[](int k) const { return b[k]; }
  
  void push_back(const T &v) { b[n++] = v; }
  void pop_back() { --n; }
  // The insert methods may be ignored if they are not used.
  T *insert(T *pos, const T &v) { return insert(pos, 1, v); }
  T *insert(T *pos, int num, const T &v) {
    copy_backward(pos, b + n, b + n + num);
    fill_n(pos, num, v);
    return b+off;
  }
  
  T *erase(T *pos) { copy(pos+1, end(), pos); --n; return pos; }
  T *erase(T *f, T *l) { copy(l, end(), f); n -= (l-f); return f; }
  
  void clear() { resize(0); }
  void resize(int ns, const T &v=T()) {
    while (n < ns) b[n++] = v;
    n = ns;
  }
};
