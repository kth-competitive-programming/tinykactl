/* KTH ACM Contest Template Library
 *
 * Numerical/rational
 *
 * Credit:
 *   By Fredrik Niemelä, Mattias de Zalenski
 */

#include "gcd.cpp"

template <class T>
struct rational {
  typedef rational<T> rT;
  typedef const rT & R;
  T n, d;
  rational(T _n=T(), T _d=T(1)) : n(_n), d(_d) { normalize(); }
  void normalize() {
    T f = gcd(n, d); n /= f; d /= f;
    if (d < T()) n *= -1, d *= -1;
  }
  bool operator < (R r) const { return n * r.d <  d * r.n; }
  bool operator ==(R r) const { return n * r.d == d * r.n; }

  rT operator -() { return rT(-n, d); }

  rT operator +(R r) { return rT(n*r.d + r.n*d, d*r.d); }
  rT operator -(R r) { return rT(n*r.d - r.n*d, d*r.d); }

  rT operator *(R r) { return rT(n*r.n, d*r.d); }
  rT operator /(R r) { return rT( n*r.d,/**/d*r.n); }
  T/**//**/ div(R r) { return/**/(n*r.d) / (d*r.n); }
  rT operator %(R r) { return rT((n*r.d) % (d*r.n), d*r.d); }

  rT operator <<(int b) { return b<0 ? a>>-b : rT(n<<b, d); }
  rT operator >>(int b) { return b<0 ? a<<-b : rT(n, d<<b); }

  ostream &print_frac(ostream &out) {
    out << n; if (d != T(1)) out << '/' << d;
    return out;
  }

  istream &read_frac(istream &in) {
    in >> n;
    if (in.peek()=='/') { char c; in >> c >> d; } else d = T(1);
    normalize();
    return in;
  }
};

template <class T>
ostream &print_dec(ostream &out, const rational<T> &r,
		   int precision = 15, int radix = 10) {
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
ostream &operator<<(ostream &out, const rational<T> &r) {
  return print_dec(out, r); //or return r.print_frac(out);
}

template <class T>
istream &read_dec(istream &in, rational<T> &r) {
  T i, f(0), z(1); 
  in >> i;
  if (in.peek() == '.') {
    char c; in >> c;
    while (in.peek() == '0') { in >> c; z *= 10; }
    if (in.peek() >= '0' && in.peek() <= '9') in >> f;
  }
  r.d = T(1);
  while (r.d <= f) r.d *= 10;
  r.d *= z;
  r.n = i*r.d + f;
  r.normalize();
  return in;
}

template <class T> 
istream& operator>>(istream &in, rational<T> &r) {
  return read_dec(in, r); // or return r.read_frac(in);
}
