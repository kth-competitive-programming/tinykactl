/* KTH ACM Contest Template Library
 *
 * Numerical/Number Theory/Prime Sieve
 *
 * Credit:
 *   By Per
 */

#include <algorithm>
#include <cmath>

using namespace std;

struct prime_sieve { 
  static const int pregen = 3*5*7*11*13;
  typedef unsigned char uchar;
  typedef unsigned int uint;
  uint n, sqrtn;
  uchar *isprime;
  int *prime, primes;

  prime_sieve(int _n): n(_n), sqrtn((int)ceil(sqrt((double)n))) {
    int n0 = n >> 4;
    prime = new int[max(5000,(int)(2.4*n/log(2.0*n)))];
    prime[0] = 2; prime[1] = 3; prime[2] = 5;
    prime[3] = 7; prime[4] = 11; prime[5] = 13;
    primes = 6;
    isprime = new uchar[n0];
    memset(isprime, 255, n0); 
    for (int j = 1, p = prime[j]; j < 6; p = prime[++j])
      for (int i=(p*p-3)>>4, s=(p*p-3)/2 & 7; i<=pregen; i+=(s+=p)>>3, s&=7)
	isprime[i] &= ~(1 << s); 

    for (int d = pregen, b = pregen+1; b < n0; b += d, d <<= 1)
      memcpy(isprime + b, isprime + 1, (n0 < b + d) ? n0-b : d);
    
    for (uint p = 17, i = 0, s = 7; p < n; p += 2, i += ++s >> 3, s &= 7)
      if (isprime[i] & (1 << s)) {
	prime[primes++] = p;
	if (p < sqrtn) {
	  int ii = i, ss = s + (p-1)*p/2;
	  for (uint pp = p*p; pp < n; pp += p<<1, ss += p) {
	    ii += (ss >> 3);
	    ss &= 7;
	    isprime[ii] &= ~(1 << ss);
	  }
	} // end if
      } // end if
  } // end constructor
};
