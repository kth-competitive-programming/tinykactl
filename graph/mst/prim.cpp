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
#include "../distfun.cpp"

template <class E, class P>
void prim(int root, E &edges, P &path, int n) {
  typedef typename E::value_type::value_type::second_type T;
  vector<T> min(n);
  dijkstra_prim(edges, min, path, root, n, id_dist<pair<int,T>,T>, true);
}
