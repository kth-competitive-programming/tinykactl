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

  P p = p1-p0, q = q1-q0;
  T det = cross(p, q);
  if (det == 0)
    return false;

  T a = dot(perp(p), p0), b = dot(perp(q), q0);
  x.x = (a*q.x - b*p.x) / det;
  x.y = (a*q.y - b*p.y) / det;
  return true;
}
