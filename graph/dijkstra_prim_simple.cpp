/* KTH ACM Contest Template Library
 *
 * Graph/Shortest Path and Minimum Spanning Tree/Dijkstra and Prim Simple
 *
 * Credit:
 *   Dijkstra
 *   By David Rydh
 */

template<class E, class M, class P>
void dijkstra( const E &edges, M &min, P &path, int start, int n,
	       bool mst = false ) {
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
    int node = -1;
    T   least = inf;

    for( int i=0; i<n; i++ )
      if( !proc[i] && min[i] < least )
        node = i, least = min[i];
    if( node < 0 ) break;

    if( mst ) min[node] = T();
    typedef typename E::value_type L;
    typedef typename L::const_iterator L_iter;

    const L &l = edges[node];
    for( L_iter it=l.begin(); it!=l.end(); ++it ) {
      int dest = (*it).first;
      T dist = min[node]+(*it).second;

      if( !proc[dest] && dist < min[dest] ) {
        min[dest] = dist;
	path[dest] = node;
      }
    }

    proc[node] = true;
  }
}
