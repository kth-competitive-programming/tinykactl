/* KTH ACM Contest Template Library
 *
 * Graph/Network Flow/Flow Graph
 *
 * The functions are all based on a flow_graph which is a container
 * with vectors with flow_edge's. The flow_edge describes an edge with an
 * allowed flow together with a pointer (index) to its opposite back-edge.
 *
 * Flows are added to the graph with the add_edge function. NB! The
 * flow for are a edge and its back-edge must be given at the same time
 * and only once.
 *
 * Credit:
 *   By David Rydh and Mattias de Zalenski
 */

#include <vector>


template <class T>
struct flow_edge {
  typedef T flow_type;
  int dest, back; // back is the index of the back-edge in graph[dest]
  T c, f; // capacity and flow
  flow_edge() {}
  flow_edge(int _dest, int _back, T _c, T _f = T())
    : dest(_dest), back(_back), c(_c), f(_f) { }
};

template <class E, class T>
void flow_add_edge(E &flow, int node, int dest, T c, T back_c = T()) {
  flow[node].push_back(flow_edge<T>(dest, edges[dest].size(), c));
  flow[dest].push_back(flow_edge<T>(node, edges[node].size() - 1, back_c));
}

typedef vector< vector< flow_edge<int> > > flow_graph;
