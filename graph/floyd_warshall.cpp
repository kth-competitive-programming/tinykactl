/*****************************************************************************
 * 
 * Graph1: floyd_warshall & transitive_closure
 * ===========================================
 *
 * Find the shortest path between all pairs of the V vertices in a
 * (directed) graph.
 *
 * Find the transitive closure and any path between the connected vertices.
 *
 * INPUT
 * -----
 * adj:  a n*n matrix describing the length of the edges. The lengths must be
 *       positive. If there is no edge between x and y adj[x][y] should be < 0.
 *       (A[x][x] can but does not need to be 0.)
 *       (WARNING! Even if it is possible to pass an vector/map containing
 *       vectors/maps, it is MUCH slower than an array since a double
 *       dereferencing is made several times. This could of course easily
 *       be fixed. Maps is VERY slow anyhow since EVERY element will be
 *       added, making it in reality a vector.)
 *       for transitive closure the adjacency matrix is a bool matrix.
 *
 *
 * n:    the number of vertices
 *
 * OUTPUT
 * ------
 * adj:  At the end of the function, A[x][y] will contain the shortest path
 *       between x and y or -1 if no path was found.
 * from_paths:
 *       from_paths[x][y] contains for each pair of nodes (x,y), the node
 *       from which the node y was entered if the path began with x.
 *
 * COMPLEXITY  O(V^3)
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


template<class V, class T>
void floyd_warshall( V &adj, T &from_paths, int n ) {
  for( int x=0; x<n; x++ )
    for( int y=0; y<n; y++ )
      from_paths[x][y] = -1;      // **

  for( int m=0; m<n; m++ )
    for( int x=0; x<n; x++ )
      if( adj[x][m] >= 0 )
	for( int y=0; y<n; y++ )
	  if( adj[m][y] >= 0 )
	    if( adj[x][y]<0 || adj[x][m] + adj[m][y] < adj[x][y] ) {
	      adj[x][y] = adj[x][m] + adj[m][y];
	      from_paths[x][y] = m;     // **
	    }
}

template<class V, class T>    // V is a bool n*n matrix
void transitive_closure( V &adj, T &from_paths, int n ) {
  for( int x=0; x<n; x++ )
    for( int y=0; y<n; y++ )
      from_paths[x][y] = -1;      // **

  for( int m=0; m<n; m++ )
    for( int x=0; x<n; x++ )
      if( adj[x][m] )
	for( int y=0; y<n; y++ )
	  if( adj[m][y] ) {
	    adj[x][y] = true;
	    from_paths[x][y] = m;     // **
	  }
}
