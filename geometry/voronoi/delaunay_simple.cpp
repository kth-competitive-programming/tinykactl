/* KTH ACM Contest Template Library
 *
 * Geometry/Voronoi/Delaunay triangulation, simple n^4 algorithm
 *
 * Credit:
 *   Based on [Geometry in C, pp. xx-yy,zz]
 *   By Mattias de Zalenski
 */

#include "point.cpp"

template <class V, class F>
void delaunay(V p, int n, F trifun) {
  typedef typename V::value_type P;
  typedef typename P::coord_type T;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      P J = p[j] - p[i]; T jd = J.dist2();
      for (int k = i + 1; (j != k || ++k) && k < n; ++k) {
	P K = p[k] - p[i]; T kd = K.dist2();
	T qd = J.cross(K);
	if (qd > T()) {
	  P q = P(J.y*kd - K.y*jd, jd*K.x - kd*J.x);
	  bool flag = true;
	  for (int l = 0; l < n; ++l) {
	    P L = p[l] - p[i]; T dl = L.dist2();
	    if (L.dot(q) + dl * qd < T()) {
	      flag = false;
	      break;
	    }
	  }
	  if (flag) trifun(i, j, k);
	}
      }
    }
  }
}
