/* KTH ACM Contest Template Library
 *
 * Numerical/Number Theory/ndivisors
 *
 * Credit:
 *   By David
 */

#include <cmath>

template< class T >
unsigned long long ndivisors( unsigned long long x, T &primes ) {
  unsigned long long sn = (unsigned long long)sqrt((double)x);
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
      sn = (unsigned long long)sqrt((double)x);
      nDivs *= (nFactors+1);
    }
  }

  if( x != 1 )
    nDivs *= 2;
  return nDivs;
}
