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
template <class F, class M, class P, class X>
struct prijm {
  typedef typename M::value_type T;
  M &min; P &path; X node;
  set< pair<T, X> > q; // use a set as a modifiable priority queue
  prijm(F f, M &m, P &p, X start, bool mst = false) : min(m), path(p) {
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
void dijkstra(F f, M &m, P &p, X x) { prijm<F, M, P, X>(f, m, p, x, false); }
template <class F, class M, class P, class X>
void prim(F f, M &m, P &p, X x) { prijm<F, M, P, X>(f, m, p, x, true); }
