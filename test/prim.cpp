/******************************************
 *
 * @JUDGE_ID: 16100CR 10034 C++
 *
 * Problem 10034 "Freckles"
 *
 * David Rydh, <f99-dry@nada.kth.se>
 * March 2002
 *****************************************/

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

#include "../graph/mst/prim.cpp"


vector< pair<double,double> > coords;
vector< vector<pair<int,double> > > edges;


int main( void ) {
  int n;

  cin >> n;

  edges.resize( n );
  coords.resize( n );

  for( int i=0; i<n; i++ )
    cin >> coords[i].first >> coords[i].second;

  for( int i=0; i<n; i++ ) {
    for( int j=i+1; j<n; j++ ) {
      double dx, dy, dist;

      dx = (coords[i].first-coords[j].first);
      dy = (coords[i].second-coords[j].second);
      dist = dx*dx+dy*dy;
      edges[i].push_back( make_pair(j,dist) );
      edges[j].push_back( make_pair(i,dist) );
    }
  }

  vector<int> path(n);
  prim( 0, edges, path, n );

  double totLen = 0.0;
  for( int i=0; i<n; i++ ) {
    int numEdges = edges[i].size();

    for( int j=0; j<numEdges; j++ ) {
      pair<int,double>  &edge = edges[i][j];

      if( path[edge.first] == i )
	totLen += sqrt(edge.second);
    }
  }

  printf( "%.2f\n", totLen );

  return 0;
}
