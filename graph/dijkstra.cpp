/* KTH ACM Contest Template Library
 *
 * Graph/Shortest Path/Dijkstra
 *
 * Credit:
 *   Dijkstra
 *   By David Rydh
 */

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
