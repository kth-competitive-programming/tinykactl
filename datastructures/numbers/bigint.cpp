/* KTH ACM Contest Template Library
 *
 * Datastructures/Numerical/Big unsigned integers
 *
 * Credit:
 *   Based on own and previous KACTL implementations
 *   By Mattias de Zalenski
 */
#include <vector>

template <class T, class M=T> // limb type, multiplication intermediate type
struct bigint {
  typedef bigint<T, M> S;
  typedef const S & R;

  static const T P; // maximum limb value
  static const unsigned N; // number of digits per limb
  vector<T> v; // limb vector

  bigint(T c = T()) { carry(c); }
  S &carry(T c) { while (c != T()) v.push_back(c % P), c /= P; return *this; }

  // limb access
  unsigned size() const { return v.size(); }
  T operator[](unsigned i) const { return v[i]; }

  // comparison
  bool operator <(R n) const {
    if (v.size() != n.size()) return v.size() < n.size();
    for (unsigned i = v.size(); i-- > 0; )
      if (v[i] != n[i]) return v[i] < n[i];
    return false;
  }
  bool operator ==(R n) const {
    if (v.size() != n.size()) return false;
    for (unsigned i = 0; i < v.size(); ++i)
      if (v[i] != n[i]) return false;
    return true;
  }

  // addition
  S &add(T c, unsigned i = 0) {
    while (c != T() && i < v.size())
      c += v[i], v[i] = c % P, c /= P;
    return carry(c);
  }
  S &operator ++() { return add(T(1)); }
  S operator ++(int) { S t = *this; add(T(1)); return t; }
  S &operator +=(T c) { return add(c); }
  S &operator +=(R n) {
    if (v.size() < n.size()) v.resize(n.size());
    T c = T();
    for (unsigned i = 0; i < n.size(); ++i)
      c += v[i] + n[i], v[i] = c % P, c /= P;
    add(c, n.size());
  }
  S operator +(T c) const { S t = *this; return t += c; }
  S operator +(R n) const { S t = *this; return t += n; }

  // subtraction
  S &sub(T c, unsigned i = 0) {
    for (; c != T() && i < v.size(); ++i)
      c += P-1 - v[i], v[i] = P-1 - c % P, c /= P;
    while (size() > 0 && v[size() - 1] == T()) v.pop_back();
    return *this;
  }
  S &operator --() { return sub(T(1)); }
  S operator --(int) { S t = *this; sub(T(1)); return t; }
  S &operator -=(T c) { return sub(c); }
  S &operator -=(R n) {
    if (v.size() < n.size()) v.resize(n.size()); // could be skipped
    T c = T();
    for (unsigned i = 0; i < n.size(); ++i)
      c += P-1 + n[i] - v[i], v[i] = P-1 - c % P, c /= P;
    sub(c, n.size());
  }
  S operator -(T c) const { S t = *this; return t -= c; }
  S operator -(R n) const { S t = *this; return t -= n; }

  // multiplication
  S &operator *=(T n) {
    M c = M();
    if (n == T())
      v.clear();
    else if (n != T(1))
      for (unsigned i = 0; i < v.size(); ++i)
	c += M(v[i]) * n, v[i] = T(c % P), c /= P;
    return carry(T(c));
  }
  S operator *(T c) const { S t = *this; return t *= c; }
  S &mul(R m, R n) {
    v.clear();
    if (m.size() > 0 && n.size() > 0) {
      v.resize(m.size() + n.size() - 1);
      for (unsigned i = 0; i < m.size(); ++i) {
	M c = M();
	for (unsigned j = 0; j < n.size(); ++j)
	  c += v[i+j] + M(m[i]) * M(n[j]), v[i+j] = T(c % P), c /= P;
	add(T(c), i + n.size());
      }
    }
    return *this;
  }
  S operator *(R n) const { S t; t.mul(*this, n); return t; }
  S &operator *=(R n) { S t1 = *this, t2 = n; return mul(t1, t2); }

  // division and modulo T
  S &divmod(T &d) {
    M c = M();
    for (unsigned i = size(); i-- > 0; )
      c = c * P + v[i], v[i] = T(c / d), c %= d;
    sub(T()); d = T(c); // sub to clear away zeros; return remainder in d
    return *this;
  }
  S &operator /=(T d) { return divmod(d); }
  S operator /(T d) const { S t = *this; t.divmod(d); return t; }
  S &operator %=(T d) { divmod(d); v.clear(); carry(d); return *this; }
  T operator %(T d) const { S t = *this; t.divmod(d); return d; }


  // long division
  S &divmod(R d, S &q) {
    S &r = *this; q = 0;
    S t = d, m = 1;
    while (t <= r) t *= 2, m *= 2;
    while (m > S(1)) {
      t /= 2, m /= 2;
      if (r >= t) r -= t, q += m;
    }
    return *this;
  }
  S &operator /=(R d) { S t = *this; t.divmod(d, *this); return *this; }
  S operator /(R d) const { S t = *this, q; t.divmod(d, q); return q; }
  S &operator %=(R d) { S q; return divmod(d, q); }
  S operator %(R d) const { S t = *this, q; t.divmod(d, q); return t; }


  // binary operations with T
  T operator &(T x) const { return v.empty() ? T(0) : v[0] & x; }
  S &operator <<=(int x) {
    while (x < 0) *this /= 2, ++x;
    while (x > 0) *this *= 2, --x;
    return *this;
  }
  S &operator >>=(int x) { return *this <<= -x; }

  S &operator &=(T x) { // allows *this &= ~3
    if (!v.empty()) v[0] &= ~T((1 << N) - 1) | x; // only the last N bits
    return *this;
  }
  S &operator |=(T x) {
    x &= T((1 << N) - 1);
    if (v.empty()) v.push_back(x); else v[0] |= x;
    return *this;
  }
  S &operator ^=(T x) {
    x &= T((1 << N) - 1);
    if (v.empty()) v.push_back(x); else v[0] ^= x;
    return *this;
  }
};

#include <iostream>
template <class T, class M>
ostream &operator <<(ostream &out, const bigint<T, M> &n) {
  if (n.size() > 0) {
    unsigned i = n.size() - 1;
    out << n[i];
    char fill = out.fill(); out.fill('0');
    while (i-- > 0)
      out.width(n.N), out << n[i]; // right-adjust is required (but default(?))
    out.fill(fill);
  }
  else
    out << '0';
  return out;
}

#include <string>
template <class T, class M>
istream& operator>>(istream& in, bigint<T, M> &n) {
  string s; in >> s;
  unsigned l = s.length();
  n.v.clear();
  while (l > 0) {
    T limb = T();
    for (unsigned k = l>n.N ? l-n.N : 0; k < l; ++k)
      limb = 10*limb + s[k]-'0';
    n.v.push_back(limb);
    l = l>n.N ? l-n.N : 0;
  }
  return in;
}

//typedef unsigned long ul;
//typedef unsigned long long ull;
//typedef bigint<ul, ull> big;
//const ul big::P = ul(1e9); // or 1e18, not using multiplication
//const unsigned big::N = 9; // or 18

//typedef unsigned short us;
//typedef unsigned long ul;
//typedef bigint<us, ul> big;
//const us big::P = us(1e4); // or 1e9, not using multiplication
//const unsigned big::N = 4; // or 9
