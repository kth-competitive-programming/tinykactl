/* KTH ACM Contest Template Library
 *
 * Graph/Shortest Path and Minimum Spanning Tree/Dijkstra and Prim
 *
 * Credit:
 *   Dijkstra Prim
 *   by Mattias de Zalenski
 */
#include <set>

// min should be initialised before-hand to inf values [path to -1 values]
template <class M, class P, bool MST>
struct prijm {
  typedef typename M::value_type T;

  M &min; P &path; int node;

  set< pair<T, X> > q; // use as an mpq

  prijm(M &m, P &p, int start) : min(m), path(p) {
    min[start] = T();
    q.insert(make_pair(min[start], start));
    while (!q.empty()) {
      node = q.begin()->second;
      q.erase(q.begin());
      if (MST) min[node] = T(); // only difference between dijkstra and prim
      f(node);
    }
  }

  void relax(int dest, T dist) {
    if (min[node] + dist < min[dest]) {
      q.erase(make_pair(min[dest], dest)); //
      min[dest] = min[node] + dist; // update dest in the queue
      q.insert(make_pair(min[dest], dest)); //
      path[dest] = node;
    }
  }

  void f(int node) { // call relax on every edge that leaves node
  }
};

template <class M, class P>
void dijkstra(M &m, P &p, int start) { prijm<M, P, false>(m, p, start); }

template <class M, class P>
void prim(M &m, P &p, int start) { prijm<M, P, true>(m, p, start); }
