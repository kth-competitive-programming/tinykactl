/* KTH ACM Contest Template Library
 *
 * Geometry/Primitives/Line intersection
 *
 * Credit:
 *   By Mattias de Zalenski
 */

template <class P, class R>
bool line_isect(P p0, P p1, P q0, P q1, R &x) {
  typedef typename R::coord_type T;

  P m = perp(p1-p0), n = perp(q1-q0);
  T det = cross(m, n);
  if (det == 0)
    return false;

  T a = dot(m, p0), b = dot(n, q0);
  x.x = (a*q.x - b*p.x) / det;
  x.y = (a*q.y - b*p.y) / det;
  return true;
}
