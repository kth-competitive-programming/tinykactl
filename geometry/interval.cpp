/* KTH ACM Contest Template Library
 *
 * Geometry/Primitives/Interval intersections
 *
 * Credit:
 *   By Mattias de Zalenski, David Rydh
 */

#include "geometry.h"

template <class T>
bool ivalisect(T p0, T p1, T q0, T q1, T &r0, T &r1) {
  T pmin = min(p0, p1), pmax = max(p0, p1);
  T qmin = min(q0, q1), qmax = max(q0, q1);
  r0 = max(pmin, qmin), r1 = min(pmax, qmax);
  return r0 <= r1;
}

template <class P>
bool rectisect(P p0, P p1, P q0, P q1, P &r0, P &r1) {
  bool xflag = ivalisect(p0.x, p1.x, q0.x, q1.x, r0.x, r1.x);
  bool yflag = ivalisect(p0.y, p1.y, q0.y, q1.y, r0.y, r1.y);
  return xflag && yflag;
}
