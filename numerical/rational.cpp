/* KTH ACM Contest Template Library
 *
 * Numerical/rational
 *
 * Credit:
 *   By Fredrik Niemelä
 */

#include "gcd.cpp"

template <class T>
struct rational {
  T n, d;
  rational(T _n=T(), T _d=T(1)) : n(_n/gcd(_n,_d)), d(_d/gcd(_n,_d)) { 
    if (d < 0) n *= -1, d *= -1;
  }

  bool operator <(const rational<T> &r) const {
    return n*r.d < d*r.n;
  }
};

template <class T>
rational<T> operator +(const rational<T> &lhs, const rational<T> &rhs) {
  return rational<T>(lhs.n*rhs.d + rhs.n*lhs.d, lhs.d*rhs.d);
}

template <class T>
rational<T> operator *(const rational<T> &lhs, const rational<T> &rhs) {
  return rational<T>(lhs.n*rhs.n, lhs.d*rhs.d);
}

/*
template <class T>
ostream &operator <<(ostream &lhs, const rational<T> &rhs) {
  lhs << rhs.n;
  if (rhs.d != 1)
    lhs << '/' << rhs.d;
  return lhs;
}
*/

const int P = 15;
template <class T>
ostream &operator <<(ostream &lhs, const rational<T> &rhs) {
  int n = rhs.n, d = rhs.d;

  if (n < 0)
    lhs << '-', n *= -1;

  lhs << n/d;
  n = n%d;

  if (n) {
    lhs << '.';

    for (int i = 0; n && i < P; ++i) {
      n *= 10;
      lhs << n/d;
      n = n%d;
    }      
  }

  return lhs;
}


