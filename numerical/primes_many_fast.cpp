/* KTH ACM Contest Template Library
 *
 * Numerical/Number Theory/primes_many_simple
 *
 * Credit:
 *   By David
 */

#include <vector>
#include <memory>

struct primes_many_fast {
  vector< unsigned int > primes;

  primes_many_fast( int n ) {
    unsigned char *v;
    unsigned int nPrimes, nPrimesEst;
    int bn, sn = (int)sqrt((double)n);
    n /= 2;
    bn = (n+7)/8; // Round to nearest byte.

    v = (unsigned char*)malloc(bn);
    memset( v, 0, bn );

    nPrimesEst = max(5000,(int)((n*2)*1.2/log((double)n*2)));
    primes.resize( nPrimesEst );

    nPrimes = 0;
    primes[nPrimes++] = 2;

    unsigned int word=0, bit=1, f=8;
    for( int i=0, p=3; i<n; i++, p+=2 ) {
      if( !(v[word]&bit) ) {
	if( p<=sn ) {
	  // p is a prime, remove all p-multiples
	  if( f != 0 ) {
	    f *= p;
	    if( f+8 > (unsigned)n )
	      f = 0;
	  }
	  if( f != 0 ) {      // Small prime optimization
	    unsigned int idx; // (can be left out)

	    // Generate small piece
	    for( idx=i+p; idx<f+8; idx+=p )
	      v[idx>>3] |= 1<<(idx&7);

	    // Replicate
	    int f2 = f/8;
	    int w;
	    for( w=f2+1; w<bn; ) {
	      if( w+f2 <= bn ) {
		memcpy( &v[w], &v[1], f2 );
		w += f2;
	      } else {
		memcpy( &v[w], &v[1], bn-w );
		w = bn;
	      }
	    }
	  } else {
	    int idx;
	    int mult = (n-i-8*p-1)/(8*p)*8;
	    int k=mult/8, mask = v[k];

	    for( idx=i+(mult+8)*p; idx>i; mask=v[--k] ) {
	      unsigned char t;
	      for( t=128; t!=0; t>>=1, idx-=p ) {
		if( !(mask & t) )
		  v[idx>>3] |= 1<<(idx&7);
	      }
	    }

	    for( idx=i+(mult+9)*p; idx<n; idx+=p )
	      v[idx>>3] |= 1<<(idx&7);
	  }
	}
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
