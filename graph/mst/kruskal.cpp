/*****************************************************************************
 * 
 * MST2: kruskal (Kruskal's MST algorithm)
 * =======================================
 *
 * Find a minimal spanning tree of a undirected graph.
 *
 * INPUT
 * -----
 * edges:  A vector with V edge-containers. The edge-containers should
 *         contain pairs (vertix, weight) and edges[vertix] should be the
 *         edge-list for the vertix "vertix".
 *
 * V:      the number of vertices
 *
 * OUTPUT
 * ------
 * tree:   The minimal spanning tree. tree may be the same vector as edges.
 *         It must already have the correct nr of edge-lists allocated.
 *
 *
 * COMPLEXITY  O(E log E)
 *
 * REQUIRES: mst/1_sets.cpp
 *
 * ------------------------------------------------------------------------- *
 *
 * NADA acmlib (10 March 2002)
 * Templates for KTH-NADA, Ballons'R'Us, ACM 2001-2002
 *   Swedish competition, Link?ping 6 Oct 2001
 *   Revised for SWERC, Portu, Portugal 17 Nov 2001
 *   Revised for World Finals, Honolulu, 23 Mar 2002
 *   David Rydh, Mattias de Zalenski, Fredrik Niemel?
 *
 *   Revised for World Finals, Prague, ?? Mar 2004
 *   Per Austrin/Three-Headed Monkey
 *
 *****************************************************************************/

#include <algorithm>
#include <vector>
#include "sets.cpp"

template <class G>
void kruskal(const G *graph, G *tree, int n) {
  typedef typename G::const_iterator          G_iter;
  typedef typename G::value_type::second_type D;
  sets sets(n);
  vector<pair< D,pair<int,int> > > E;

  // Convert all edges into a single edge-list
  for( int i=0; i<n; i++ )
    for(G_iter it = graph[i].begin(); it!=graph[i].end(); ++it)
      if (i < it->first)//Undirected:only use half of the edges
	E.push_back(make_pair(it->second,
			      make_pair(i, it->first)));
  sort(E.begin(), E.end());
  for(int i=0; i<n; i++) tree[i].clear();

  int numEdges = edges.size();
  for(int i = 0; i < numEdges; ++i) {
    pair<int,int> &e = E[i].second;
    if(!sets.equal(e.first, e.second)) {
      sets.link(e.first, e.second);
      tree[e.first].push_back(make_pair(e.second, E[i].first));
      tree[e.second].push_back(make_pair(e.first, E[i].first));
    }
  }
}
