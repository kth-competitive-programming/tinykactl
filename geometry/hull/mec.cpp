/* KTH ACM Contest Template Library
 *
 * Geometry/Minimum Enclosing Circle/Simple hull algorithm
 *
 * Credit:
 *   By Mattias de Zalenski
 *   Revised (STLised) by Per Austrin
 */

#include "hull_diameter.cpp"
#include "incircle.cpp"

template <class It, class P>
bool mec(It begin, It end, P &c, It &i1, It &i2, It &i3, 
	 double eps = 1e-13) {
  typedef typename P::coord_type T;
  hull_diameter2(begin, end, i1, i2);
  c = (*i1 + *i2) / 2;
  T r2 = (c-*i1).dist2();
  bool f = false;
  for (int i = 0; i < n; ++i)
    if ((c-*i).dist2() > r2) {
      i3 = i, f = true;
      enclosing_centre(*i1, *i2, *i3, c, eps);
      r2 = (c-*i).dist2();
    }
  return f;
}

template <class It, class P>
double mec(It begin, It end, P &c, double eps = 1e-13) {
  It i1, i2, i3;
  mec(begin, end, c, i1, i2, i3, eps);
  return dist(c, *i1);
}
