/* KTH ACM Contest Template Library
 *
 * tinystl/stack (vector implementation)
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By David Rydh
 */

#include "vector"

template <class T>
struct stack {
  vector<T> v; stack() : v() {}
  void push(const T &x) { v.push_back(x); }
  void pop() { v.pop_back(); }
  bool empty() { return v.empty(); }
  T &top() { return v.back(); }
  const T &top() const { return v.back(); }
};
