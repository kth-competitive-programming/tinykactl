/*****************************************************************************
 * 
 * geometry.h
 * ==========
 *
 * pi, point struct, line struct, general geometric operations:
 *
 * sqr, point dx, dy, dist, angle, linear angle theta.
 *
 *****************************************************************************/
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <math.h>

const double pi = acos(0) * 2;

template <class T> struct point {
  typedef T coord_type;
  T x, y;
  point(T _x=T(), T _y=T() ) : x(_x), y(_y) {}
  bool operator <(const point<T> &p) const {
    return x < p.x || x <= p.x && y < p.y;
  }
};

template <class T> struct line {
  typedef T coord_type;
  point<T> p1, p2;
  line(point<T> _p1=point<T>(), point<T> _p2=point<T>() ):p1(_p1), p2(_p2) {}
};

template <class T> inline T sqr(T x) { return x * x; }

// q = p + (dx,dy)
template <class T>
inline typename T::coord_type dx(const T &p, const T &q) { return q.x - p.x; }
template <class T>
inline typename T::coord_type dy(const T &p, const T &q) { return q.y - p.y; }

// q = p + dist * e^{i*angle}
template <class T>
inline double dist(const T &p, const T &q) {
  return sqrt(sqr((double) dx(p, q)) + sqr((double) dy(p, q)));
}
template <class T>
inline double angle(const T &p, const T &q) {
  return atan2(dy(p, q), dx(p, q));
}

// dist = sqrt(dist2)
template <class T>
inline double dist2(const T &p, const T &q) {
  return sqr((double) dx(p, q)) + sqr((double) dy(p, q));
}

// f(x)=theta(0,e^{i*x}) : (-pi,pi] -> (-2,2], strictly increasing
template <class T>
inline double theta(const T &p, const T &q) {
  double x = dx(p, q), y = dy(p, q);
  if (x == 0 && y == 0) return 0;
  double t = y / (x < 0 ^ y < 0 ? x - y : x + y);
  return x < 0 ? y < 0 ? t - 2 : t + 2 : t;
}
#endif
