#include <iostream>
#include <map>
#include <vector>

using namespace std;

#include "../graph/dijkstra_simple.cpp"
#include "../graph/dijkstra_prim.cpp"

int main( void ) {
  vector< double > min;
  vector< int > from;
  vector< map<int, double> > edges;
  int n;

  /*
  // Read graph
  cin >> n;
  edges.resize( n );

  for( int i=0; i<n; i++ ) {
    int m;

    cin >> m;
    for( int j=0; i<m; j++ ) {
      int k;
      double dist;

      cin >> k >> dist;
      edges[i][k] = dist;
    }
  }
  */

  n = 5;
  edges.resize( n );
  edges[0][1] = 500.0;
  edges[0][2] = 100.0;
  edges[0][3] = 50.0;
  edges[0][4] = 200.0;
  edges[2][3] = 300.0;
  edges[2][4] = 50.0;
  edges[3][4] = 200.0;

  // Calculate shortest path from 0 to 0...n-1
  min.resize( n );
  from.resize( n );
  dijkstra_prim( edges, min, from, 0, n, id_dist<pair<int,double>,double> );

  cout << from[0] << " " << from[1] << " " << from[2] << " "
       << from[3] << " " << from[4] << endl;
  cout << min[0] << " " << min[1] << " " << min[2] << " "
       << min[3] << " " << min[4] << endl;
}
