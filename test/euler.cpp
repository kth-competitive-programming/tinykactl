#include <iostream>
#include <vector>
#include <set>
#include <list>

using namespace std;

#include "../graph/euler_walk.cpp"

void deBruijn( int numSymbols, int L, char symbols[]);

int main( void ) {
  deBruijn( 2, 3, "10" );
  deBruijn( 3, 3, "ABC" );
}

void deBruijn( int numSymbols, int L, char symbols[]) {
  int                numNodes;
  vector< set<int> > edges;
  list<int>          path;

  // Number of nodes is numSymbols^(L-1)
  numNodes = 1;
  for( int i=0; i<L-1; i++ )
    numNodes *= numSymbols;

  // Create edges
  edges.reserve( numNodes );

  for( int i=0; i<numNodes; i++ ) {
    edges.push_back( set<int>() );

    set<int> &s = edges.back();

    for( int j=0; j<numSymbols; j++ )
      s.insert( (i*numSymbols)%numNodes + j );
  }

  // Find euler walk
  path.clear();
  euler_walk( edges, 0, path );

  // Non-cyclic deBruijn sequences
  cout << "Non-cyclic:" << endl;

  for( list<int>::iterator iter = path.begin(); iter != path.end(); iter++ ) {
    int node = *iter;

    if( iter == path.begin() ) {
      int d = numNodes;

      for( int j=0; j<L-1; j++ ) {
        d/= numSymbols;
        cout << symbols[ node % numSymbols ];
      }
    } else
      cout << symbols[ node % numSymbols ];
  }

  // Cyclic deBruijn sequences
  cout << endl << "Cyclic:" << endl;

  for( list<int>::iterator iter = path.begin(); iter != --path.end(); iter++) {
    int node = *iter;

    cout << symbols[ node % numSymbols ];
  }
  cout << endl << endl;
}
