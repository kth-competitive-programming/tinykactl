/* KTH ACM Contest Template Library
 *
 * Graph/Shortest Path and Minimum Spanning Tree/Dijkstra and Prim
 *
 * Credit:
 *   Dijkstra
 *   Prim
 *   by Mattias de Zalenski
 */
#include <set>

template <class V> struct idxless {
  const V &v; idxless(const V &_v) : v(_v) { }
  bool operator<(int i, int j) const { return v[i] < v[j]; }
};
/*
template <class V, class C> struct idxcomp {
  const V &v; const C &c; idxcomp(const V &_v, const C &_c) : v(_v), c(_c) { }
  bool operator<(int i, int j) const { return c(v[i], v[j]); }
};
*/

template <class E, class M, class P, class D, class T>
void dijkstra_prim(int start, E &edges, M &min, P &path, D distfun,
		   T inf = T(1 << 29), bool mst = false) {
  typedef idxless< M > C;
  set< int, C > q(C(min)); // use a set as a modifiable priority queue
  for (int i = 0; i < edges.size(); i++)
    min[i] = inf;
  min[start] = T();
  q.insert(start);
  while (!q.empty()) {
    int node = *q.begin();
    q.erase(q.begin());
    if (mst) min[node] = T(); // only difference between dijkstra and prim
    typedef E::value_type L;
    L &l = edges[node];
    for (L::iterator it = l.begin(); it != l.end(); it++) {
      pair<int, T> p = distfun(*it, min[node]);
      int dest = p.first; T dist = min[node] + p.second;
      if (min[dest] == inf || dist < min[dest]) {
	q.erase(dest); // \
	min[dest] = dist; // update dest in the queue
	q.insert(dest); //
	path[dest] = node;
      }
    }
  }
}

// sample dist fun:s
pair<int, int> one_dist(int node, int) { return make_pair(node, 1); }
template <class W> pair<int, W> w_dist(pair<int, W> edge, W) { return edge; }
// for time-table searches:
struct mod_dist { int mod; mod_dist(int _mod) : mod(_mod) { }
  pair<int, int> operator()(pair<int, set<int> > &edge, int t) {
    const set<int> &tbl = edge.second; int tmod = t % mod;
    set<int>::const_iterator it = tbl.lower_bound(tmod);
    if (it == tbl.end()) t += mod, it = tbl.begin();
    return make_pair(edge.first, t - tmod + *it);
  }
};
