/*****************************************************************************
 * 
 * Graph10: dijkstra_general (without heap, general with map/vector)
 * =================================================================
 *
 * Find the shortest path from a given vertex to all of the V vertices in
 * a (directed) graph with non-negative lengths.
 *
 * INPUT
 * -----
 * edges:  A container with V edge-containers. The edge-containers should
 *         contain pairs (vertix, distance) and edges[vertix] should be the
 *         edge-list for the vertix "vertix". All distances must be positive.
 *
 *         (this allows edges to be a map of (multi)maps or a vector of
 *         vectors etc. WARNING! All vertices must be present in "edges"
 *         even if they don't have any outgoing edges.)
 *
 * start:  The vertix from which the shortest path should be calculated.
 *
 * V:      The number of vertices.
 *
 * OUTPUT
 * ------
 * min:    At the end of the function, min[vertix] will contain the shortest
 *         path between "start" and "vertix" or -1 if no path was found.
 *
 * from_path:
 *         from_path[x] contains the vertix, y, from which the vertix
 *         x was entered (OPTIONAL, set to NULL if not wanted)
 *
 * COMPLEXITY  O(V^2 * log V)
 *
 * REQUIRES    general/indexed_container.cpp
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

#include <map>
#include "../general/10_indexed_container.cpp"

template<class V, class M, class T>
void dijkstra_general( V &edges, M &min, T *from,
               typename indexed_container<T>::index_type start )
{
  typedef indexed_container<V> V_help;
  typedef indexed_container<M> M_help;
  typedef typename V_help::index_type I;
  typedef typename V::const_iterator V_iter;
  typedef typename M::iterator M_iter;
  typedef typename V_help::value_type E;
  typedef typename E::const_iterator E_iter;
  typedef typename indexed_container<M>::value_type DIST;
  const DIST inf = (DIST)0x20000000;

  // Initialize min & from
  for( V_iter iter=edges.begin(); iter!=edges.end(); iter++ ) {
    I  i = V_help::indexof(edges, iter);

    cout << i << endl;
    min[i] = inf;
    if( from )
      (*from)[i] = -1;
  }
  min[start] = 0;


  // Initalize processed
  map< I, bool >   processed;


  // Find shortest path
  while( true ) {
    I    node;
    DIST least = inf;

    for( M_iter iter=min.begin(); iter!=min.end(); iter++ ) {
      I  i = M_help::indexof(min, iter);

      if( !processed[i] && M_help::valueof(min, iter) < least ) {
        node = i;
        least = M_help::valueof(min, iter);
      }
    }

    if( least == inf )    // the rest of the nodes are unreachable
      break;


    // Process node
    E &elist = edges[node];  // may create new edgelist if node doesn't exist.

    for( E_iter e=elist.begin(); e!=elist.end(); e++ ) {
      I destNode = (*e).first;

      if( !processed[destNode] && min[node]+(*e).second < min[destNode]) {
        min[destNode] = min[node] + (*e).second;
	if( from )
	  (*from)[destNode] = node;
      }
    }

    processed[node] = true;
  }

  // Update min to -1 if inf
  for( V_iter iter=edges.begin(); iter!=edges.end(); iter++ ) {
    I  i = V_help::indexof(edges, iter);

    if( min[i] == inf )
      min[i] = -1;
  }
}
