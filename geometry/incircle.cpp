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
  P a = A - D; T a2 = dist2(a);
  P b = B - D; T b2 = dist2(b);
  P c = C - D; T c2 = dist2(c);
  return (a2 * cross(b, c) +
	  b2 * cross(c, a) +
	  c2 * cross(a, b));
}

template <class P, class R>
bool enclosing_centre(P A, P B, P C, R &p, double eps = 1e-13) {
  typedef typename R::coord_type T;
  P a = A - C, b = B - C;
  T det2 = cross(a, b) * 2;
  if (-eps < det2 && det2 < eps) return false;
  T a2 = dist2(a), b2 = dist2(b);
  p.x = (b.y * a2 - a.y * b2) / det2 + C.x;
  p.y = (a.x * b2 - b.x * a2) / det2 + C.y;
  return true;
}

#include "heron.cpp"
template <class P, class T>
bool enclosing_radius(P A, P B, P C, T &r, T eps = 1e-13) {
  T a = dist(B-C), b = dist(C-A), c = dist(A-B);
  T K4 = heron(a, b, c) * 4;
  if (K4 < eps) return false;
  r = a * b * c / K4;
  return true;
}
