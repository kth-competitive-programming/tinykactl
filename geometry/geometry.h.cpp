/* KTH ACM Contest Template Library
 *
 * Geometry/Primitives/pi, sqr, line unnecessary
 *
 * Credit:
 *   by Mattias de Zalenski
 */

#include <cmath>

const double pi = acos(0.0) * 2;


template <class T> T sqr(T x) { return x * x; }


template <class P> struct line {
  typedef typename P::coord_type coord_type;
  P p1, p2; line(P _p1 = P(), P _p2 = P()) : p1(_p1), p2(_p2) { }
};
