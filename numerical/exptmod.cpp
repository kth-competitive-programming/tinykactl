/* KTH ACM Contest Template Library
 *
 * Numerical/Number Theory/exptmod
 *
 * Exponentiate two numbers modulo something.
 *
 * Credit:
 *   By Mattias de Zalenski
 */

template< class T >
T exptmod( T a, T b, T mod ) {
  T r = 1;
  a %= mod;
  while( b > T() ) {
    if( b & 1 )
      r *= a, r %= mod; // or mulmod!
    a *= a, a %= mod; // or mulmod!
    b >>= 1;
  }
  return r;
}
