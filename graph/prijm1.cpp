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
template <class M, class P, bool MST>
struct prijm1 {
  typedef typename M::value_type T;

  M &min; P &path; int node;

  queue< int > q;

  prijm1(M &m, P &p, int start) : min(m), path(p) {
    min[start] = T();
    q.push(start);
    while (!q.empty()) {
      node = q.front(); q.pop();
      if (MST) min[node] = T(); // only difference between dijkstra and prim
      f(node);
    }
  }

  void relax(int dest) {
    if (min[node] + 1 < min[dest]) {
      min[dest] = min[node] + dist;
      q.push(dest);
      path[dest] = node;
    }
  }

  void f(int node) { // call relax on every edge that leaves node
  }
};

template <class M, class P>
void dijkstra1(M &m, P &p, int start) { prijm1<M, P, false>(m, p, start); }

template <class M, class P>
void prim1(M &m, P &p, int start) { prijm1<M, P, true>(m, p, start); }
