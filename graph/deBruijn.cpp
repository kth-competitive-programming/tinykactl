/* KTH ACM Contest Template Library
 *
 * Graph/Euler Cycle/de Bruijn
 *
 * Credit:
 *   N. G. de Bruijn
 *   by David Rydh
 */

#include <iostream>
#include <vector>

using namespace std;

#include "euler_walk.cpp"

void deBruijn( int numSymbols, int L, char symbols[]) {
  int                numNodes;
  vector< vector<int> > edges;
  list<int>          path;

  // Number of nodes is numSymbols^(L-1)
  numNodes = 1;
  for( int i=0; i<L-1; i++ )
    numNodes *= numSymbols;

  // Create edges
  edges.resize( numNodes );

  for( int i=0; i<numNodes; i++ ) {
    edges[i].resize( numSymbols );

    for( int j=0; j<numSymbols; j++ )
      edges[i][j] = (i*numSymbols)%numNodes + j;
  }

  // Find euler walk
  path.clear();
  euler_walk( edges, 0, path );

  // Non-cyclic deBruijn sequences
  cout << "Non-cyclic:" << endl;

  string answer;
  for( list<int>::iterator iter = path.begin(); iter != path.end(); iter++ ) {
    int node = *iter;

    if( iter == path.begin() ) {
      int d = numNodes;

      for( int j=0; j<L-1; j++ ) {
        d/= numSymbols;
        answer += symbols[ node % numSymbols ];
      }
    } else
      answer += symbols[ node % numSymbols ];
  }
  cout << answer << endl;

  // Cyclic deBruijn sequences
  cout << "Cyclic:" << endl;
  cout << answer.substr(0, answer.length()-(L-1)) << endl << endl;
}
