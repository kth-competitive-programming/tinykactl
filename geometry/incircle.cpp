/* KTH ACM Contest Template Library
 *
 * Geometry/Enclosing circle/Test, Midpoint, Radius
 *
 * Credit:
 *   Based on [Geometry in C, pp. xx-yy,zz]
 *   By Mattias de Zalenski
 */

template <class P>
double incircle(P A, P B, P C, P D) {
  typedef typename P::coord_type T;
  P a = A - D; T a2 = a.dist2();
  P b = B - D; T b2 = b.dist2();
  P c = C - D; T c2 = c.dist2();
  return (a2*b.cross(c) + b2*c.cross(a) + c2*a.cross(b));
}

template <class P, class R>
bool enclosing_centre(P A, P B, P C, R &p, double eps = 1e-13) {
  typedef typename R::coord_type T;
  P a = A - C, b = B - C;
  T det2 = a.cross(b) * 2;
  if (-eps < det2 && det2 < eps) return false;
  T a2 = a.dist2(), b2 = b.dist2();
  p.x = (b.y * a2 - a.y * b2) / det2 + C.x;
  p.y = (a.x * b2 - b.x * a2) / det2 + C.y;
  return true;
}

template <class P, class T>
bool enclosing_radius(P A, P B, P C, T &r, T eps = 1e-13) {
  T a = (B-C).dist(), b = (C-A).dist(), c = (A-B).dist();
  T K4 = heron(a, b, c) * 4;
  if (K4 < eps) return false;
  r = a * b * c / K4;
  return true;
}
