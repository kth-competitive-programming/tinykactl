/* KTH ACM Contest Template Library
 *
 * Geometry/Primitives/Point operations
 *
 * Credit:
 *   By Mattias de Zalenski
 */

template <class P> typename P::coord_type dist2(P p) { return dot(p, p); }
template <class P> typename P::coord_type dx(P p, P q) { return q.x - p.x; }
template <class P> typename P::coord_type dy(P p, P q) { return q.y - p.y; }
// for point3:
template <class P> typename P::coord_type dz(P p, P q) { return q.z - p.z; }


#include <cmath>
template <class P> double dist(P p) { return sqrt(dist2(p)); }
template <class P> double angle(P p) { return atan2(p.y, p.x); }
template <class P> double theta(P p) {
  double x = p.x, y = p.y; if (x==0 && y==0) return 0;
  double t = y / (x<0^y<0 ? x-y : x+y);
  return x<0 ? y<0 ? t-2 : t+2 : t;
}


template <class P> P unit(P p) { return p / dist(p); }
template <class P> P perp(P p) { return P(-p.y, p.x); }
template <class P> P normal(P p) { return unit(perp(p)); }
// for point3: (unit normal to a plane from two vectors)
template <class P> P normal(P p, P q) { return unit(cross(p, q)); }
