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
 *   David Rydh for previous impl.
 *   By Per Austrin
 */

#include <queue>
#include "flow_graph.cpp"

int mark[MAXNODES];

Flow inc_flow_dfs(adj_list *g, int s, int t, Flow maxf) {
  if (s == t) return maxf;
  Flow inc;   mark[s] = 0;
  for (adj_iter it = g[s].begin(); it != g[s].end(); ++it)
    if (mark[it->dest] && it->r() && 
	(inc=inc_flow_dfs(g,it->dest,t,min(maxf, it->r()))))
      return it->f+=inc, g[it->dest][it->back].f -= inc, inc;
  return 0;
}

Flow inc_flow_bfs(adj_list *g, int s, int t, Flow inc) {
  queue<int> q;  q.push(s);
  while (!q.empty() && mark[t] < 0) {
    int v = q.front();  q.pop();
    for (adj_iter it = g[v].begin(); it != g[v].end(); ++it)
      if (mark[it->dest] < 0 && it->r())
        mark[it->dest] = it->back, q.push(it->dest);
  }
  if (mark[t] < 0) return 0;
  flow_edge* e;  int v = t;
  while (v != s)
    e = &g[v][mark[v]], v = e->dest, inc<?=g[v][e->back].r();
  v = t;
  while (v != s)
    e = &g[v][mark[v]], e->f -= inc, 
      v = e->dest, g[v][e->back].f += inc;
  return inc;
}

Flow max_flow(adj_list *graph, int n, int s, int t) {
  Flow flow = 0, inc = 0;
  do flow += inc, memset(mark, 255, sizeof(int)*n);
  while ((inc = inc_flow_dfs(graph, s, t, 1<<28)));
  return flow;//inc_flow_bfs(...             ...)
}
