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
  typedef point S;
  typedef const S &R;
  T x, y;
  point(T _x=T(), T _y=T()) : x(_x), y(_y) { }
  bool operator< (R p) const {
    return x < p.x || x <= p.x && y < p.y;
  }
  S operator-(R p) const { return S(x - p.x, y - p.y); }
  S operator+(R p) const { return S(x + p.x, y + p.y); }
  S operator/(T d) const { return S(x / d, y / d); }
  T dot(R p)  const  { return x*p.x + y*p.y; }
  T cross(R p) const { return x*p.y - y*p.x; }
};

template <class T> T dot(point<T> p, point<T> q) { return p.dot(q); }

template <class T> T cross(point<T> p, point<T> q) { return p.cross(q); }
