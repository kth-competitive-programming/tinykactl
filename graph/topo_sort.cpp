/*****************************************************************************
 * 
 * 7_topo_sort: Topological sort
 * =============================
 *
 * INPUT
 * -----
 *
 * OUTPUT
 * ------
 *
 * COMPLEXITY  O( V + E )
 *
 * REQUIRES  -
 * ------------------------------------------------------------------------- *
 *
 * NADA acmlib (10 March 2002)
 * Templates for KTH-NADA, Ballons'R'Us, ACM 2001-2002
 *   Swedish competition, Linköping 6 Oct 2001
 *   Revised for SWERC, Portu, Portugal 17 Nov 2001
 *   Revised for World Finals, Honolulu, 23 Mar 2002
 *   David Rydh, Mattias de Zalenski, Fredrik Niemelä
 *
 *****************************************************************************/

#include <vector>
#include <queue>

template <class E, class I>
bool topo_sort(const E *edges, I &idx, int n) {
  typedef typename E::const_iterator E_iter;
  vector<int> indeg(n);
  for (int i = 0; i < n; i++)
    for (E_iter e = edges[i].begin(); e != edges[i].end(); e++)
      indeg[*e]++;
  queue<int> q; // use priority_queue for lexic. smallest ans.
  for (int i = 0; i < n; i++)
    if (indeg[i] == 0) q.push(-i);
  int nr = 0;
  while (q.size() > 0) {
    int i = -q.front(); // top() for priority_queue
    idx[i] = ++nr;
    q.pop();
    for (E_iter e = edges[i].begin(); e != edges[i].end(); ++e)
      if (--indeg[*e] == 0) q.push(-*e);
  }
  return nr == n;
}
