/* KTH ACM Contest Template Library
 *
 * Geometry/Primitives/Point structure
 *
 * Credit:
 *   By Mattias de Zalenski
 */
#include <cmath>

template <class T>
struct point {
  typedef T coord_type;
  T x, y; point(T _x=T(), T _y=T()) : x(_x), y(_y) { }
  bool operator<(const point<T> &p) const { return x!=p.x ? x<p.x : y<p.y; }
  point<T> operator-(const point<T> &p)const { return point<T>(x-p.x,y-p.y); }
  point<T> operator/(T d) const { return point<T>(x/d, y/d); }
};


template <class T> T dX(T p, T q) { return q - p; }

template <class T> T dx(point<T> p, point<T> q) { return q.x - p.x; }
template <class T> T dy(point<T> p, point<T> q) { return q.y - p.y; }

template <class T> T sqr(T x) { return x * x; }
template <class T> T dist2(point<T> p) { return sqr(p.x) + sqr(p.y); }
template <class T> T dist(point<T> p) { return sqrt((double) dist2(p)); }

template <class T> T dot(point<T> p, point<T> q) { return p.x*q.x + p.y*q.y; }
template <class T> T cross(point<T> p, point<T> q) { return p.x*q.y-p.y*q.x; }

template <class P> P unit(P p) { return p / dist(p); }
template <class P> P perp(P p) { return P(-p.y, p.x); }
template <class P> P normal(P p) { return unit(perp(p)); }
