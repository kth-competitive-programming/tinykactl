/******************************************
 *
 * @JUDGE_ID: 25719RJ 264 C++
 *
 * Problem 264 "Count on Cantor"
 *
 * David Rydh, <f99-dry@nada.kth.se>
 * September 2002
 *****************************************/

#include <cstdlib>
#include <cstdio>

#include <algorithm>

int diag[5000];

int main( void ) {
  int n;

  for( int i=0, j=1; i<5000; j+=++i )
    diag[i] = j;

  while( scanf("%d", &n)==1 ) {
    int d,a,b;

    d = (upper_bound( diag+0, diag+5000, n )-diag)-1;
    a = 1;
    b = d+1;
    for( int nx = n-diag[d]; nx > 0; nx-- ) {
      a++;
      b--;
    }
    if( !(d & 1) )
      swap( a,b );
    printf( "TERM %d IS %d/%d\n", n, a,b );
  }
  return 0;
}
