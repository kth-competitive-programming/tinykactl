/* KTH ACM Contest Template Library
 *
 * Geometry/Primitives/CCW
 *
 * Credit:
 *   Based on Sedgewick
 *   By David Rydh
 *   Updated and moved by Mattias de Zalenski
 */

template <class P>
int ccw(P p0, P p1, P p2) {
  typedef typename P::coord_type T;
  P d1 = p1-p0, d2 = p2-p0;

  T d = cross(d1, d2);
  if( d != 0 ) return d>0 ? 1:-1;

  // Points are on a line

  // If points are on different sides of p1, the angle is 
  // 180 degrees (a degenerated triangle). This is a ambigous
  // case which never occurs for the convex_hull algorithm.
  if (d1.x * d2.x < 0 || d1.y * d2.y < 0) return -1;

  // The correct ordering of 3 points on a row is p0-p1-p2.
  if (dist2(d1) < dist2(d2)) return +1;

  // If all three points coincide return 0.
  return 0;
}
