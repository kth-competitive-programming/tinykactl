/* KTH ACM Contest Template Library
 *
 * Geometry/Hull/Hull diameter
 *
 * Credit:
 *   By David Rydh, Mattias de Zalenski
 *   Revised (STLised) by Per Austrin
 */

#include "point.cpp"

template <class It>
double hull_diameter2(It begin, It end, It &i1, It &i2) {
  typedef iterator_traits<It>::value_type::coord_type T;
  int n = end - begin;
  if (n < 2) { i1 = i2 = 0; return 0; }
  T m = 0;
  int i, j = 1, k = 0;
  It i, j = begin+1, k = begin;
  for (i = begin; i <= k; i++) {  // wander around
    T d2 = (*j-*i).dist2(); // find opposite
    while (++j != end) {
      T t = (*j-*i).dist2();
      if (t > d2) d2 = t; else break;
    }
    --j;
    if (i == begin) k = j; // remember first opposite index
    if (d2 > m) m = d2, i1 = i, i2 = j;
  }
  return m;
}
