/* KTH ACM Contest Template Library
 *
 * Graph/Minimum Spanning Tree/Prim
 *
 * Credit:
 *   Dijkstra, Prim
 *   By Mattias de Zalenski
 */
#include <vector>
#include "../dijkstra_prim.cpp"

template <class P, class T> P id_dist(P edge, T) { return edge; }
template <class E, class P>
void prim(int root, E &edges, P &path, int n) {
  typedef typename E::value_type::value_type::second_type T;
  vector<T> min(n);
  dijkstra_prim(root, edges, min, path, n, id_dist, true);
}
