/* KTH ACM Contest Template Library
 *
 * Geometry/Polygons/Inside
 *
 * Credit:
 *   By David Rydh
 */

#include "point.cpp"

// Determine on which side of a line a point is.  +1/-1 is left/right
// of vector $p_1-p_0$ and 0 is on the line.
template <class P> inline
int sideof(P p0, P p1, P q) {
  typename P::coord_type d = cross(p1-p0, q-p0);
  return d > 0 ? 1 : d < 0 ? -1 : 0;
}

// Determine if a point is on a line segment (incl the end points).
template<class P> inline
bool on_segment(P p0, P p1, P q) {
  return (p0.dx(q)*p1.dx(q) <= 0 && p0.dy(q)*p1.dy(q) <= 0 &&
	  (p1-p0).cross(q-p0) == 0);
}

// Get a measure of the distance of a point from a line (0 on the line
// and positive/negative on the different sides).
template <class P> inline
double linedist(P p0, P p1, P q) {
  return (double) cross(p1-p0, q-p0) / dist(p1-p0);
}
