/*****************************************************************************
 * 
 * Geometry6: geometry ops
 * =======================
 *
 * General geometric operations.
 *
 * Point dx, dy, dist, angle, linear angle theta.
 *
 * REQUIRES  geometry.h
 * ------------------------------------------------------------------------- *
 *
 * NADA acmlib (10 March 2002)
 * Templates for KTH-NADA, Ballons'R'Us, ACM 2001-2002
 *   Swedish competition, Link?ping 6 Oct 2001
 *   Revised for SWERC, Portu, Portugal 17 Nov 2001
 *   Revised for World Finals, Honolulu, 23 Mar 2002
 *   David Rydh, Mattias de Zalenski, Fredrik Niemel?
 *
 *****************************************************************************/

#include "geometry.h"

template <class T> inline T sqr(T x) { return x * x; }

// q = p + (dx,dy)
template <class T>
typename T::coord_type dx(const T &p, const T &q) { return q.x - p.x; }
template <class T>
typename T::coord_type dy(const T &p, const T &q) { return q.y - p.y; }

// q = p + dist * e^{i*angle}
template <class T>
double dist(const T &p, const T &q) {
  return sqrt(sqr((double) dx(p, q)) + sqr((double) dy(p, q)));
}
template <class T>
double angle(const T &p, const T &q) {
  return atan2(dy(p, q), dx(p, q));
}

// dist = sqrt(dist2)
template <class T>
double dist2(const T &p, const T &q) {
  return sqr((double) dx(p, q)) + sqr((double) dy(p, q));
}

// f(x)=theta(0,e^{i*x}) : (-pi,pi] -> (-2,2], strictly increasing
template <class T>
double theta(const T &p, const T &q) {
  double x = dx(p, q), y = dy(p, q);
  if (x == 0 && y == 0) return 0;
  double t = y / (x < 0 ^ y < 0 ? x - y : x + y);
  return x < 0 ? y < 0 ? t - 2 : t + 2 : t;
}
