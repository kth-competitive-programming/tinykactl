// Problem F "Page hopping" in ACM WF 2000.

#include <stdio.h>
#include <iostream>

#include <vector>
#include <set>
#include "../graph/3_dijkstra_1.cpp"

bool solve( int testNum );

int main() {
  for( int i=1; solve(i); i++ )
    ;

  return 0;
}

bool solve( int testNum ) {
  int i,j,n;
  int totLength, numPaths;

  // Page numbers are 1-100.
  vector< set<int> > edges;
  edges.resize( 100 );

  // read input
  for( n=0; true; n++ ) {
    scanf( "%d%d", &i,&j );
    if( i == 0 && j == 0 )
      break;
    i--;
    j--;
    edges[i].insert( j );
  }

  if( n==0 )
    return false;


  numPaths = 0;
  totLength = 0;
  for( i=0; i<100; i++ ) {
    int min[100], from[100];

    dijkstra_1( edges, min, from, i, 100 );

    for( j=0; j<100; j++ ) {
      if( i!=j && min[j] >= 0 ) {
        totLength += min[j];
        numPaths++;
      }
    }
  }


  printf( "Case %d: average length between pages = %.3f clicks\n",
	  testNum, (float)totLength/numPaths );

  return true;
}
