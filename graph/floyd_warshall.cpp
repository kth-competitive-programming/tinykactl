/* KTH ACM Contest Template Library
 *
 * Graph/Shortest Path/Floyd-Warshall
 *
 * Credit:
 *   By David Rydh
 */

template<class V1, class V2>
void floyd_warshall( V1 &adj, V2 &path, int n ) {
  for( int x=0; x<n; x++ )
    for( int y=0; y<n; y++ )
      path[x][y] = -1;

  for( int m=0; m<n; m++ )
    for( int x=0; x<n; x++ )
      if( adj[x][m] >= 0 )
	for( int y=0; y<n; y++ )
	  if( adj[m][y] >= 0 )
	    if( adj[x][y] < 0 || adj[x][m] + adj[m][y] < adj[x][y] ) {
	      adj[x][y] = adj[x][m] + adj[m][y];
	      path[x][y] = m;
	    }
}
