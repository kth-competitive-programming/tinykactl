/******************************************
 *
 * @JUDGE_ID: 16100CR 10249 C++
 *
 * Problem 10249 "The Grand Dinner" (Problem D in ACM Warmup 2, 2002)
 *
 * David Rydh, <f99-dry@nada.kth.se>
 * ACM Warmup competition 2, 11 March 2002
 *****************************************/

using namespace std;

#include <cstdlib>
#include <iostream>

//#include "../graph/maxflow/ford_fulkerson_1.cpp"
#include "../graph/maxflow/lift_to_front.cpp"


//flow_graph edges;
vector<vector<flow_edge<int> > > edges;

int main( void ) {
  int M, N, c;
  int totC1, totC2;

  while( true ) {
    cin >> M >> N;

    if( M==0 && N==0 )
      break;

    edges.clear();
    edges.resize( M+N+2 );

    // Add source-team edges
    totC1 = 0;
    for( int i=0; i<M; i++ ) {
      cin >> c;

      flow_add_edge( edges, 0, i+2, c );
      totC1 += c;
    }

    // Add board-sink edges
    totC2 = 0;
    for( int i=0; i<N; i++ ) {
      cin >> c;

      flow_add_edge( edges, i+2+M, 1, c );
      totC2 += c;
    }

    if( totC1 > totC2 ) {
      cout << "0" << endl;
      continue;
    }

    // Add team-board edges
    for( int i=0; i<M; i++ ) {
      for( int j=0; j<N; j++ ) {
	flow_add_edge( edges, i+2, j+2+M, 1 );
      }
    }
    /*
    while( flow_increase1(edges, 0, 1) )
      ;
    */
    lift_to_front( edges, 0, 1 );

    bool found = true;
    for( int i=0; i<M; i++ ) {
      if( edges[0][i].c > 0 )
	found = false;
    }

    if( found ) {
      cout << "1" << endl;

      for( int i=0; i<M; i++ ) {
	bool first = true;
	for( int j=0; j<N; j++ ) {
	  if( edges[i+2][j+1].c == 0 ) {
	    if( !first )
	      cout << " ";
	    cout << j+1;
	    first = false;
	  }
	}
	cout << endl;
      }
    } else
      cout << "0" << endl;
  }
  return 0;
}
