/* @JUDGE_ID: 16129WN 10362 C++ ""
 *
 * Problem 10362 "Trains"
 */

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
//#include <set>
#include <map>
//#include <cmath>

using namespace std;

/* KTH ACM Contest Template Library
 *
 * General/Named items/Index mapper
 *
 * Credit:
 *   By Mattias de Zalenski
 */

// function semantics for name->index map
// vector semantics for index->name map
template <class M>
struct index_mapper {
  int count;
  map<M, int> m; // name->index map
  vector<M> b; // index->name vector
  index_mapper() : count(0) { }
  int operator()(M name) {
    if (m.count(name) == 0) {
      m[name] = count;
      b.push_back(name);
      count++;
    }
    return m[name];
  }
  M &operator[](int idx) { return b[idx]; }
};

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

template <class E, class M, class P, class D>
void dijkstra_prim(E &edges, M &min, P &path, int start, int n, D distfun,
		   bool mst = false) {
  typedef typename M::value_type T;
  //T inf(1<<29);

  typedef idxless< M > C;
  C comp( min );
  set< int, C > q(comp); // use a set as a modifiable priority queue

  for (int i = 0; i < n; i++) {
    //min[i] = inf;
    path[i] = -1;
  }
  //min[start] = T();

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

// for time-table searches:
template <int MOD>
pair<int, int > mod_dist(const pair<int, pair<int, int> > &edge, int t) {
  return make_pair(edge.first, (edge.second.first - t % MOD + MOD) % MOD +
    edge.second.second);
}

using namespace std;

const int N = 0;
const bool debug = true;

void init();
bool solve(int P);

int main() {
  init();
  
  // for-solve
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
    solve(i);
  
  return 0;
}

void init() {
}

typedef vector < pair< int, pair<int, int> > > L;
typedef vector< L > E;

bool solve(int P) {
  int n;
  cin >> n;
  E graph;
  index_mapper<string> mapper;
  const int MOD = 24 * 60;
  for (int i = 0; i < n; i++) {
    int k;
    cin >> k;
    char c;
    int t = 0, h, m;
    int pidx = mapper("");
    for (int i = 0; i < k; i++) {
      string name;
      cin >> h >> c >> m >> name;
      int d = h * 60 + m;
      int idx = mapper(name);
      if (idx >= (int) graph.size())
	graph.resize(idx + 1);
      graph[pidx].push_back(make_pair(idx, make_pair(t % MOD, d)));
      t += d;
      pidx = idx;
    }
  }
  string from, to;
  cin >> from >> to;
  int start = mapper(from), end = mapper(to);
  vector<int> path(graph.size());
  map<int, int> rtimes, times;
  for (L::iterator it = graph[start].begin(); it != graph[start].end(); ++it) {
    vector<int> min(graph.size(), 1 << 29);
    min[start] = it->second.first;
    dijkstra_prim(graph, min, path, start, graph.size(), mod_dist<MOD>);
    if( rtimes.count(min[end]%MOD) == 0 ||
	rtimes[min[end]%MOD]>min[end]-min[start] )
      rtimes[min[end]%MOD] = min[end]-min[start];
  }

  if( P>0 )
    printf( "\n" );

  for (map<int,int>::iterator it = rtimes.begin(); it != rtimes.end(); ++it)
    times[((it->first-it->second)%MOD+MOD)%MOD] = it->second;

  for (map<int,int>::iterator it = times.begin(); it != times.end(); ++it) {
    int t1 = it->first;
    int t2 = it->second;
    printf("%02d:%02d %d:%02d\n", t1 / 60, t1 % 60, t2 / 60, t2 % 60);
  }
  return true;
}
