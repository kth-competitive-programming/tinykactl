/* KTH ACM Contest Template Library
 *
 * Geometry/Primitives/Point structure, 3D
 *
 * Credit:
 *   By Mattias de Zalenski
 */

template <class T>
struct point3 {
  typedef T coord_type;
  T x, y, z;
  point3(T _x=T(), T _y=T(), T _z=T()) : x(_x), y(_y), z(_z) { }
  bool operator< (const point3<T> &p) const {
    return x < p.x || x <= p.x && (y < p.y || y <= p.y && z < p.z);
  }
  point3<T> operator-(const point3<T> &p) const {
    return point3<T>(x - p.x, y - p.y, z - p.z);
  }
  point3<T> operator/(T d) const {
    return point3<T>(x / d, y / d, z / d);
  }
};

template <class T> T dot(point3<T> p, point3<T> q) {
  return p.x*q.x + p.y*q.y + p.z*q.z;
}

template <class P> P cross(P p, P q) {
  return P(p.y*q.z - p.z*q.y,
	   p.z*q.x - p.x*q.z,
	   p.x*q.y - p.y*q.x);
}
