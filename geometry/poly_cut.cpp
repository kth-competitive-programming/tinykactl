/* KTH ACM Contest Template Library
 *
 * Geometry/Primitives/Polygon cut
 *
 * Credit:
 *   By Mattias de Zalenski
 */

#include "line_isect.cpp"

template <class It, class P>
It poly_cut(It first, It last, P p0, P p1, It result) {
  if (first == last) return result;
  P p = p1-p0;
  It j = last; --j;
  bool pside = cross(p, *j-p0) > 0;
  for (It i = first; i != last; ++i) {
    bool side = cross(p, *i-p0) > 0;
    if (pside ^ side)
      line_isect(p0, p1, *i, *j, *result++);
    if (side)
      *result++ = *i;
    j = i; pside = side;
  }
  return result;
}
