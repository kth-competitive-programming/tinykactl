#include <vector>
#include <queue>

typedef vector<int> vi;

template <int MaxV=100>
struct matcher {
  vi *graph;
  int V, label[MaxV+1], mate[MaxV+1], first[MaxV+1];
  queue<int> outer;

  /* Find maximum matching. Answer is stored in mate array.
   * mate[x in 1..V] = y in 1..V iff x is matched to y. */
  int maxmatch(vi *g, int n) {
    V = n;
    graph = g;
    memset(first, 0, sizeof(first));
    memset(label, -1, sizeof(label));
    memset(mate, 0, sizeof(mate));
    int s = 0;
    
    for (int u = 1; u <= V; ++u)
      if (mate[u] == 0) { // u is unmatched; augment.
	label[u] = first[u] = 0;
	while (!outer.empty()) outer.pop();
	outer.push(u);
	s += augment(u);
	label[0] = -1;  // reset
	for (int i = 1; i <= V; ++i)
	  if (label[i] >= 0)
	    label[i] = label[mate[i]] = -1;
      }
    return s;
  }

  bool augment(int u) { // Try to find an augmenting path from u
    while (!outer.empty()) { 
      int x = outer.front();      //choose outer vertex...
      outer.pop();
      if (label[x] < 0) continue;//...and make sure it's outer
      for (vi::iterator it=graph[x-1].begin(); it != graph[x-1].end(); ++it) {
	int y = *it + 1;
	if (y != u && mate[y] == 0) {  // path found!
	  mate[y] = x;
	  update(x, y);
	  return true;
	} else if (label[y] >= 0) { // odd cycle, make blossom
	  label_edge(x, y);
	} else if (label[mate[y]] < 0) {//simple case, just go on
	  label_vertex(mate[y], x);
	  first[mate[y]] = y;
	}
      }
    }
    return false;
  }
  void update(int v, int w) { // augment path w | P(v), w outer
    int t = mate[v];
    mate[v] = w;
    if (mate[t] != v) return;
    if (label[v] >= 0 && label[v] <= V)
      mate[t] = label[v], update(label[v], t);
    int x = vertex1(label[v]), y = vertex2(label[v]);
    update(x, y);
    update(y, x);
  }
  void label_edge(int x, int y) { // blossom P(x) isect P(y)
    int r = first[x], s = first[y], f = edge(x, y);
    if (r == s) return;
    label[s] = -f;
    while (label[r] >= -V) {
      label[r] = -f;
      if (s != 0) swap(r, s);
      r = first[label[mate[r]]];
    }
    while ((x = first[x]) != r)
      label_vertex(x, f), first[x] = r, x = label[mate[x]];
    while ((y = first[y]) != r) 
      label_vertex(y, f), first[y] = r, y = label[mate[y]];
    for (int i = 0; i <= V; ++i)
      if (label[first[i]] >= 0)
	first[i] = r;
  }  
  void label_vertex(int v, int l) { // update v's label
    if (l >= 0 && label[v] < 0) outer.push(v);
    label[v] = l;
  } 
  int edge(int x, int y) { return x*(V+1) + y + V + 1; }
  int vertex1(int e) { return (e-V-1) / (V+1); }
  int vertex2(int e) { return (e-V-1) % (V+1); }
};
