/* KTH ACM Contest Template Library
 *
 * Geometry/Primitives/pi, sqr, point simple, line unnecessary
 *
 * Credit:
 *   by Mattias de Zalenski
 */

#include <cmath>

const double pi = acos(0.0) * 2;

template <class T> T sqr(T x) { return x * x; }


template <class T> struct point {
  typedef T coord_type;
  T x, y;
  point(T _x=T(), T _y=T()) : x(_x), y(_y) { }
  bool operator< (const point<T> &p) const {
    return x < p.x || x <= p.x && y < p.y;
  }
};


template <class T> struct line {
  typedef T coord_type;
  point<T> p1, p2;
  line(point<T> _p1=point<T>(), point<T> _p2=point<T>() ):p1(_p1), p2(_p2) {}
};
