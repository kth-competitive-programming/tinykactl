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
  typedef bigint S;
  typedef const S & R;

  static const T P; // maximum limb value
  static const unsigned N; // number of digits per limb

  vector<T> v; // limb vector

  bigint(T c = 0) { carry(c); }

  S &carry(T c) { while (c != 0) v.push_back(c % P), c /= P; return *this; }

  // limb access
  unsigned size() const { return v.size(); }
  T operator[](unsigned i) const { return v[i]; }
  T &operator[](unsigned i) { return v[i]; }

  // comparison
  int comp(R n, unsigned j = 0) const {
    if (v.size() != n.size() + j) return v.size() < n.size() + j ? -1 : 1;
    for (unsigned i = v.size(); i-- > j; )
      if (v[i] != n[i - j]) return v[i] < n[i - j] ? -1 : 1;
    return 0;
  }
  bool operator <(R n) const { return comp(n) < 0; }
  bool operator ==(R n) const { return comp(n) == 0; }

  // addition
  S &add(T c, unsigned i = 0) {
    while (c != 0 && i < v.size())
      c += v[i], v[i] = c % P, c /= P, ++i;
    return carry(c);
  }
  S &operator +=(T c) { return add(c); }
  S operator +(T c) const { S t = *this; return t += c; }

  S &add(R n, unsigned j = 0) {
    if (v.size() < n.size() + j) v.resize(n.size() + j);
    T c = 0;
    for (unsigned i = 0; i < n.size(); ++i)
      c += v[i + j] + n[i], v[i + j] = c % P, c /= P;
    add(c, n.size() + j);
    return *this;
  }
  S &operator +=(R n) { return add(n); }
  S operator +(R n) const { S t = *this; return t += n; }

  // subtraction
  S &sub(T c, unsigned i = 0) {
    for (; c != 0 && i < v.size(); ++i)
      c += P-1 - v[i], v[i] = P-1 - c % P, c /= P;
    while (size() > 0 && v[size() - 1] == 0) v.pop_back();
    return *this;
  }
  S &operator -=(T c) { return sub(c); }
  S operator -(T c) const { S t = *this; return t -= c; }

  S &sub(R n, unsigned j = 0) {
    T c = 0; //assert(v.size() < n.size());
    for (unsigned i = 0; i < n.size(); ++i)
      c += P-1 + n[i] - v[i + j], v[i + j] = P-1 - c % P, c /= P;
    sub(c, n.size() + j);
    return *this;
  }
  S &operator -=(R n) { return sub(n); }
  S operator -(R n) const { S t = *this; return t -= n; }

  // increment/decrement
  S &operator ++() { return add(1); }
  S &operator --() { return sub(1); }
  S operator ++(int) { S t = *this; add(1); return t; }
  S operator --(int) { S t = *this; sub(1); return t; }

  // multiplication
  S &operator *=(T n) {
    M c = M();
    if (n == 0)
      v.clear();
    else if (n != 1)
      for (unsigned i = 0; i < v.size(); ++i)
	c += M(v[i]) * n, v[i] = T(c % P), c /= P;
    return carry(T(c));
  }
  S operator *(T c) const { S t = *this; return t *= c; }

  S operator *(R n) const {
    R m = *this;
    S r;
    if (m.size() > 0 && n.size() > 0) {
      r.v.resize(m.size() + n.size() - 1);
      for (unsigned i = 0; i < m.size(); ++i) {
	M c = M();
	for (unsigned j = 0; j < n.size(); ++j)
	  c += r[i+j] + M(m[i]) * M(n[j]), r[i+j] = T(c % P), c /= P;
	r.add(T(c), i + n.size());
      }
    }
    return r;
  }
  S &operator *=(R n) { return *this = *this * n; }

  // division and modulo T
  S &divmod(T &d) { // d is divisor in, remainder out
    M c = M();
    for (unsigned i = size(); i-- > 0; )
      c = c * P + v[i], v[i] = T(c / d), c %= d;
    sub(0); d = T(c); // sub to clear away zeros; return remainder in d
    return *this;
  }
  S &operator /=(T d) { return divmod(d); }
  S operator /(T d) const { S t = *this; t.divmod(d); return t; }
  S &operator %=(T d) { divmod(d); *this = d; return *this; }
  T operator %(T d) const { S t = *this; t.divmod(d); return d; }


  // long division
  void divmod(S &d) {
    S n = *this, q;
    if (!(n < d) && d.size() > 0) {
      M e = M(d[d.size() - 1]) * P + (d.size() >= 2 ? d[d.size() - 2] + 1 : 0);
      unsigned i = n.size() - d.size(), j = n.size();
      q.v.resize(i + 1);
      while (!(n < d)) {
	if (n.comp(d, i) >= 0) {
	  M m =
	    (M(j < n.size() ? n[j] : 0) * P +
	     (j >= 1 ? n[j - 1] : 0)) * P +
	    (j >= 2 ? n[j - 2] : 0);
	  T g = T(m / e);
	  n.sub(d * g, i);
	  while (n.comp(d, i) >= 0)
	    ++g, n.sub(d, i);
	  q[i] = g;
	}
	--i, --j;
      }
    }
    *this = q; // store quotient in this
    sub(0); d = n; // sub to clear away zeros; return remainder in d
  }
  /*
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
  */
  S &operator /=(R d) { S r = d; return divmod(r); }
  S operator /(R d) const { S t = *this, r = d; return t.divmod(r); }
  S &operator %=(R d) { S r = d; divmod(r); return *this = r; }
  S operator %(R d) const { S t = *this, r = d; t.divmod(r); return r; }


  // binary operations with T
  T operator &(T x) const { return v.empty() ? 0 : v[0] & x; }
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
    x &= (1 << N) - 1;
    if (v.empty()) v.push_back(x); else v[0] |= x;
    return *this;
  }
  S &operator ^=(T x) {
    x &= (1 << N) - 1;
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
    T limb = 0;
    for (unsigned k = l>n.N ? l-n.N : 0; k < l; ++k)
      limb = 10*limb + s[k]-'0';
    n.v.push_back(limb);
    l = l>n.N ? l-n.N : 0;
  }
  n.sub(0);
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
