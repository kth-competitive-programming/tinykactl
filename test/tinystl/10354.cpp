/******************************************
 *
 * @JUDGE_ID: 25719RJ 10354 C++
 *
 * Problem 10354 "Avoiding the Boss"
 *
 * David Rydh, <f99-dry@nada.kth.se>
 * POPUP Tävling 3 (Valladolid), 2002-09-13
 *****************************************/

#include <iostream>
//#include <cstdio>
//#include <algorithm>
//#include <vector>
//#include <utility>
using namespace std;

#include "../../tinystl/vector.cpp"
#include "../../tinystl/pair.cpp"

const int N = 0;

void init();
bool solve(int P);

template<class E, class M>
void dijkstra( const E &edges, M &min, int start, int n,
	       bool mst = false ) {
  typedef typename M::value_type T;
  T inf(1<<29);

  // Initialize min & path
  for( int i=0; i<n; i++ )
    min[i] = inf;
  min[start] = T();

  // Initalize proc
  vector<bool> proc( n, false );

  // Find shortest path
  while( true ) {
    int node = -1;
    T   least = inf;

    for( int i=0; i<n; i++ )
      if( !proc[i] && min[i] < least )
        node = i, least = min[i];
    if( node < 0 ) break;

    if( mst ) min[node] = T();
    typedef typename E::value_type L;
    typedef typename L::const_iterator L_iter;

    const L &l = edges[node];
    for( L_iter it=l.begin(); it!=l.end(); ++it ) {
      int dest = (*it).first;
      T dist = min[node]+(*it).second;

      if( !proc[dest] && dist < min[dest] )
        min[dest] = dist;
    }

    proc[node] = true;
  }

  // Update min to -1 if inf
  for( int i=0; i<n; i++ ) {
    if( min[i] == inf )
      min[i] = -1;
  }
}


int main() {
  init();
  
  //while-solve
  int n = 0;
  while (solve(n))
    n++;

  return 0;
}

void init() {
}

vector< vector<pair<int,int> > > edges;
vector<pair<int,int> >::iterator edge_iter;

bool solve(int K) {
  int P, R, BH, OF, YH, M;
  cin >> P >> R >> BH >> OF >> YH >> M;
  if (cin.fail()) return false;

  BH--;
  OF--;
  YH--;
  M--;

  edges.clear();
  edges.resize( P );

  for( int i=0; i<R; i++ ) {
    int n1, n2, cost;

    cin >> n1 >> n2 >> cost;
    n1--;
    n2--;
    edges[n1].push_back( make_pair(n2,cost) );
    edges[n2].push_back( make_pair(n1,cost) );
  }

  vector< int > min, min2;
  min.resize( P );
  min2.resize( P );
  dijkstra( edges, min, BH, P );
  dijkstra( edges, min2, OF, P );

  bool imp = false;
  int bossMin = min[OF];
  for( int i=0; i<P; i++ ) {
    if( min[i]+min2[i] <= bossMin ) {
      edges[i].clear();
      //      cout << "Removing " << i+1 << endl;
      if( i==M )
	imp = true;
    }
  }

  dijkstra( edges, min, YH, P );
  if( min[M] == -1 || imp )
    cout << "MISSION IMPOSSIBLE." << endl;
  else
    cout << min[M] << endl;

  return true;
}
