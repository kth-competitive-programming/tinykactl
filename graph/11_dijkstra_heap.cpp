/*****************************************************************************
 * 
 * Graph4: dijkstra_heap (no maps)
 * ===============================
 *
 * Find the shortest path from a given vertex to all of the V vertices in
 * a (directed) graph with non-negative lengths.
 *
 * INPUT
 * -----
 * edges:  A vector with V edge-containers. The edge-containers should
 *         contain pairs (vertix, distance) and edges[vertix] should be the
 *         edge-list for the vertix "vertix". All distances must be positive.
 *
 *         (this allows edges to be a vector of (multi)maps or vectors etc)
 *
 * start:  The vertix from which the shortest path should be calculated.
 *
 * V:      The number of vertices.
 *
 * OUTPUT
 * ------
 * min:    (A vector of the same size as edges.)
 *         At the end of the function, min[vertix] will contain the shortest
 *         path between "start" and "vertix" or -1 if no path was found.
 *
 * from_path: (A vector of the same size as edges.)
 *         from_path[x] contains the vertix, y, from which the vertix
 *         x was entered (OPTIONAL, set to NULL if not wanted)
 *
 * COMPLEXITY  O(V * log V)
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

// S is a random access iterator into a container containing
// sequences (vector, list) with pairs of node-indices (edge-lists)
// and distances (type DIST).

// R is a random access iterator into a container containing
// distances (type DIST).

// T is a random access iterator into a container containing
// node-indices of size V.

template<class R, class S, class T>
void shortest_path_heap( const S edges, R min, T from, int start, int V ) {
  typedef S::value_type      E;
  typedef E::const_iterator  E_iter;

  struct dijkstra_vertix {
    int  nr;

    bool operator<( const dijkstra_vertix &x ) {
      return min[nr] > min[x.nr];  // We want the LEAST value
    }

    void set_position( int pos ) {
      inverse[nr] = pos;
    }
  };

  typedef R::value_type      DIST;
  upd_heap<DijkstraVertix>   heap();
  vector<int>                inverse;
  const DIST                 inf = (DIST)0x20000000;

  // Initialize min/from
  for( int i=0; i<V; i++ ) {
    min[i] = inf;
    from[i] = -1; // ***
  }
  min[start] = 0;


  // Initialize heap
  inverse.resize( V );
  for( int i=0; i<V; i++ )
    heap.push( i );


  // Find shortest path
  while( !heap.empty() ) {
    int   node = heap.top();
    heap.pop();
    if( min[node] == inf )    // the rest of the nodes are unreachable
      break;

    // Process node
    for( E_iter e=S[node].begin(); e!=S[node].end(); e++ ) {
      int destNode = (*e).first;

      if( inverse[destNode] >= 0 &&
	  min[node]+(*e).second < min[destNode] )
	{
	  min[destNode] = min[node]+(*e).second;
	  heap.key_increased( inverse[destNode] );

	  from[destNode] = node; // ***
	}
    }
  }

  for( int i=0; i<V; i++ ) {
    if( min[i] == inf )
      min[i] = -1;
  }
}
