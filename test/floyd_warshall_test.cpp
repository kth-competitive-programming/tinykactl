// Problem F "Page hopping" in ACM WF 2000.

#include <vector>
#include <map>
#include "../graph/1_floyd_warshall.cpp"


bool solve( int testNum );

int main() {
  for( int i=1; solve(i); i++ )
    ;

  return 0;
}

class Length {
  int l;

public:
  Length() { l = -1; }
  Length( int a ) { l=a; }

  operator int&() { return l; }
};

bool solve( int testNum ) {
  int i,j,n;
  int totLength, numPaths;

  // Method a) map-map (slow)
  // map< int, map<int, Length> > edges;

  /*
  // Method b) vector-vector (quite slow)
  vector< vector<int> > edges;
  edges.resize( 100 );
  for( i=0; i<100; i++ )
    edges[i].resize( 100 );
  */

  // Method c) 2D-array
  int edges[100][100];

  // Initialize matrix (for b and c)
  for( i=0; i<100; i++ )
    for( j=0; j<100; j++ )
      edges[i][j] = -1;

  // read input
  for( n=0; true; n++ ) {
    scanf( "%d%d", &i,&j );
    if( i == 0 && j == 0 )
      break;
    i--;
    j--;
    edges[i][j] = 1;
  }

  if( n==0 )
    return false;

  floyd_warshall( edges, (int ***)NULL, 100 );

  numPaths = 0;
  totLength = 0;
  for( i=0; i<100; i++ ) {
    for( j=0; j<100; j++ ) {
      if( i==j || edges[i][j]<0 )
        continue;
      totLength += edges[i][j];
      numPaths++;
    }
  }

  printf( "Case %d: average length between pages = %.3f clicks\n",
	  testNum, (float)totLength/numPaths );

  return true;
}
