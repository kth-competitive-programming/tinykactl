/* KTH ACM Contest Template Library
 *
 * Geometry/Polygons/Inside
 *
 * Credit:
 *   By David Rydh
 */

#include "point_ops.cpp"

template <class P>
int sideof(P p0, P p1, P q) {
  typename P::coord_type d = cross(p1-p0, q-p0);
  return d > 0 ? 1 : d < 0 ? -1 : 0;
}

template<class P>
bool onsegment(P p0, P p1, P q) {
  // Check if point is outside line segment rectangle.
  if( dx(p0,q)*dx(p1,q) > 0 || dy(p0,q)*dy(p1,q) > 0 )
    return false;

  // Check if point is on line (not line segment)
  return cross(p1-p0, q-p0) == 0;
}

template <class P>
double linedist(P p0, P p1, P q) {
  return (double) cross(p1-p0, q-p0) / dist(p1-p0);
}
