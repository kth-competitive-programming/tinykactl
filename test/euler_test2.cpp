/******************************************
 *
 * @JUDGE_ID: 16100CR 10129 C++
 *
 * Problem 10034 "Play on Words"
 *
 * David Rydh, <f99-dry@nada.kth.se>
 * March 2002
 *****************************************/

#include <cstdlib>
#include <iostream>

#include <vector>
#include <set>
#include <list>
#include "../graph/6_euler_walk.cpp"


int main( void ) {
  int T;

  cin >> T;

  for( int t=0; t<T; t++ ) {
    char               word[1500];
    vector< set<int> > edges;
    list<int>          path;
    int                numNodes = 'z'-'a'+1;
    int                numWords;

    edges.clear();
    edges.resize(numNodes);

    // Add edges
    cin >> numWords;
    for( int i=0; i<numWords; i++ ) {
      cin >> word;

      int l = strlen(word);

      edges[ word[0]-'a' ].insert( word[l-1]-'a' );
    }

    // Find odd node
    int i;
    for( i=0; i<numNodes; i++ ) {
      if( edges[i].size() % 2 == 1 )
	break;
    }

    // We don't actually need to calculate the euler-path but it
    // is a good test for the algorithm
    path.clear();
    if( i<numNodes )
      euler_walk( edges, i, path );

    if( path.size() == numWords+1 )
      cout << "Ordering is possible." << endl;
    else
      cout << "The door cannot be opened." << endl;
  }

  return 0;
}
