/* KTH ACM Contest Template Library
 *
 * Geometry/Polygon area/Cross product (determinant) sum
 *
 * Credit:
 *   By Mattias de Zalenski
 */

#include "point.cc"

template <class T, class It>
T poly_area2(It begin, It end) {
  T a = T();
  for (It i = begin, j = end - 1; i != end; j = i++)
    a += j->cross(*i);
  return a;
}
