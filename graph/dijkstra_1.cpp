/* KTH ACM Contest Template Library
 *
 * Graph/Shortest Path/Dijkstra 1
 *
 * Find the shortest path from a given vertex to all of the V vertices in
 * a (directed) graph where all lengths are 1.
 *
 * Credit:
 *   By David Rydh
 */

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
