/* KTH ACM Contest Template Library
 *
 * Graph/Network Flow/Fulkerson 1
 *
 * A Maximum Flow algorithm based upon Ford-Fulkersons method with
 * DFS search. All augmenting path have flow 1 and this algorithm is
 * thus suited for bipartite matching graphs.
 *
 * The maximum flow is calculated by repetitive calls to flow_increase1
 *
 * Complexity: O(E*numPaths)
 *
 * Credit:
 *   By David Rydh
 */

#include "flow_graph.cpp"

// Function prototypes
bool flow_increase1( flow_graph &g, int source, int sink );
// Internal auxillary function
bool flow_dfs1( flow_graph &g, vector<int> &proc, int source, int sink );


bool flow_increase1( flow_graph &g, int source, int sink ) {
  vector<int> proc;     // in reality bool but vector<bool> is slower

  proc.resize( g.size(), false );

  return flow_dfs1( g, proc, source, sink );
}

bool flow_dfs1( flow_graph &g, vector<int> &proc, int node, int sink ) {
  typedef vector<flow_edge<int> >::iterator  E_iter;
  typedef vector<flow_edge<int> >            E;
  bool found = false;

  proc[node] = true;

  E & el = g[node];
  for( E_iter e=el.begin(); e!=el.end(); e++ ) {
    if( e->c <= 0 )
      continue;

    int dest = e->dest;

    if( !proc[dest] ) {
      // Process this node
      if( dest == sink || flow_dfs1(g,proc,dest,sink) ) {
	// Found augmenting path - add flow 1
	e->f++; e->c--;
	g[dest][e->back].f--; g[dest][e->back].c++;

        found = true;
        break;
      }
    }
  }

  return found;
}
