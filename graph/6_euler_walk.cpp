/*****************************************************************************
 * 
 * Graph6: euler_walk
 * ==================
 *
 * Find an eulerian walk in a directed graph, i.e. a walk traversing all
 * edges exactly once.
 *
 * The algorithm ASSUMES that there is an eulerian walk. If there isn't,
 * it will return a maximal path which neccessarily isn't the longest.
 *
 * If the graph isn't cyclic, the start node must be a node with
 * outDegree-inDegree = 1.
 *
 * euler_walk can be used to test if a graph has an eulerian walk by first
 * finding a start-node (or any node if it is cyclic) and then checking
 * if path.size() == nrOfEdges+1. But obviously this is slower than checking
 * all degrees and if the graph is connected.
 *
 * INPUT
 * -----
 * edges:  A vector with V edge-containers. The edge-containers should
 *         contain vertix-indices. (e.g. they could be (multi)sets)
 *         WARNING! The edges will be modified and emptied.
 *
 * start:  The vertix from which the eulerian path should begin.
 *
 * cyclic: true if the path must be cyclic.
 *
 * OUTPUT
 * ------
 * path:   (At start an empty list of integers)
 *         At the end of the function, "path" will contain the euler-path
 *         given as VERTIX numbers. If the path is cyclic the last vertix
 *         will be "start".
 *
 * COMPLEXITY  O( E )
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

template<class V>
void euler_walk( V &edges, int start, list< int > &path, bool cyclic=false ) {
  int node = start, next_node;

  // Find a maximal path
  while( true ) {
    typename V::value_type &s = edges[node];

    path.push_back( node );

    if( s.empty() )
      break;

    // Follow the first edge and remove it
    next_node = *s.begin();
    s.erase( s.begin() );

    node = next_node;
  }

  // If no cyclic path was found, return an "empty" path, i.e. only the start node
  if( cyclic && node != start ) {
    path.clear();
    path.push_back( node );
    return;
  }

  // Extend path with cycles
  for( list<int>::iterator iter = path.begin(); iter != path.end(); iter++ ) {
    node = *iter;

    typename V::value_type &s = edges[node];

    while( !s.empty() ) {
      list<int>  extra_list;

      euler_walk( edges, node, extra_list, true /*must be cyclic*/ );

      path.splice( iter, extra_list, extra_list.begin(), --extra_list.end() );
    }
  }
}
