/* KTH ACM Contest Template Library
 *
 * Numerical/Number Theory/primes_many_simple
 *
 * Credit:
 *   By David
 */

#include <vector>
#include <memory>

struct primes_many_simple {
  vector< unsigned int > primes;

  primes_many_simple( int n ) {
    unsigned char *v;
    unsigned int nPrimes, nPrimesEst;
    int bn, sn = (int)sqrt((double)n);
    n /= 2;
    bn = (n+7)/8;

    v = (unsigned char*)malloc(bn);
    memset( v, 0, bn );

    nPrimesEst = max(5000,(int)((n*2)*1.2/log((double)n*2)));
    primes.resize( nPrimesEst );

    nPrimes = 0;
    primes[nPrimes++] = 2;

    unsigned int word=0, bit=1;
    for( int i=0, p=3; i<n; i++, p+=2 ) {
      if( !(v[word]&bit) ) {
	if( p<=sn )
	  for( int idx=i+p; idx<n; idx+=p )
	    v[idx>>3] |= 1<<(idx&7);
	primes[nPrimes++] = p;
      }
      if( (bit <<= 1) >= 256 )
	word++, bit=1;
    }
    if( nPrimes > nPrimesEst )
      cout << "OOPS!" << endl;
    free( v );

    primes.resize( nPrimes );
  }
};

