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

// one distfun
pair<int, int> one_dist(int node, int) { return make_pair(node, 1); }

// weighted edge distfun
template <class P, class T> P id_dist(P edge, T) { return edge; }

// for time-table searches without mod:
template <class T, T inf>
pair<int, T> step_dist(pair<int, pair<T, T> > &edge, T t) {
  return make_pair(edge.first, edge.second.first < t ? inf :
		   edge.second.first - t + edge.second.second);
}

// for time-table searches:
template <int MOD>
pair<int, int > mod_dist(const pair<int, pair<int, int> > &edge, int t) {
  return make_pair(edge.first, (edge.second.first - t % MOD + MOD) % MOD +
    edge.second.second);
}
