/* KTH ACM Contest Template Library
 *
 * Numerical/Number Theory/Soll Primes
 *
 * Credit:
 *   Eratosthenes
 *   By David Rydh
 */

#include <vector>

struct prime_sieve {
  char *v;

  prime_sieve( int n ) {
    int sn = (int)sqrt(n);
    n /= 2;
    v = (char*)malloc(n);
    memset( v, 1, n );

    for( int i=0, p=3; i<sn; i++, p+=2 ) {
      if( v[i] ) {
	// p is a prime, remove all p-multiples
	for( int j=i+p; j<n; j+=p )
	  v[j] = 0;
      }
    }
  }

  bool isprime( int m ) {
    if( !(m&1) )
      return (m==2);
    return v[(m-3)/2];
  }
};
