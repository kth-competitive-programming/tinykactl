/******************************************
 *
 * @JUDGE_ID: 16100CR B C++
 *
 * Problem B "Complete Tree Labeling"
 *
 * David Rydh, <f99-dry@nada.kth.se>
 * ACM Warmup competition 2, 11 March 2002
 *****************************************/

#include <cstdlib>
#include <iostream>

using namespace std;

#include "../numerical/bigint/bigint_full.cpp"

int k;

void solve( int n, int d, int *f );

int primes[20000];
int numPrimes;


int main( void ) {
  int d;
  int i,n;

  numPrimes=1;
  primes[0]=2;

  for( int i=3; i<=20000; i+=2 ) {
    int j;

    for( j=0; j<numPrimes; j++ ) {
      if( i%primes[j] == 0 )
	break;
    }
    if( j==numPrimes )
      primes[numPrimes++] = i;
  }

  while( true ) {
    k = d = 0;
    cin >> k >> d;

    if( k==0 )
      break;

    n = 1;

    int s;
    for( s=1, i=0; i<d; i++ ) {
      s *= k;
      n += s;
    }

    int f[20000];

    solve( n-1, d, f );
    

    BigInt numComb(1);
    for( int i=0; i<numPrimes; i++ ) {
      for( int j=0; j<f[i]; j++ )
	numComb *= primes[i];
    }
    
    numComb.print();
    
    cout << endl;
  }

  return 0;
}


void factor( int *f, int n, int mult ) {
  for( int i=0; i<numPrimes && n>1; i++ ) {
    while( n%primes[i] == 0 ) {
      n/=primes[i];
      f[i]+=mult;
    }
  }
}

void solve( int n, int d, int *f ) {
  if( d==0 ) {
    // Return 1

    for( int i=0; i<numPrimes; i++ )
      f[i] = 0;
    return;
  }

  solve( (n-k)/k, d-1, f );

  // numComb^k
  for( int i=0; i<numPrimes; i++ )
    f[i] *= k;

  // n!
  for( int i=1; i<=n; i++ )
    factor( f, i, +1 );

  // (n/k)!^-k
  int s = n/k;
  for( int i=1; i<=s; i++ )
    factor( f, i, -k );
}
