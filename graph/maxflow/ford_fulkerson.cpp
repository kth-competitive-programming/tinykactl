/*****************************************************************************
 * 
 * MaxFlow3: fulkerson (Ford-Fulkerson for general flow networks)
 * ==============================================================
 *
 * A Maximum Flow algorithm based upon Ford-Fulkersons method with
 * either BFS or DFS search.
 *
 * COMPLEXITY: O(E*numPaths)
 *
 * REQUIRES:   maxflow/1_general.cpp
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

#include <queue>
#include "1_general.cpp"

// Function prototypes
bool flow_increase1( FlowGraph &g, int source, int sink );

// Internal auxillary functions
void flow_findaugpath_dfs( const FlowGraph &g, vector<int> &backEdges,
                       int source, int sink );
void flow_findaugpath_bfs( const FlowGraph &g, vector<int> &backEdges,
                       int source, int sink );


/************************************************************
 * Max-flow in a general flow-graph
 ************************************************************/

int flow_increase( FlowGraph &g, int source, int sink ) {
  const int   inf = 0x20000000;
  vector<int> backEdges;

  backEdges.resize( g.size(), -1 );
  backEdges[source] = 0; // backEdges>=0 is also used to mark
  // if the node has been traversed

  // Find augmenting path (choose one of these)
  flow_findaugpath_dfs( g, backEdges, source, sink );
  //  flow_findaugpath_bfs( g, backEdges, source, sink );

  if( backEdges[sink] < 0 )
    return 0;

  // Find min-slack
  int  minSlack = inf;

  for( int node=sink; node!=source; ) {
    FlowEdge &backEdge = g[node][backEdges[node]];
    FlowEdge &forwardEdge = g[backEdge.destNode][backEdge.backEdgeIndex];

    if( forwardEdge.cap < minSlack )
      minSlack = forwardEdge.cap;

    node = backEdge.destNode;
  }

  // Increase flow
  for( int node=sink; node!=source; ) {
    FlowEdge &backEdge = g[node][backEdges[node]];
    FlowEdge &forwardEdge = g[backEdge.destNode][backEdge.backEdgeIndex];

    forwardEdge.cap -= minSlack;
    backEdge.cap += minSlack;

    node = backEdge.destNode;
  }

  return minSlack;
}


// The backEdges is an array containing the index of the backEdge
// which should be followed to get back to the source

void flow_findaugpath_bfs( const FlowGraph &g, vector<int> &backEdges,
		       int source, int sink )
{
  const int   inf = 0x20000000;
  queue<int>  q;
  vector<int> min;

  min.resize( g.size() );

  // Initialize min/backEdges
  int n = g.size();
  for( int i=0; i<n; i++ ) {
    min[i] = inf;
    backEdges[i] = -1;
  }
  min[source] = 0;

  // BFS-search
  q.push( source );

  while( !q.empty() ) {
    int node = q.front();
    int length = min[node]+1;

    q.pop();

    // Process node
    const vector<FlowEdge>   &edges = g[node];
    int                      numEdges = edges.size();
    for( int i=0; i<numEdges; i++ ) {
      const FlowEdge &fe = edges[i];

      if( fe.cap <= 0 )
	continue;

      int destNode = fe.destNode;

      if( length < min[destNode] ) {
	// Process this node the next run
	min[destNode] = length;
        backEdges[destNode] = fe.backEdgeIndex;
	q.push( destNode );

	if( destNode == sink )
	  return;
      }
    }
  }
}

// The backEdges is an array containing the index of the backEdge
// which should be followed to get back to the source.
// Make sure backEdges is initialized to -1 prior to this function
// except for the source which should have a value >=0!

bool flow_findaugpath_dfs( FlowGraph &g, vector<int> &backEdges,
                           int node, int sink )
{
  typedef vector<FlowEdge>::iterator  E_iter;
  typedef vector<FlowEdge>            E;

  E & el = g[node];
  for( E_iter e=el.begin(); e!=el.end(); e++ ) {
    if( (*e).cap <= 0 )
      continue;

    int destNode = (*e).destNode;

    if( backEdges[destNode] < 0 ) {
      // Process this node
      backEdges[destNode] = (*e).backEdgeIndex;

      if( destNode == sink || flow_findaugpath_dfs(g,backEdges,destNode,sink) )
        // Found augmenting path
        return true;
    }
  }

  return false;
}
