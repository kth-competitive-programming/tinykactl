/* KTH ACM Contest Template Library
 *
 * Graph/Max flow/Preflow-Push lift-to-front
 *
 * Credit:
 *   Karzanov, Goldberg (, Tarjan?)
 *   From [Intro to Algs ed. 8, pp.605-625,629]
 *   By Mattias de Zalenski
 */

#include <vector>
#include "flow_graph.cpp"


template <class E, class T, class V>
void add_flow(E &flow, flow_edge<T> &edge, T f, V &excess) {
  flow_edge<T> &back = flow[edge.dest][edge.back];
  edge.f += f; edge.c -= f;
  back.f -= f; back.c += f;
  excess[edge.dest] += f;
  excess[back.dest] -= f;
}

template <class E>
typename E::value_type::value_type::flow_type lift_to_front(E &flow,
						   int source, int sink) {
  typedef typename E::value_type::value_type::flow_type T;
  typedef typename E::value_type L;
  typedef typename L::iterator L_iter;
  int v = flow.size();

  // init preflow
  vector<int> height(v, 0);
  vector<T> excess(v, T());
  height[source] = v - 2;

  for (L_iter it = flow[source].begin(); it != flow[source].end(); it++)
    add_flow(flow, *it, it->c, excess);

  // init lift-to-front
  vector<int> l(v, sink); // lift-to-front list
  vector<L_iter> cur; // current edge, per node
  int p = sink; 
  for (int i = 0; i < v; i++)
    if (i != source && i != sink)
      l[i] = p, p = i; // turn l into a linked list from p to sink
  for (int i = 0; i < v; i++)
    cur.push_back(flow[i].begin());

  // lift-to-front loop
  int r = p, u = p;
  while (u != sink) {
    int oldheight = height[u];

    // discharge u
    while (excess[u] > 0)
      if (cur[u] == flow[u].end()) {
	// lift u
	height[u] = 2 * v - 1;
	for (L_iter it = flow[u].begin(); it != flow[u].end(); it++)
	  if (it->c > 0 && height[it->dest]+1 < height[u]) {
	    height[u] = height[it->dest]+1;
	    cur[u] = it; // start from an admissable edge!
	  }
      }
      else if (cur[u]->c > 0 && height[u] == height[cur[u]->dest] + 1)
	// push on edge cur[u]
	add_flow(flow, *cur[u], min(excess[u], (*cur[u]).c), excess);
      else
	++cur[u];

    // the lift-to-front bit:
    if (height[u] > oldheight && u != p)
      l[r] = l[u], l[u] = p, p = u; // move u to front of list
    r = u, u = l[r]; // move to next in list
  }
  return excess[sink];
}
