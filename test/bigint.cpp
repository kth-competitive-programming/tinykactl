/******************************************
 *
 * @JUDGE_ID: 16100CR I C++
 *
 * Problem I "The Priest Mathematician"
 *
 * David Rydh, <f99-dry@nada.kth.se>
 * ACM Warmup competition 2, 11 March 2002
 *****************************************/

#include <cstdlib>
#include <iostream>

using namespace std;

#include "../datastructures/numbers/bigint_full.cpp"


BigInt a[10001];
bool   p[10001];

BigInt solve( int n );


void solve( int n, BigInt &res ) {
  if( n<=1 ) {
    res = BigInt(n);
    return;
  }
  if( p[n] ) {
    res = a[n];
    return;
  }

  BigInt b(2), minMoves, moves;

  for( int k=1; k<200 && k<n; k++ ) {
    solve(n-k, moves);
    moves += moves;
    moves += b;
    b += b;

    if( k==1 || moves < minMoves )
      minMoves = moves;
  }
  minMoves -= 1;
  p[n] = true;

  res = a[n] = minMoves;
}

int main( void ) {
  int line=0;

  while( true ) {
    int n=-1;

    cin >> n;
    if( n<0 )
      break;

    BigInt minMoves;

    solve( n, minMoves );

    minMoves.print();
    cout << endl;
    line++;
  }

  return 0;
}
