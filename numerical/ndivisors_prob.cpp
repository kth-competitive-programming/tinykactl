/* KTH ACM Contest Template Library
 *
 * Numerical/Number Theory/ndivisors_prob
 *
 * Credit:
 *   By David
 */

#include <cmath>

#include "rabin-miller.cpp"

template< class T >
unsigned long long ndivisors_prob( unsigned long long x, T &primes ) {
  unsigned long long sn = (unsigned long long)pow((double)x,1.0/3.0);
  unsigned int nDivs = 1, nPrimes = primes.size();

  for( unsigned int i=0; i<nPrimes; i++ ) {
    unsigned int p = primes[i];

    if( p>sn )
      break;

    if( x % p == 0 ) {
      int nFactors = 0;

      while( x % p == 0 ) {
	x /= p;
	nFactors++;
      }
      sn = (unsigned long long)pow((double)x,1.0/3.0);
      nDivs *= (nFactors+1);
    }
  }

  if( x != 1 ) {
    // x is either prime, a square or product of two primes.

    unsigned long long y = (unsigned long long)sqrt( (double)x );
    if( y*y == x )
      nDivs *= 3;
    else if( isprime_rabin_miller(x, 2) ) // Nr of iters, 10-50 may be proper.
      nDivs *= 2;
    else
      nDivs *= 4;
  }
  return nDivs;
}
