/* KTH ACM Contest Template Library
 *
 * Geometry/Convex hull in space/Insertion algorithm, O(nF)
 *
 * Credit:
 *   Based on [Geometry in C, pp. xx-yy,zz]
 *   By Mattias de Zalenski
 */
#include <set>

struct ABC {
  int a, b, c; ABC(int _a, int _b, int _c):a(_a), b(_b), c(_c) {}
  bool operator<(const ABC &o) const {
    return a!=o.a ? a<o.a : b!=o.b ? b<o.b : c<o.c;
  }
};

template <class V, class L>
bool convex_hull_space(V p, int n, L &trilist) {
  typedef typename V::value_type P3;
  typedef typename P3::coord_type T;
  typedef typename L::value_type I3;
  typedef set<pair<int, int> > SPI;
  int a, b, c; // Find a proper tetrahedron
  for (a = 1; a < n; ++a) if ((p[a]-p[0]).dist2() != T()) break;
  for (b = a + 1; b < n; ++b) if ((p[a]-p[0]).cross(p[b]-p[0]).
				  dist2()) break;
  for (c = b + 1; c < n; ++c) if ((p[a]-p[0]).cross(p[b]-p[0]).
				  dot(p[c]-p[0]) != T()) break;
  if (c >= n) return false;
  if ((p[a]-p[0]).cross(p[b]-p[0]).dot(p[c]-p[0]) > T()) 
    swap(a, b);
  trilist.push_back(I3(0, a, b)); // Use it as initial hull
  trilist.push_back(I3(0, b, c));
  trilist.push_back(I3(0, c, a));
  trilist.push_back(I3(a, c, b));
  for (int i = 1; i < n; ++i) {
    typename L::iterator it = trilist.begin();
    SPI edges;
    P3 &P = p[i];
    while (it != trilist.end()) {
      int a = it->a, b = it->b, c = it->c;
      P3 &A = p[a], &B = p[b], &C = p[c];
      P3 normal = (B-A).cross(C-A);
      T d = normal.dot(P-A);
      if (d > T()) {
	edges.insert(make_pair(a, b));
	edges.insert(make_pair(b, c));
	edges.insert(make_pair(c, a));
	trilist.erase(it++); // ugly!!
      } else ++it;
    }
    for (SPI::iterator j = edges.begin(); j != edges.end(); ++j)
      if (edges.count(make_pair(j->second, j->first)) == 0)
	trilist.push_back(I3(i, j->first, j->second));
  }
  return true;
}
