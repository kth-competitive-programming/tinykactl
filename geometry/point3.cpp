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
  typedef point3 S;
  typedef const S &R;
  T x, y, z;
  point3(T _x=T(), T _y=T(), T _z=T()) : x(_x), y(_y), z(_z) { }
  bool operator< (R p) const {
    return x < p.x || x <= p.x && (y < p.y || y <= p.y && z<p.z);
  }
  S operator-(R p) const { return S(x - p.x, y - p.y, z - p.z); }
  S operator+(R p) const { return S(x + p.x, y + p.y, z + p.z); }
  S operator/(T d) const { return S(x / d, y / d, z / d); }
  T dot(R p)  const  { return x*p.x + y*p.y + z*p.z; }
  S cross(R p) const { return S(y*p.z - z*p.y,
				z*p.x - x*p.z,
				x*p.y - y*p.x); }
};

// unit normal to a plane from two vectors
template <class P> P normal(P p, P q) { return unit(p.cross(q));}

