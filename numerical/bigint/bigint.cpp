/* KTH ACM Contest Template Library
 *
 * Datastructures/<problem>/<algorithm>
 *
 * Credit:
 *   Based on my own and previous KACTL implementations
 *   By Mattias de Zalenski
 */
#include <vector>

template <class T, class M=T> // cell type and multiplication intermediate type
struct bigint {
  typedef bigint<T, M> bT;
  typedef const bT & R;
  static const T P; // maximum cell value
  static const unsigned N; // number of digits per cell
  vector<T> v;

  bigint(T c = T()) { carry(c); }
  bT &carry(T c) { while (c != T()) v.push_back(c % P), c /= P; return *this; }

  // cell access
  unsigned size() { return v.size(); }
  T &operator[](unsigned i) { return v[i]; }

  bool operator <(R n) const {
    if (v.size() != n.size()) return v.size() < n.size();
    for (unsigned i = 0; i < v.size(); ++i)
      if (v[i] != n[i]) return v[i] < n[i];
    return false;
  }
  bool operator ==(R n) const {
    if (v.size() != n.size()) return false;
    for (unsigned i = 0; i < v.size(); ++i)
      if (v[i] != n[i]) return false;
    return true;
  }

  bT &add(T c, unsigned i = 0) {
    while (c != T() && i < v.size())
      c += v[i], v[i] = c % P, c /= P;
    return carry(c);
  }
  bT &operator +=(T c) { return add(c); }
  bT &operator +=(R n) {
    if (v.size() < n.size()) v.resize(n.size());
    T c = T();
    for (unsigned i = 0; i < n.size(); ++i)
      c += v[i] + n[i], v[i] = c % P, c /= P;
    add(c, n.size());
  }
  bT operator +(T c) const { bT t = *this; return t += c; }
  bT operator +(R n) const { bT t = *this; return t += n; }

  bT &sub(T c, unsigned i = 0) {
    while (c != T() && i < v.size())
      c += P - v[i], v[i] = c % P, c /= P, --c;
    return carry(c);
  }
  bT &operator -=(T c) { return sub(c); }
  bT &operator -=(R n) {
    if (v.size() < n.size()) v.resize(n.size());
    T c = T();
    for (unsigned i = 0; i < n.size(); ++i)
      c += P + n[i] - v[i], v[i] = c % P, c /= P, --c;
    sub(c, n.size());
  }
  bT operator -(T c) const { bT t = *this; return t -= c; }
  bT operator -(R n) const { bT t = *this; return t -= n; }

  bT &operator *=(T n) {
    const M MP = M(P);
    M c = M(), m = M(n);
    for (unsigned i = 0; i < n.size(); ++i)
      c += M(v[i]) * m, v[i] = T(c % MP), c /= MP;
    carry(T(c));
  }
  bT &operator *(R n) {
    bT r; r.v.resize(v.size() + n.size() - 1);
    const M MP = M(P);
    for (unsigned i = 0; i < v.size(); ++i) {
      M c = M();
      for (unsigned j = 0; j < n.size(); ++j)
	c += M(v[i]) * M(v[j]), r[i+j] = T(c % MP), c /= MP;
      r.add(c, i + n.size());
    }
    return r;
  }
  bT operator *(T c) const { bT t = *this; return t *= c; }
  bT &operator *=(R n) const { bT t = *this; return *this = t * n; }
};

template <class T, class M>
ostream &operator<<(ostream &out, bigint<T, M>::R n) {
  if (n.size() > 0) {
    unsigned i = n.size() - 1;
    cout << v[i];
    while (i-- > 0)
      cout << fill('0') << setw(n.N) << right << v[i]; // ??
  }
}

typedef unsigned long ul;
typedef unsigned long long ull;

typedef bigint<ul, ull> bulull;
const ul bulull::P = ul(1e9);

#include <iostream>
int main() {
  cout << x.P << endl;
  return 0;
}
