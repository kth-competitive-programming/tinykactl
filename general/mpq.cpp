#include <set>

template <class T, class C>
struct upq {
  set<T, C> s;
  upq(const C &c = C()) : s(c) { }
  void empty() { return s.empty(); }
  void push(const T &x) { s.insert(x); }
  const T &front() { return *s.begin(); }
  template <class V>
  void update(const T &x, V &oldv, const V &newv) {
    s.erase(x);
    oldv = newv;
    s.insert(x);
  }
  void pop() { s.erase(s.begin()); }
};

