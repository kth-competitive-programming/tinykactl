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

template <class T>
struct flow_edge {
  int dest, back;
  T c, f; // capacity and flow
  flow_edge(int _dest, int _back, T _c, T _f = T())
    : dest(_dest), back(_back), c(_c), f(_f) { }
};

template <class E, class T>
void flow_add_edge(E &flow, int node, int dest, T c, T back_c = T()) {
  edges[node].push_back(flow_edge(dest, edges[dest].size(), c));
  edges[dest].push_back(flow_edge(node, edges[node].size() - 1, back_c));
}

template <class E, class T, class V>
void add_flow(E &flow, flow_edge &edge, T f, V excess) {
  flow_edge &back = flow[edge.dest][edge.back];
  edge.f += f; edge.c -= f;
  back.f -= f; back.c += f;
  excess[edge.dest] += f;
  excess[back.dest] -= f;
}

template <class E>
T lift_to_front(E &flow, int source, int sink) {
  int v = flow.size();

  // init preflow
  vector<int> height(v, 0);
  vector<T> excess(v, T());
  height[source] = v - 2;
  typedef E::value_type L;
  for (L::iterator it = flow[source].begin(); it != flow[source].end(); it++)
    add_flow(flow, *it, it->c, excess);

  // init lift-to-front
  vector<int> l(v, sink); // lift-to-front list
  vector<L::iterator> cur; // current edge, per node
  int p = sink; 
  for (int i = 0; i < v; i++)
    if (i != source && i != sink)
      l[i] = p, p = i; // turn l into a linked list from p to sink
  for (int i = 0; i < v; i++)
    cur.push_back(flow[i].begin());

  // lift-to-front loop
  int r = source, u = p;
  while (u != sink) {
    int oldheight = height[u];

    // discharge u
    while (excess[u] > 0)
      if (cur[u] == flow[u].end()) {
	// lift u
	int minh = v - 2;
	for (L::iterator it = flow[u].begin(); it != flow[u].end(); it++)
	  if (it->c > 0) minh = min(minh, height[it->dest]);
	height[u] = 1 + minh;
	// last four lines may maybe be replaced by height[u]++; ..
	cur[u] = flow[u].begin();
      }
      else if (cur[u]->c > 0 && height[u] == height[cur[u]->dest] + 1)
	// push on edge cur[u]
	add_flow(flow, cur[u], min(excess[u], cur[u]->c), excess);
      else
	++cur[u];

    // the lift-to-front bit:
    if (height[u] > oldheight)
      l[r] = l[u], l[u] = p, p = u; // move u to front of list
    r = u, u = l[r]; // move to next in list
  }
  return excess[sink];
}
