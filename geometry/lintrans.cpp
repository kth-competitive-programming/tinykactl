/* KTH ACM Contest Template Library
 *
 * Geometry/Primitives/Rotation-Scaling
 *
 * Credit:
 *   By Per Austrin
 */

// Apply the linear transformation which takes line p0-p1 to line
// q0-q1 to point r (without reflection).
template <class P>
P lintrans(const P& p0, const P& p1,
	   const P& q0, const P& q1, const P& r) {
  P dp = p1-p0, dq = q1-q0, num(dp.cross(dq), dp.dot(dq));
  typename P::coord_type den = dp.dist2();
  return q0 + P((r-p0).cross(num), (r-p0).dot(num)) / den;
}
