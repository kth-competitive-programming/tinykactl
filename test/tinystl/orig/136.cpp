/******************************************
 *
 * @JUDGE_ID: 25719RJ 136 C++
 *
 * Problem 136 "Ugly Numbers"
 *
 * David Rydh, <f99-dry@nada.kth.se>
 * September 2002
 *****************************************/

#include <cstdlib>
#include <cstdio>

#include <vector>
#include <algorithm>

vector<int> uglys;

int main( void ) {
  long long nr = 1, nr2, nr3;

  for( int i=0; i<32; i++ ) {
    nr2 = nr;
    for( int j=0; j<20; j++ ) {
      if( nr2 >= 0x7fffffff )
	break;

      nr3 = nr2;
      for( int k=0; k<14; k++ ) {
	if( nr3 >= 0x7fffffff )
	  break;
	uglys.push_back( nr3 );
	nr3 *= 5;
      }
      nr2 *= 3;
    }
    nr *= 2;
  }
  sort( uglys.begin(), uglys.end() );
  printf( "The 1500'th ugly number is %d.\n", uglys[1499] );
}
