/******************************************
 *
 * @JUDGE_ID: 25719RJ 10381 C++ ""
 *
 * Problem 10381 "The Rock"
 *
 * David Rydh, <f99-dry@nada.kth.se>
 * UVA Regional Warmup Competition 24 oct.
 *****************************************/

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <algorithm>

/* KTH ACM Contest Template Library
 *
 * Graph/Shortest Path/Dijkstra 1
 *
 * Find the shortest path from a given vertex to all of the V vertices in
 * a (directed) graph where all lengths are 1.
 *
 * Credit:
 *   By David Rydh
 */

#include <queue>

template<class V, class S>
void dijkstra_1( const V &edges, S &min, int start, int n ) {
  const int inf = 1 << 29;
  queue<int> q;

  // Initialize min
  min[start] = 0;

  q.push( start );

  while( !q.empty() ) {
    int node = q.front();
    int length = min[node]+1;

    q.pop();
 
    // Process node
    for( int d = 0; d<4; d++ ) {
      int destNode = edges[node][d];
      if( destNode < 0 )
	continue;

      if( length < min[destNode] ) {
	// Process this node the next run
	min[destNode] = length;
	q.push( destNode );
      }
    }
  }

  for( int i=0; i<n; i++ ) {
    if( min[i] == inf )
      min[i] = -1;
  }
}

template<class V, class S>
void dijkstra_1_spec( const V &edges, S &min, int start, int n ) {
  queue<int> q;

  q.push( start );

  while( !q.empty() ) {
    int node = q.front();
    int *length = min[node].ptr();

    q.pop();
 
    // Process node
    for( int d = 0; d<4; d++ ) {
      int destNode = edges[node][d];
      if( destNode < 0 )
	continue;

      bool proc = false;

      // Update min[4]
      if( length[4]+1 < min[destNode][4] ) {
	min[destNode][4] = length[4]+1;
	proc = true;
      }

      // Update min[5]
      int m = length[5]+1;
      for( int j=0; j<5; j++ )
	if( j!=d )
	  m = max(m, length[j]+1);
      if( m < min[destNode][5] ) {
	min[destNode][5] = m;
	proc = true;
      }

      /*      int m = length[5]+1;
      for( int j=0; j<5; j++ ) {
	if( j!=d )
	  m = max(m, length[j]+1);

	if( (d^j)==2 )
	  continue;
	if( length[4]+1 < min[destNode][j] ) {
	  min[destNode][j] = length[4]+1;
	  proc = true;
	}
      }
      if( m < min[destNode][5] ) {
	min[destNode][5] = m;
	proc = true;
      }
      */


      if( proc ) {
	// Process this node the next run
	q.push( destNode );
	/*
	cerr << node << " " << destNode << ' ';
	for( int i=0; i<6; i++ )
	  cerr << min[destNode][i] << ' ';
	  cerr << endl;*/
      }
    }
  }
}


using namespace std;

const int N = 1600;
const bool debug = true;

void init();
bool solve(int P);

int main() {
  init();

  // for-solve
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i)
    solve(i);

  return 0;
}

void init() {
}

template< class T, int N >
struct array {
  T a[N];

  array() { for( int i=0; i<N; i++ ) a[i] = T(); }
  T &operator[]( int i ) { return a[i]; }
  const T &operator[]( int i ) const { return a[i]; }
  T *ptr() { return a; }
};

bool solve(int P) {
  int nr, nc;
  cin >> nr >> nc;

  int nNodes = nr*nc;
  int start, end;
  bool wall[N];

  for( int i=0; i<nNodes; i++ ) {
    char ch;

    cin >> ch;
    wall[i] = ch=='#';
    if( ch=='X' )
      end = i;
    else if( ch=='E' )
      start = i;
  }

  vector< array<int,4> > edges( nNodes );

  for( int i=0; i<nNodes; i++ ) {
    int r = i/nc, c = i%nc;

    edges[i][0] = (r>0 && !wall[i-nc]) ? i-nc : -1;
    edges[i][1] = (c<nc-1 && !wall[i+1]) ? i+1 : -1;
    edges[i][2] = (r<nr-1 && !wall[i+nc]) ? i+nc : -1;
    edges[i][3] = (c>0 && !wall[i-1]) ? i-1 : -1;
  }

  vector< array<int,6> > min_spec( nNodes );
  vector< int > min( nNodes );

  const int inf = 1 << 29;
  for( int i=0; i<nNodes; i++ ) {
    int r = i/nc, c = i%nc;

    min_spec[i][4] = min_spec[i][5] = (i==end ? 0:inf);

    if( wall[i] )
      continue;

    for( int j=0; j<nNodes; j++ )
      min[j] = (i==j ? 0:inf);
    dijkstra_1( edges, min, end, nNodes );

    if( r>0 )    min_spec[i-nc][2] = min[i-nc];
    if( c<nc-1 ) min_spec[i+1][3] = min[i+1];
    if( r<nr-1 ) min_spec[i+nc][0] = min[i+nc];
    if( c>0 )    min_spec[i-1][1] = min[i-1];
  }

  dijkstra_1_spec( edges, min_spec, end, nNodes );

  cout << min_spec[start][5] << endl;

  return true;
}
