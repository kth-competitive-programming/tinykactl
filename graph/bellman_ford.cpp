/* KTH ACM Contest Template Library
 *
 * Graph/Shortest path/Bellman-Ford-2
 *
 * Credit:
 *   Based on Popup-02 lecture
 *   By Mattias de Zalenski
 *   Modified by David Rydh
 */

template <class E, class M, class P, class D>
bool bellman_ford(E &edges, M &min, P &path, 
		  int start, int n, int m) {
  typedef typename M::value_type T;
  T inf(1<<29);

  for (int i = 0; i < n; i++) {
    min[i] = inf;
    path[i] = -1;
  }
  min[start] = T();

  bool changed = true;
  for (int i = 1; changed; ++i) { // V-1 times
    changed = false;
    for (int j = 0; j < m; ++j) {
      int node = edges[j].first.first;
      int dest = edges[j].first.second;
      T dist = min[node] + edges[j].second;

      if (dist < min[dest]) {
	if( i>=n )
	  return false; // negative cycle!
	min[dest] = dist;
	path[dest] = node;
	changed = true;
      }
    }
  }
  return true; // graph is negative-cycle-free
}
