/* KTH ACM Contest Template Library
 *
 * Geometry/Primitives/Point structure
 *
 * Credit:
 *   By Mattias de Zalenski
 */

template <class T>
struct point {
  typedef T coord_type;
  T x, y;
  point(T _x=T(), T _y=T()) : x(_x), y(_y) { }
  bool operator< (const point<T> &p) const {
    return x < p.x || x <= p.x && y < p.y;
  }
  point<T> operator-(const point<T> &p) const {
    return point<T>(x - p.x, y - p.y);
  }
  point<T> operator/(T d) const {
    return point<T>(x / d, y / d);
  }
};

template <class T> T dot(point<T> p, point<T> q) {
  return p.x*q.x + p.y*q.y;
}

template <class T> T cross(point<T> p, point<T> q) {
  return p.x*q.y - p.y*q.x;
}
