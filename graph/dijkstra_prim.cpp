/* KTH ACM Contest Template Library
 *
 * Graph/Shortest Path and Minimum Spanning Tree/Dijkstra and Prim
 *
 * Credit:
 *   Dijkstra
 *   Prim
 *   by Mattias de Zalenski
 *   Modified by David Rydh
 */
#include <set>

template <class E, class M, class P, class D>
void dijkstra_prim(E &edges, M &min, P &path, int start, int n, D distfun,
		   bool mst = false) {
  typedef typename M::value_type T;
  T inf(1<<29);

  set< pair<T, int> > q; // use a set as a modifiable priority queue

  for (int i = 0; i < n; i++) {
    min[i] = inf;
    path[i] = -1;
  }
  min[start] = T();

  q.insert(make_pair(min[start], start));
  while (!q.empty()) {
    int node = q.begin()->second;
    q.erase(q.begin());
    if (mst) min[node] = T(); // only difference between dijkstra and prim
    typedef typename E::value_type L;
    typedef typename L::const_iterator L_iter;

    const L &l = edges[node];
    for (L_iter it = l.begin(); it != l.end(); ++it) {
      pair<int, T> p = distfun(*it, min[node]);
      int dest = p.first; T dist = min[node] + p.second;
      if (dist < min[dest]) {
	q.erase(make_pair(min[dest], dest)); //
	min[dest] = dist; // update dest in the queue
	q.insert(make_pair(min[dest], dest)); //
	path[dest] = node;
      }
    }
  }
}
