/* KTH ACM Contest Template Library
 *
 * Geometry/Primitives/Point structure, 3D
 *
 * Credit:
 *   By Mattias de Zalenski
 */
#include <cmath>

template <class T>
struct point3 { // probably easiest to extend point to write this
  typedef T coord_type;
  T x, y, z; point3(T _x=T(), T _y=T(), T _z=T()) : x(_x), y(_y), z(_z) { }
  bool operator<(const point3<T> &p) const {
    return x!=p.x ? x<p.x : y!=p.y ? y<p.y : z<p.z;
  }
  point3<T> operator-(const point3<T> &p) const {
    return point3<T>(x-p.x,y-p.y,z-p.z);
  }
  point3<T> operator/(T d) const { return point3<T>(x/d, y/d,z/d); }
};

template <class T> T dx(point3<T> p, point3<T> q) { return q.x - p.x; }
template <class T> T dy(point3<T> p, point3<T> q) { return q.y - p.y; }
template <class T> T dz(point3<T> p, point3<T> q) { return q.z - p.z; }

//template <class T> T sqr(T x) { return x * x; }
template <class T> T dist2(point3<T> p) { return sqr(p.x)+sqr(p.y)+sqr(p.z); }
template <class T> T dist(point3<T> p) { return sqrt((double) dist2(p)); }

template <class T> T dot(point3<T> p, point3<T> q) {
  return p.x*q.x + p.y*q.y + p.z*q.z;
}
template <class P> P cross(P p, P q) {
  return P(p.y*q.z-p.z*q.y,
	   p.z*q.x-p.x*q.z,
	   p.x*q.y-p.y*q.x);
}

template <class P> P unit(P p) { return p / dist(p); }
