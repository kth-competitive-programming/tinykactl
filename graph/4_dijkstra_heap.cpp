/*****************************************************************************
 * 
 * Graph4: dijkstra (with heap, no maps)
 * =====================================
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
 *         (this allows edges to be a vector of (multi)maps or vectors etc,
 *         but note that maps are slower to iterate than vectors)
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
 * COMPLEXITY  O( (V+E)*log V )
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

#include <algorithm>

template<class V, class M, class T>
// T may be int, double etc (INFINITY may have to be changed)
void dijkstra_heap( const V &edges, M &min, T &from,
		    int start, int n )
{
  typedef typename V::value_type::const_iterator E_iter;
  typedef typename M::value_type DIST;
  const DIST inf = (DIST)0x20000000;

  vector<int>   heap, heapIndex;
  int           heapSize;


  for( int i=0; i<n; i++ ) {
    min[i] = inf;
    from[i] = -1; // ***
  }
  min[start] = 0;

  // Initialize heap
  heap.resize( n );
  heapIndex.resize( n );
  heapSize = n;
  for( int i=0; i<n; i++ )
    heap[i] = heapIndex[i] = i;

  heap[0] = start; heapIndex[start] = 0;
  heap[start] = 0; heapIndex[0] = start;

  // Find shortest path
  while( heapSize > 0 ) {
    int    node, parent, child;

    // Remove head of heap
    node = heap[0];
    heapIndex[node] = -1;    // no longer in heap
    heap[0] = heap[heapSize-1];
    heapIndex[heap[0]] = 0;
    heapSize--;

    if( min[node] == inf )    // the rest of the nodes are unreachable
      break;

    // Heapify
    parent = 0;
    child = 1;
    while( child < heapSize ) {
      if( child+1 < heapSize && min[heap[child+1]] < min[heap[child]] )
	child++;
      if( min[heap[parent]] < min[heap[child]] )
	break;
      swap( heap[parent], heap[child] );
      swap( heapIndex[heap[parent]], heapIndex[heap[child]] );
      parent = child;
      child = parent*2+1;
    }

    // Process node
    for( E_iter e=edges[node].begin(); e!=edges[node].end(); e++ ) {
      int destNode = (*e).first;

      if( heapIndex[destNode]>=0 &&
	  min[node]+(*e).second < min[destNode] )
	{
	  min[destNode] = min[node]+(*e).second;
	  from[destNode] = node; // ***

	  // Update heap
	  child = heapIndex[destNode];
	  while( child > 0 ) {
	    parent = (child-1)/2;
	    if( min[heap[parent]] < min[heap[child]] )
	      break;
	    swap( heap[parent], heap[child] );
	    swap( heapIndex[heap[parent]], heapIndex[heap[child]] );
	    child = parent;
	  }
	}
    }
  }

  for( int i=0; i<n; i++ ) {
    if( min[i] == inf )
      min[i] = -1;
  }
}
