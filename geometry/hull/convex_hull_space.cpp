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
  int a, b, c; ABC(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }
  bool operator<(const ABC &o) const {
    return a!=o.a ? a<o.a : b!=o.b ? b<o.b : c<o.c;
  }
};

template <class V, class S>
bool convex_hull_space(V p, int n, S &triset) {
  typedef typename V::value_type P3;
  typedef typename P3::coord_type T;
  typedef typename S::value_type I3;
  int a, b, c;
  for (a = 1; a < n; ++a) if (dist2(p[a]-p[0]) != T()) break;
  for (b = a + 1; b < n; ++b) if (dist2(cross(p[a]-p[0],p[b]-p[0]))) break;
  for (c = b + 1; c < n; ++c) if (dot(cross(p[a]-p[0],p[b]-p[0]), p[c]-p[0])
				  != T()) break;
  if (c >= n) return false;
  if (dot(cross(p[a]-p[0],p[b]-p[0]), p[c]-p[0]) > T()) swap(a, b);
  triset.insert(I3(0, a, b));
  triset.insert(I3(0, b, c));
  triset.insert(I3(0, c, a));
  triset.insert(I3(a, c, b));
  for (int i = 1; i < n; ++i) {
    typedef pair<int, int> I2;
    set< pair<int, int> > edges;
    P3 &P = p[i];
    {
      typename S::iterator it = triset.begin();
      while (it != triset.end()) {
        int a = it->a, b = it->b, c = it->c;
	P3 &A = p[a], &B = p[b], &C = p[c];
	P3 normal = cross(B-A, C-A);
	T d = dot(normal, P-A);
	if (d > T()) {
	  edges.insert(make_pair(a, b));
	  edges.insert(make_pair(b, c));
	  edges.insert(make_pair(c, a));
	  triset.erase(it++); // ugly!!
	}
	else
	  ++it;
      }
    }
    for (set<I2>::iterator it = edges.begin(); it != edges.end(); ++it)
      if (edges.count(make_pair(it->second, it->first)) == 0)
	triset.insert(I3(i, it->first, it->second));
  }
  return true;
}