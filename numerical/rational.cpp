/* KTH ACM Contest Template Library
 *
 * Numerical/rational
 *
 * Credit:
 *   By Fredrik Niemelä
 */

#include <iostream>
using namespace std;

#include "gcd.cpp"

template <class T>
struct rational {
  T n, d;
  rational(T _n=T(), T _d=T(1)) : n(_n), d(_d) {
    normalize();
  }
  void normalize() {
    if (d < T()) n *= -1, d *= -1;
    T f = n < T() ^ d < n ? gcd(n, d) : gcd(d, n);
    n /= f; d /= f;
  }
  bool operator <(const rational<T> &r) const { return n*r.d < d*r.n; }
  bool operator ==(const rational<T> &r) const { return n*r.d == d*r.n; }
};

template <class T>
rational<T> operator +(const rational<T> &a, const rational<T> &b) {
  return rational<T>(a.n*b.d + b.n*a.d, a.d*b.d);
}

template <class T>
rational<T> operator -(const rational<T> &a) {
  return rational<T>(-a.n, a.d);
}

template <class T>
rational<T> operator -(const rational<T> &a, const rational<T> &b) {
  return rational<T>(a.n*b.d - b.n*a.d, a.d*b.d);
}

template <class T>
rational<T> operator *(const rational<T> &a, const rational<T> &b) {
  return rational<T>(a.n*b.n, a.d*b.d);
}

template <class T>
rational<T> operator /(const rational<T> &a, const rational<T> &b) {
  return rational<T>(a.n*b.d, a.d*b.n);
}

template <class T>
T div(const rational<T> &a, const rational<T> &b) {
  return (a.n*b.d) / (a.d*b.n);
}

template <class T>
rational<T> operator %(const rational<T> &a, const rational<T> &b) {
  return rational<T>((a.n*b.d) % (a.d*b.n), a.d*b.d);
}

template <class T>
rational<T> operator <<(const rational<T> &a, int b) {
  return b < 0 ? a >> -b : rational<T>(a.n << b, a.d);
}

template <class T>
rational<T> operator >>(const rational<T> &a, int b) {
  return b < 0 ? a << -b : rational<T>(a.n, a.d << b);
}

template <class T>
ostream &print_frac(ostream &out, const rational<T> &r) {
  out << r.n;
  if (r.d != 1) out << '/' << r.d;
  return out;
}

template <class T>
ostream &print_dec(ostream &out, const rational<T> &r,
		   int radix = 10, int precision = 15) {
  T n = r.n, d = r.d;
  if (n < T()) out << '-', n *= -1;
  out << n/d; n %= d;
  if (T() < n) {
    out << '.';
    for (int i = 0; n && i < precision; ++i) {
      n *= radix;
      out << n/d; n %= d;
    }
  }
  return out;
}

template <class T>
ostream &operator <<(ostream &out, const rational<T> &r) {
  return print_dec(out, r);
}

template <class T>
istream &read_frac(istream &in, rational<T> &r) {
  in >> r.n;
  if (in.peek() == '/') {
    char c; in >> c >> r.d;
  } else
    r.d = T(1);
  r.normalize();
  return in;
}

template <class T>
istream &read_dec(istream &in, rational<T> &r) {
  T i, f(0); 
  in >> i;
  if (in.peek() == '.') {
    char c; in >> c >> f;
  }
  r.d = T(1);
  while (r.d <= f) r.d *= 10;
  r.n = i*r.d + f;
  r.normalize();
  return in;
}

template <class T>
istream &operator >>(istream &in, rational<T> &r) {
  return read_dec(in, r);
}
