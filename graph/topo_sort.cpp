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

template <class V, class I>
bool topo_sort(const V &edges, I &idx, int n) {
  typedef typename V::value_type::const_iterator E_iter;
  vector<int> indeg;
  indeg.resize(n, 0);
  for (int i = 0; i < n; i++)
    for (E_iter e = edges[i].begin(); e != edges[i].end(); e++)
      indeg[*e]++;
  //queue<int> q;
  priority_queue<int> q; // **
  for (int i = 0; i < n; i++)
    if (indeg[i] == 0)
      q.push(-i);
  int nr = 0;
  while (q.size() > 0) {
    //int i = -q.front();
    int i = -q.top(); // **
    idx[i] = nr++;
    q.pop();
    for (E_iter e = edges[i].begin(); e != edges[i].end(); e++)
      if (--indeg[*e] == 0)
	q.push(-*e);
  }
  return nr == n;
}
