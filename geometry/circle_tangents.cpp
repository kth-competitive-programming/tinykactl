/* KTH ACM Contest Template Library
 *
 * Geometry/Primitives/Circle Tangents
 *
 * Credit:
 *   By David Rydh
 */

template <class P, class T>
bool circle_tangents(const P &p, const P &c, T r, P &t1, P &t2) {
  P a = (c-p), ap = perp(a);
  double a2 = dist2(a), r2 = r*r;
  P x = p+a*(1-r2/a2), y = ap*(sqrt(a2-r2)*r/a2);

  t1 = x + y;
  t2 = x - y;
  return a2==r2;
}
