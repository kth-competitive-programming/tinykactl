/******************************************
 *
 * @JUDGE_ID: 25719RJ 10305 C++
 *
 * Problem 10305 "Ordering Tasks"
 *
 * David Rydh, <f99-dry@nada.kth.se>
 * June 2002
 *****************************************/

#include <cstdlib>
#include <iostream>

//#include <vector>
//#include <queue>
//#include "../../tinystl/vector.cpp"
#include "../../tinystl/priority_queue.cpp"

template <class V, class I>
bool topo_sort(const V &edges, I &idx, int n) {
  typedef typename V::value_type::const_iterator E_iter;
  vector<int> indeg;
  indeg.resize(n, 0);
  for (int i = 0; i < n; i++)
    for (E_iter e = edges[i].begin(); e != edges[i].end(); e++)
      indeg[*e]++;
  //queue<int> q;
  priority_queue<int> q; // **
  for (int i = 0; i < n; i++)
    if (indeg[i] == 0)
      q.push(-i);
  int nr = 0;
  while (q.size() > 0) {
    //int i = -q.front();
    int i = -q.top(); // **
    idx[i] = nr++;
    q.pop();
    for (E_iter e = edges[i].begin(); e != edges[i].end(); e++)
      if (--indeg[*e] == 0)
	q.push(-*e);
  }
  return nr == n;
}


int main() {
  vector< vector<int> > graph;
  vector< int > idx;

  while( true ) {
    int n=0,m=0;

    cin >> n >> m;
    if( n==0 && m==0 )
      break;

    graph.clear();
    graph.resize( n );
    idx.resize( n );

    for( int i=0; i<m; i++ ) {
      int a,b;

      cin >> a >> b;
      a--;
      b--;
      graph[a].push_back( b );
    }
    if( !topo_sort(graph, idx, n) ) {
      throw -1;
      return -1;
    }
    for( int i=0; i<n; i++ ) {
      cout << idx[i]+1;
      if( i<n-1 )
	cout << " ";
    }
    cout << endl;
  }

  return 0;
}
