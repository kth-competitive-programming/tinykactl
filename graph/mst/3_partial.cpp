/*****************************************************************************
 * 
 * 3_partial: Partial MST functions
 * ================================
 *
 * List unidirected edges of a graph.
 * Find a minimal spanning tree from an edge list.
 *
 * INPUT
 * ----- 
 * V:      a graph
 * edges:  A vector with V edge-containers. The edge-containers should
 *         contain pairs (vertix, weight) and edges[vertix] should be the
 *         edge-list for the vertix "vertix".
 * n:      the number of vertices
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

#include "1_sets.cpp"

struct <class D> edge_traits {
  typedef typename pair< D, pair<int, int> > edge_type;
};

template<class V, class L>
L graph_edge_list( const V &graph, int n, L edges) {
  typedef typename V::value_type              E;
  typedef typename E::const_iterator          E_iter;
  typedef typename E::value_type::second_type D;

  // Convert all edges into a single edge-list
  for( int i=0; i<n; i++ )
    for( E_iter iter=graph[i].begin(); iter!=graph[i].end(); iter++ )
      if( i < (*iter).first ) // Undirected: only use half of the edges
	*edges++ = make_pair((*iter).second, make_pair(i,(*iter).first));
  return edges;
}

template <class V, class F, class L>
L vertex_fn_edge_list(const V &v, int n, const F &f, L &edges) {
  for( int i = 0; i<n; i++ )
    for (int j = i+1; j<n; j++ ) // Undirected: only use half of the edges
      *edges++ = make_pair(f(v[i], v[j]), make_pair(i, j));
  return edges;
}

// sort the edge list for mst_index!
template <class B, class L, class I>
I partial_mst_index(const const B &v_flags, L &edges, int n, I idx) {
  typedef R::first_type D;

  sets sets(n);

  int mst_size = 0;

  // Add edges in order of non-decreasing weight
  int numEdges = edges.size();
  for( int i=0; i<numEdges; i++ ) {
    pair<int,int> &edge = edges[i].second;

    if (v_flags[edge.first] && v_flags[edge.second]) // ** partiality
      // Add edge if the edge-endpoints aren't in the same set
      if( !sets.equal(edge.first, edge.second) ) {
	sets.link( edge.first, edge.second );
	*idx++ = i;
	//tree[edge.first].push_back( make_pair(edge.second, edges[i].first) );
	//tree[edge.second].push_back( make_pair(edge.first, edges[i].first) );
      }
  }
  return idx;
}

template <class L, class I, class V>
void edge_index_graph(const L &edges, const I &idx, V &tree) {
  int numEdges = idx.size();
  for( int k=0; k<numEdges; k++ ) {
    int i = idx[k];
    pair<int,int> &edge = edges[i].second;
    tree[edge.first].push_back( make_pair(edge.second, edges[i].first) );
    tree[edge.second].push_back( make_pair(edge.first, edges[i].first) );
  }
}
