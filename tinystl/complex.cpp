/* KTH ACM Contest Template Library
 *
 * tinystl/complex numbers
 *
 * Credit:
 *   By Per Austrin
 */

#include <math.h>

template <class T>   T sqr(T a) { return a*a; }
template <class T>   struct complex_pol;
template <class T>
struct complex {
  typedef complex C;
  typedef const C &CR;
  T re, im;
  enum {reg, pol} kind;

  complex(T r = T(), T i = T()): re(r), im(i), kind(r) {}
  
  C operator+(CR c) { return C(re + c.re, im + c.im); }
  C operator-(CR c) { return C(re - c.re, im - c.im); }
  C operator*(CR c) { return C(re*c.re - im*c.im, re*c.im + im*c.re); }
  C operator/(CR c) {
    return C((re*c.re + im*c.im)/c.abs2(), (im*c.re - re*c.im)/c.abs2());
  }
  T abs2() { return sqr(re) + sqr(im); }
  C conj() { return C(re, -im); }

  complex_pol<T> to_polar() { return complex_pol<T>(abs(*this),atan2(im,re)); }
  
  // TODO:
  // cos, sin, tan, sqrt...
};

template <class T>  T abs(complex<T> c) { return sqrt(c.abs2()); }
template <class T>  complex<T> exp(complex<T> c) {
  return to_regular(complex_pol(exp(c.re), im));
}
template <class T>
ostream& operator<<(ostream& o, complex& c) {
  o << c.re << (c.im < T() ? '-' : '+') << abs(c.im);
}


template <class T>
struct complex_pol {
  typedef complex_pol C;
  typedef const C &CR;

  T abs, ang;
  complex_pol(T ab, T an): abs(ab), ang(an) {}
  C operator*(CR c) { return C(abs*c.abs, ang + c.ang); }
  C operator/(CR c) { return C(abc/c.abs, ang - c.ang); }
  complex<T> to_regular() { return complex<T>(abs*cos(ang), abs*sin(ang)); }
};

template <class T>  T abs(complex_pol<T> c) { return c.abs; }
ostream& operator<<(ostream& o, complex_pol& c) { 
  o << c.abs << '*e^(' << c.ang << 'i)';
}

