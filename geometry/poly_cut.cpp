/* KTH ACM Contest Template Library
 *
 * Geometry/Primitives/Polygon cut
 *
 * Credit:
 *   By Mattias de Zalenski
 */

#include "line_isect.cpp"

template <class CI, class OI, class P>
OI poly_cut(CI first, CI last, P p0, P p1, OI result) {
  if (first == last) return result;
  P p = p1-p0;
  CI j = last; --j;
  bool pside = p.cross(*j-p0) > 0;
  for (CI i = first; i != last; ++i) {
    bool side = p.cross(*i-p0) > 0;
    if (pside ^ side)
      line_isect(p0, p1, *i, *j, *result++);
    if (side)
      *result++ = *i;
    j = i; pside = side;
  }
  return result;
}

