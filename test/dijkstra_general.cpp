#include <iostream>
#include <map>
#include <vector>

using namespace std;

#include "../obsolete/10_dijkstra_general.cpp"

int main( void ) {
  int n;
  map< int, map<int, float> > edges;
  map< int, float > min;
  map< int, int > from;

  edges[1][2] = 100.0;
  edges[1][3] = 50.0;
  edges[1][4] = 200.0;
  edges[2][3] = 300.0;
  edges[2][4] = 50.0;
  edges[3][4] = 200.0;
  edges[4]; // Create an empty edge-list

  dijkstra_general( edges, min, &from, 1 );

  cout << from[1] << " " << from[2] << " " << from[3] << " " << from[4] <<endl;
}
