/* KTH ACM Contest Template Library
 *
 * Graph/Transitive Closure/Transitive Closure
 *
 * Find the transitive closure and any path between the connected vertices.
 *
 * Credit:
 *   By David Rydh
 */

template<class V, class T>    // V is a bool n*n matrix
void transitive_closure( V &adj, T &paths, int n ) {
  for( int x=0; x<n; x++ )
    for( int y=0; y<n; y++ )
      paths[x][y] = -1;

  for( int m=0; m<n; m++ )
    for( int x=0; x<n; x++ )
      if( adj[x][m] )
	for( int y=0; y<n; y++ )
	  if( adj[m][y] ) {
	    adj[x][y] = true;
	    paths[x][y] = m;
	  }
}

