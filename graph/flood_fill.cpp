/* KTH ACM Contest Template Library
 *
 * Graph/Connectivity/Flood fill
 *
 * Credit:
 *   By Mattias de Zalenski
 */
#include <queue>

template <class E, class M, class T>
void flood_fill(E &edges, M &m, int start, T from, T to) {
  typedef typename E::value_type L;
  typedef typename L::const_iterator L_iter;
  queue<int> q;

  if (from == to) return;
  q.push(start);
  while (!q.empty()) {
    int node = q.front(); q.pop();
    if (m[node] == from) {
      m[node] = to;
      const L &l = edges[node];
      for (L_iter it = l.begin(); it != l.end(); it++)
	q.push(*it);
    }
  }
}
