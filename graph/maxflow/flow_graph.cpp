/*****************************************************************************
 * 
 * MaxFlow1: General structures for maxflow-algortihs
 * ==================================================
 *
 * Find the maximum flow. The functions are all based on the FlowGraph
 * data structure which is a vector of vectors with FlowEdges. The
 * FlowEdge describes an edge with an allowed flow together with a
 * pointer (index) to its opposite back-edge.
 *
 * Flows are added to the graph with the add_edge function. NB! The
 * flow for are a edge and its back-edge must be given at the same time
 * and only once.
 *
 * The maximum flow are calculated by repetitive calls to increase_flow
 * or increase_flow1. The last function is an optimized version where
 * all augmenting paths have the flow 0/1 (e.g. a bipartite matching).
 *
 * increase_flow and increase_flow1 both have complexity O(E).
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

#include <vector>

/***************************************
 * General Max-flow structures/functions
 ***************************************/

struct FlowEdge {
  int  destNode;
  int  cap;             // The amount of flow that this edge can allow
  int  backEdgeIndex;   // The index of the back-edge in graph[destNode]

  FlowEdge( int a=-1, int b=0, int c=-1 ) : destNode(a), cap(b),
                                            backEdgeIndex(c) {}
};

typedef vector< vector<FlowEdge> > FlowGraph;

void flow_addedge( FlowGraph &g, int start, int end, int cap, int back_cap=0 ){
  g[start].push_back( FlowEdge(end, cap, g[end].size()) );
  g[end].push_back( FlowEdge(start, back_cap, g[start].size()-1) );
}

