/* KTH ACM Contest Template Library
 *
 * Graph/Euler Cycle/Euler Walk
 *
 * Credit:
 *   Leonhard Euler
 *   by David Rydh
 */

#include <list>

template<class V>
void euler_walk( V &edges, int start, list< int > &path, bool cyclic=false ) {
  int node = start, next_node;
  // Find a maximal path
  while(true) {
    typename V::value_type &s = edges[node];
    path.push_back(node);
    if(s.empty()) break;
    // Follow the first edge and remove it
    next_node = *s.begin();
    s.erase( s.begin() );
    node = next_node;
  }

  // If no cyclic path was found, return "empty" path.
  if(cyclic && node != start) {
    path.clear();
    path.push_back( node );
    return;
  }

  // Extend path with cycles
  for(list<int>::iterator it=--path.end(); it!=path.begin();) {
    list<int>::iterator iter2 = iter; iter2--;
    node = *iter;
    typename V::value_type &s = edges[node];
    while(!s.empty()) {
      list<int> add;
      euler_walk(edges, node, add, true /* must be cyclic */);
      path.splice(it, add, add.begin(), --add.end() );
    }
    it = iter2;
  }
}
