/* KTH ACM Contest Template Library
 *
 * datastructures/priority queue/mpq
 *
 * Credit:
 *   By Mattias de Zalenski
 */

#include <algorithm>
#include <set>

template <class T, class C = greater<T> > // priority_queue compatibility..
struct mpq {
  set<T, C> s;
  mpq(const C &c = C()) : s(c) { }
  bool empty() { return s.empty(); }
  void push(const T &x) { s.insert(x); }
  const T &front() { return *s.begin(); }
  template <class S>
  void update(const T &x, S &oldv, const S &newv) {
    s.erase(x);
    oldv = newv;
    s.insert(x);
  }
  void pop() { s.erase(s.begin()); }
};

