/* KTH ACM Contest Template Library
 *
 * Graph/Shortest Path/Dijkstra
 *
 * Credit:
 *   Dijkstra
 *   By David Rydh
 */

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
 *         contain pairs (vertex, distance) and edges[vertex] should be the
 *         edge-list for the vertex "vertex". All distances must be positive.
 *
 *         (this allows edges to be a vector of (multi)maps or vectors etc)
 *
 * start:  The vertex from which the shortest path should be calculated.
 *
 * V:      The number of vertices.
 *
 * OUTPUT
 * ------
 * min:    (A vector of the same size as edges.)
 *         At the end of the function, min[vertix] will contain the shortest
 *         path between "start" and "vertex" or -1 if no path was found.
 *
 * from_path: (A vector of the same size as edges.)
 *         from_path[x] contains the vertex, y, from which the vertex
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

template<class E, class M, class P>
void dijkstra( const E &edges, M &min, P &path, int start, int n ) {
  typedef typename E::value_type L;
  typedef typename L::const_iterator L_iter;
  typedef typename M::value_type T;
  T inf(1<<29);

  // Initialize min & path
  for( int i=0; i<n; i++ ) {
    min[i] = inf;
    path[i] = -1;
  }
  min[start] = T();

  // Initalize proc
  vector<bool> proc( n, false );

  // Find shortest path
  while( true ) {
    int node;
    T   least = inf;

    for( int i=0; i<n; i++ )
      if( !proc[i] && min[i] < least )
        node = i, least = min[i];
    if( least == inf )    // the rest of the nodes are unreachable
      break;

    // Process node
    const L &l = edges[node];
    for( L_iter e=l.begin(); e!=l.end(); ++e ) {
      int destNode = (*e).first;

      if( !proc[destNode] && min[node]+(*e).second < min[destNode]) {
        min[destNode] = min[node] + (*e).second;
	path[destNode] = node;
      }
    }

    proc[node] = true;
  }
}
