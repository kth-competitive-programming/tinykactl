/* KTH ACM Contest Template Library
 *
 * Graph/Shortest Path and Minimum Spanning Tree/Dijkstra and Prim
 *
 * Credit:
 *   Dijkstra
 *   Prim
 *   by Mattias de Zalenski
 */
#include <set>

template <class V> struct idxless {
  const V &v;
  idxless(const V &_v) : v(_v) { }
  bool operator()( const int &i, const int &j ) const { return v[i] < v[j]; }
};
/*
template <class V, class C> struct idxcomp {
  const V &v; const C &c;
  idxcomp(const V &_v, const C &_c) : v(_v), c(_c) { }
  bool operator()(int i, int j) const { return c(v[i], v[j]); }
};
*/

template <class E, class M, class P, class D>
void dijkstra_prim(E &edges, M &min, P &path, int start, int n, D distfun,
		   bool mst = false) {
  typedef typename M::value_type T;
  T inf(1<<29);

  typedef idxless< M > C;
  C comp( min );
  set< int, C > q(comp); // use a set as a modifiable priority queue

  for (int i = 0; i < n; i++) {
    min[i] = inf;
    path[i] = -1;
  }
  min[start] = T();

  q.insert(start);
  while (!q.empty()) {
    int node = *q.begin();
    q.erase(q.begin());
    if (mst) min[node] = T(); // only difference between dijkstra and prim
    typedef typename E::value_type L;
    typedef typename L::const_iterator L_iter;

    const L &l = edges[node];
    for (L_iter it = l.begin(); it != l.end(); ++it) {
      pair<int, T> p = distfun(*it, min[node]);
      int dest = p.first; T dist = min[node] + p.second;
      if (dist < min[dest]) {
	q.erase(dest);    //
	min[dest] = dist; // update dest in the queue
	q.insert(dest);   //
	path[dest] = node;
      }
    }
  }
}



// one distfun
pair<int, int> one_dist(int node, int) { return make_pair(node, 1); }

// weighted edge distfun
template <class P, class T> P id_dist(P edge, T) { return edge; }

// for time-table searches without mod:
template <class T, T inf>
pair<int, T> step_dist(pair<int, T> &edge, T t) {
  return make_pair(edge.first, edge.second < t ? inf : edge.second - t);
}

// for time-table searches:
template <int MOD>
pair<int, int> mod_dist(pair<int, int> &edge, int t) {
  return make_pair(edge.first, (edge.second - t % MOD + MOD) % MOD);
}

// for time-table searches with lots of times per connection:
struct mod_dist {
  int mod; mod_dist(int _mod) : mod(_mod) { }
  pair<int, int> operator()(pair<int, set< int > > &edge, int t) {
    const set<int> &tbl = edge.second; int tmod = t % mod;
    set<int>::const_iterator it = tbl.lower_bound(tmod);
    if (it == tbl.end()) t += mod, it = tbl.begin();
    return make_pair(edge.first, t - tmod + *it);
  }
};
