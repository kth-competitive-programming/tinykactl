/* KTH ACM Contest Template Library
 *
 * Geometry/Polyhedron volume/Vector tripple product (determinant) sum
 *
 * Credit:
 *   By Mattias de Zalenski
 */

template <class V, class L>
double poly_volume(const V &p, const L &trilist) {
  typename L::value_type::coord_type v = 0;
  for (typename L::const_iterator i = trilist.begin(); i != trilist.end; ++i)
    v += dot(cross(p[i->a], p[i->b]), p[i->c]);
  return (double) v / 6;
}
