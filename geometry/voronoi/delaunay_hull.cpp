/* KTH ACM Contest Template Library
 *
 * Geometry/Voronoi/Delaunay triangulation, algorithm using hull3d
 *
 * Credit:
 *   Based on [Geometry in C, pp. xx-yy,zz]
 *   By Mattias de Zalenski
 */
#include <vector>
#include <list>

#include "point3.cpp"
#include "convex_hull_space.cpp"

template <class V, class F>
void delaunay(V &p, int n, F trifun) {
  typedef point3<typename V::value_type::coord_type> P3;
  typedef vector<P3> V3;
  typedef list<ABC> L;
  V3 p3(n);
  for (int i = 0; i < n; ++i)
    p3[i] = P3(p[i].x, p[i].y, dist2(p[i]));
  L l;
  convex_hull_space(p3, n, l);
  for (L::iterator it = l.begin(); it != l.end(); ++it)
    if ((p3[it->b]-p3[it->a]).
	cross(p3[it->c]-p3[it->a]).dot(P3(0,0,1)) < 0)
      trifun(it->a, it->c, it->b); // triangles are turned!
}
