/*****************************************************************************
 * 
 * MaxFlow2: fulkerson1 (Ford-Fulkerson for bipartite matching)
 * ============================================================
 *
 * A Maximum Flow algorithm based upon Ford-Fulkersons method with
 * DFS search. All augmenting path have flow 1 and this algorithm is
 * thus suited for bipartite matching graphs.
 *
 * COMPLEXITY: O(E*numPaths)
 *
 * REQUIRES:   maxflow/1_general.cpp
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

#include "1_general.cpp"

// Function prototypes
bool flow_increase1( FlowGraph &g, int source, int sink );

// Internal auxillary function
bool flow_dfs1( FlowGraph &g, vector<int> &proc, int source, int sink );


bool flow_increase1( FlowGraph &g, int source, int sink ) {
  vector<int> proc;     // in reality bool but vector<bool> is slower

  proc.resize( g.size(), false );

  return flow_dfs1( g, proc, source, sink );
}

bool flow_dfs1( FlowGraph &g, vector<int> &proc, int node, int sink ) {
  typedef vector<FlowEdge>::iterator  E_iter;
  typedef vector<FlowEdge>            E;
  bool found = false;

  proc[node] = true;

  E & el = g[node];
  for( E_iter e=el.begin(); e!=el.end(); e++ ) {
    if( (*e).cap <= 0 )
      continue;

    int destNode = (*e).destNode;

    if( !proc[destNode] ) {
      // Process this node
      if( destNode == sink || flow_dfs1(g,proc,destNode,sink) ) {
	// Found augmenting path - add flow 1
	(*e).cap--;
	g[destNode][(*e).backEdgeIndex].cap++;

        found = true;
        break;
      }
    }
  }

  return found;
}
