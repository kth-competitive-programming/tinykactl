/* KTH ACM Contest Template Library
 *
 * Graph/Shortest Path and Minimum Spanning Tree/Dijkstra and Prim
 *
 * Credit:
 *   Dijkstra Prim
 *   by Mattias de Zalenski
 */
#include <set>

// min should be initialised before-hand to inf values, path to -1 values
template <class F, class M, class P, class X>
struct prijmx {
  typedef typename M::value_type T;
  M min; P path; X node;
  set< pair<T, X> > q; // use a set as a modifiable priority queue
  prijmsktrax(F f, M &m, P &p, X start, bool mst = false) : min(m), path(p) {
    min[start] = T();
    q.insert(make_pair(min[start], start));
    while (!q.empty()) {
      node = q.begin()->second;
      q.erase(q.begin());
      if (mst) min[node] = T(); // only difference between dijkstra and prim
      f(node, *this); // for_edge
    }
  }
  void operator ()(pair<X, T> p) {
    X dest = p.first; T dist = min[node] + p.second;
    if (dist < min[dest]) {
      q.erase(make_pair(min[dest], dest)); //
      min[dest] = dist; // update dest in the queue
      q.insert(make_pair(min[dest], dest)); //
      path[dest] = node;
    }
  }
};
template <class F, class M, class P, class X>
void prijm(F f, M &m, P &p, X x, bool t) { prijmx<F, M, P, X>(f, m, p, x, t); }

/*
// example for_edge function objects:
typedef vector<int> Vi; vector<Vi> g;
struct onefun {
  template <class F> void operator()(int node, F f) {
    const Vi &l = g[node];
    for (Vi::const_iterator i = l.begin(); i != l.end(); ++i)
      f(make_pair(*i, 1));
  }
}
typedef vector<pair<int, int> > Vp; vector<Vp> h;
struct lenfun {
  template <class F> void operator()(int node, F &f) {
    const Vp &l = h[node];
    for_each(l.begin(), l.end(), f);
  }
}
typedef vector<point<double> > VP; int n; VP pts(n);
struct distfun {
  template <class F> void operator()(int node, F &f) {
    for (int i = 0; i < pts.size(); ++i)
      f(i, dist(pts[node] - pts[i]));
  }
}
*/
