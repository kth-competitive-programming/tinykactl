/* KTH ACM Contest Template Library
 *
 * Graph/Shortest Path and Minimum Spanning Tree/Dijkstra and Prim 1
 *
 * Credit:
 *   Dijkstra Prim
 *   by Mattias de Zalenski
 */
#include <queue>

// min should be initialised before-hand to inf values [path to -1 values]
template <class F, class M, class P, class X, bool MST>
struct prijm1 {
  typedef typename M::value_type T;
  M &min; P &path; X node;
  queue< X > q;
  prijm1(F f, M &m, P &p, X start) : min(m), path(p) {
    min[start] = T();
    q.insert(start);
    while (!q.empty()) {
      node = q.front(); q.pop();
      if (MST) min[node] = T(); // only difference between dijkstra and prim
      f(node, *this); // for_edge
    }
  }
  void operator ()(X dest) {
    if (min[node] + 1 < min[dest]) {
      min[dest] = min[node] + dist;
      q.push(dest);
      path[dest] = node;
    }
  }
};
template <class F, class M, class P, class X>
void dijkstra1(F f, M &m, P &p, X x) { prijm1<F, M, P, X, false>(f, m, p, x); }
template <class F, class M, class P, class X>
void prim1(F f, M &m, P &p, X x) { prijm1<F, M, P, X, true>(f, m, p, x); }
