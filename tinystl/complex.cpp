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
  complex(complex_pol<T> c): re(c.abs*cos(c.ang)), im(c.abs*sin(c.ang)) {}
  
  C operator+(CR c) { return C(re + c.re, im + c.im); }
  C operator-(CR c) { return C(re - c.re, im - c.im); }
  C operator*(CR c) { return C(re*c.re - im*c.im, re*c.im + im*c.re); }
  C operator/(CR c) {
    return C((re*c.re + im*c.im)/c.abs2(), (im*c.re - re*c.im)/c.abs2());
  }
  T abs2() { return sqr(re) + sqr(im); }
  C conj() { return C(re, -im); }
  // TODO:
  // cos, sin, tan, sqrt...
};

template <class T>  T abs(complex<T> c) { return sqrt(c.abs2()); }
template <class T>  complex<T> exp(complex<T> c) {
  return complex<T>(complex_pol<T>(exp(c.re), c.im));
}
template <class T>
ostream& operator<<(ostream& o, complex& c) {
  o << c.re << (c.im < T() ? '-' : '+') << abs(c.im);
}


template <class T>
struct complex_pol {
  typedef complex_pol C;
  typedef const C &CR;
  complex_pol(const complex<T> c): abs(abs(c)), ang(atan(c.im, c.re)) {}

  T abs, ang;
  complex_pol(T ab, T an): abs(ab), ang(an) {}
  C operator*(CR c) { return C(abs*c.abs, ang+c.ang); }
  C operator/(CR c) { return C(abs/c.abs, ang-c.ang); }
};

template <class T>  T abs(complex_pol<T> c) { return c.abs; }
ostream& operator<<(ostream& o, complex_pol& c) { 
  o << c.abs << '*e^(' << c.ang << 'i)';
}
