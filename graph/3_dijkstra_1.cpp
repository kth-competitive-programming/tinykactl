/*****************************************************************************
 * 
 * Graph3: dijkstra_vector_1 (no maps, equvivalent to bfs)
 * =======================================================
 *
 * Find the shortest path from a given vertex to all of the V vertices in
 * a (directed) graph where all lengths are 1.
 *
 * INPUT
 * -----
 * edges:  A vector with V edge-containers. The edge-containers should
 *         contain vertix numbers. (e.g. they could be (multi)sets)
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
 *         x was entered
 *
 * COMPLEXITY  O(E+V)
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

#include <queue>


template<class V, class S, class T>
void dijkstra_1( const V &edges, S &min, T &from, int start, int n ) {
  typedef typename V::value_type::const_iterator  E_iter;
  const int inf = 1 << 29;
  queue<int> q;

  // Initialize min
  for( int i=0; i<n; i++ ) {
    min[i] = inf;
    from[i] = -1;  // ****
  }
  min[start] = 0;

  q.push( start );

  while( !q.empty() ) {
    int node = q.front();
    int length = min[node]+1;

    q.pop();
 
    // Process node
    for( E_iter e=edges[node].begin(); e!=edges[node].end(); e++ ) {
      int destNode = *e;

      if( length < min[destNode] ) {
	// Process this node the next run
	min[destNode] = length;
	q.push( destNode );

	from[destNode] = node; // ****
      }
    }
  }

  for( int i=0; i<n; i++ ) {
    if( min[i] == inf )
      min[i] = -1;
  }
}
