/* KTH ACM Contest Template Library
 *
 * Numerical/Number Theory/mulmod
 *
 * Multiply two numbers modulo something.
 * mod must be less than Tmax/2.
 *
 * Credit:
 *   By David Rydh
 */

template< class T > // Note! T must be unsigned!
T mulmod( T a, T b, T mod ) {
  T max = T(-1)>>1;
  T c = 0;

  if( a>=max ) a %= mod;
  if( b>=max ) b %= mod;
  while( b > 0 ) {
    if( b & 1 ) {
      c += a;
      if( c>=max ) c %= mod;
    }
    a *= 2;
    if( a>=max ) a %= mod;
    b >>= 1;
  }
  if( c>=mod ) c %= mod;
  return c;
}
