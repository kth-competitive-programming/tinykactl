/* KTH ACM Contest Template Library
 *
 * Graph/Network Flow/Ford Fulkerson
 *
 * A Maximum Flow algorithm based upon Ford-Fulkersons method with
 * either BFS or DFS search.
 *
 * Complexity: O(E*numPaths)
 *
 * Credit:
 *   By David Rydh
 */

#include <queue>
#include "flow_graph.cpp"

// Function prototypes
int flow_increase1( flow_graph &g, int source, int sink );

// Internal auxillary functions
void flow_findaugpath_dfs( const flow_graph &g, vector<int> &backEdges,
                       int source, int sink );
void flow_findaugpath_bfs( const flow_graph &g, vector<int> &backEdges,
                       int source, int sink );


/************************************************************
 * Max-flow in a general flow-graph
 ************************************************************/

int flow_increase( flow_graph &g, int source, int sink ) {
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
    flow_edge<int> &backEdge = g[node][backEdges[node]];
    flow_edge<int> &forwardEdge = g[backEdge.dest][backEdge.back];

    if( forwardEdge.c < minSlack )
      minSlack = forwardEdge.c;

    node = backEdge.dest;
  }

  // Increase flow
  for( int node=sink; node!=source; ) {
    flow_edge<int> &backEdge = g[node][backEdges[node]];
    flow_edge<int> &forwardEdge = g[backEdge.dest][backEdge.back];

    forwardEdge.c -= minSlack;
    backEdge.c += minSlack;

    node = backEdge.dest;
  }

  return minSlack;
}


// The backEdges is an array containing the index of the backEdge
// which should be followed to get back to the source

void flow_findaugpath_bfs( const flow_graph &g, vector<int> &backEdges,
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
    const vector<flow_edge<int>>   &edges = g[node];
    int                            numEdges = edges.size();
    for( int i=0; i<numEdges; i++ ) {
      const flow_edge &fe = edges[i];

      if( fe.c <= 0 )
	continue;

      int dest = fe.dest;

      if( length < min[dest] ) {
	// Process this node the next run
	min[dest] = length;
        backEdges[dest] = fe.back;
	q.push( dest );

	if( dest == sink )
	  return;
      }
    }
  }
}

// The backEdges is an array containing the index of the backEdge
// which should be followed to get back to the source.
// Make sure backEdges is initialized to -1 prior to this function
// except for the source which should have a value >=0!

bool flow_findaugpath_dfs( flow_graph &g, vector<int> &backEdges,
                           int node, int sink )
{
  typedef vector<flow_edge<int> >::iterator  E_iter;
  typedef vector<flow_edge<int> >            E;

  E & el = g[node];
  for( E_iter e=el.begin(); e!=el.end(); e++ ) {
    if( (*e).c <= 0 )
      continue;

    int dest = (*e).dest;

    if( backEdges[dest] < 0 ) {
      // Process this node
      backEdges[dest] = (*e).backEdge;

      if( dest == sink || flow_findaugpath_dfs(g,backEdges,dest,sink) )
        // Found augmenting path
        return true;
    }
  }

  return false;
}
