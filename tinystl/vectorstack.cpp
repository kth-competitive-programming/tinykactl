/* KTH ACM Contest Template Library
 *
 * tinystl/vectorstack
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By David Rydh
 */

#include "vector"

// The vectorstack has all of stack and also some extra
// functions such as clear(). (it inherits all of vector)

template <class T>
struct vectorstack : vector<T> {
  stack() : vector<T>() {}
  void push(const T &x) { push_back(x); }
  void pop() { pop_back(); }
  T &top() { return back(); }
  const T &top() const { return back(); }
};

