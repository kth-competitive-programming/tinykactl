/* KTH ACM Contest Template Library
 *
 * Geometry/Polygon area/Cross product (determinant) sum
 *
 * Credit:
 *   By Mattias de Zalenski
 */

template <class V>
double poly_area(V p, int n) {
  typename V::value_type::coord_type a = 0;
  for (int i = 0, j = n - 1; i < n; j = i++)
    a += cross(p[j], p[i]);
  return (double) a / 2;
}
