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

template< class T >
T mulmod( T a, T b, T mod ) {
  T c = 0;

  a %= mod;
  b %= mod;
  while( b > 0 ) {
    if( b & 1 ) {
      c += a;
      if( c>=mod ) c -= mod;
    }
    a *= 2;
    if( a>=mod ) a -= mod;
    b >>= 1;
  }
  return c;
}
