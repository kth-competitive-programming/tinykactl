/* KTH ACM Contest Template Library
 *
 * Graph/Connectivity/Connected components
 *
 * Credit:
 *   By Mattias de Zalenski
 */
#include <vector>
#include "flood_fill.cpp"

template <class E, class M>
int connected_components(E &edges, M &m, int n) {
  int count = 0;
  for (int i = 0; i < n; ++i)
    m[i] = 0;
  for (int i = 0; i < n; ++i)
    if (m[i] == 0) {
      ++count;
      flood_fill(edges, m, i, 0, count);
    }
  return count;
}
