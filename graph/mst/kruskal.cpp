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
 *****************************************************************************/

#include <algorithm>
#include <vector>

#include "sets.cpp"

template<class V>
void kruskal( const V &graph, V &tree, int n ) {
  typedef typename V::value_type              E;
  typedef typename E::const_iterator          E_iter;
  typedef typename E::value_type::second_type D;

  sets sets(n);
  vector< pair< D,pair<int,int> > > edges;

  // Convert all edges into a single edge-list
  for( int i=0; i<n; i++ ) {
    for( E_iter iter=graph[i].begin(); iter!=graph[i].end(); iter++ ) {
      if( i < (*iter).first ) // Undirected: only use half of the edges
	edges.push_back( make_pair((*iter).second,
				   make_pair(i,(*iter).first)) );
    }
  }

  // Clear tree
  for( int i=0; i<n; i++ )
    tree[i].clear();

  sort( edges.begin(), edges.end() );

  // Add edges in order of non-decreasing weight
  int numEdges = edges.size();
  for( int i=0; i<numEdges; i++ ) {
    pair<int,int>  &edge = edges[i].second;

    // Add edge if the edge-endpoints aren't in the same set
    if( !sets.equal(edge.first, edge.second) ) {
      sets.link( edge.first, edge.second );
      tree[edge.first].push_back( make_pair(edge.second, edges[i].first) );
      tree[edge.second].push_back( make_pair(edge.first, edges[i].first) );
    }
  }
}
