/*****************************************************************************
 * 
 * Graph2: dijkstra (without heap, no maps)
 * ========================================
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
 *         x was entered.
 *
 * COMPLEXITY  O(V^2+E)
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

template<class V, class M, class T>
void dijkstra( const V &edges, M &min, T &from, int start, int n )
{
  typedef typename V::value_type::const_iterator E_iter;
  typedef typename M::value_type DIST;
  const DIST inf = (DIST)0x20000000;

  // Initialize min & from
  for( int i=0; i<n; i++ ) {
    min[i] = inf;
    from[i] = -1; // ***
  }
  min[start] = 0;


  // Initalize processed
  vector<bool>   processed;
  processed.resize( n, false );


  // Find shortest path
  while( true ) {
    int  node;
    DIST least = inf;

    for( int i=0; i<n; i++ ) {
      if( !processed[i] && min[i] < least ) {
        node = i;
        least = min[i];
      }
    }

    if( least == inf )    // the rest of the nodes are unreachable
      break;


    // Process node
    for( E_iter e=edges[node].begin(); e!=edges[node].end(); e++ ) {
      int destNode = (*e).first;

      if( !processed[destNode] && min[node]+(*e).second < min[destNode]) {
        min[destNode] = min[node] + (*e).second;
	from[destNode] = node; // ***
      }
    }

    processed[node] = true;
  }

  // Update min to -1 if inf
  for( int i=0; i<n; i++ ) {
    if( min[i] == inf )
      min[i] = -1;
  }
}
