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
#include "mpq"

template <class E, class M, class P, class D>
void dijkstra_prim(int start, E &edges, M &min, P &path, int n, D distfun,
		   bool mst = false) {
  typedef idxless< M > C;
  typedef E::value_type L;
  typedef typename M::value_type T;
  T inf(1<<29);

  mpq< int, C > q(C(min)); // use a modifiable priority queue
  for (int i = 0; i < n; i++)
    min[i] = inf;
  min[start] = T();

  q.push(start);
  while (!q.empty()) {
    int node = q.front(); q.pop();
    if (mst) min[node] = T(); // only difference between dijkstra and prim
    L &l = edges[node];
    for (L::iterator it = l.begin(); it != l.end(); it++) {
      pair<int, T> p = distfun(*it, min[node]);
      int dest = p.first; T dist = min[node] + p.second;
      if (dist < min[dest]) {
	q.update(dest, min[dest], dist);
	path[dest] = node;
      }
    }
  }
}
