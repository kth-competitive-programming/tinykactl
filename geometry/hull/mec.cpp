/* KTH ACM Contest Template Library
 *
 * Geometry/Minimum Enclosing Circle/Simple hull algorithm
 *
 * Credit:
 *   By Mattias de Zalenski
 */

#include "hull_diameter.cpp"
#include "../incircle.cpp"

template <class V, class P>
bool mec(V p, int n, P &c, int &i1, int &i2, int &i3, double eps = 1e-13) {
  typedef typename P::coord_type T;
  hull_diameter2(p, n, i1, i2);
  c = (p[i1] + p[i2]) / 2;
  T r2 = dist2(c, p[i1]);
  bool f = false;
  for (int i = 0; i < n; ++i)
    if (dist2(c, p[i]) > r2) {
      i3 = i, f = true;
      enclosing_centre(p[i1], p[i2], p[i3], c, eps);
      r2 = dist2(c, p[i]);
    }
  return f;
}

template <class V, class P>
double mec(V p, int n, P &c, double eps = 1e-13) {
  int i1, i2, i3;
  mec(p, n, c, i1, i2, i3, eps);
  return dist(c, p[i1]);
}
