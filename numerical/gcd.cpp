/* KTH ACM Contest Template Library
 *
 * Numerical/Number Theory/gcd
 *
 * Credit:
 *   Euclides
 *   Based on [Intro to Algorithms 8th ed, p. 810]
 *   Variation of numerical/gcd.cpp
 *   By David Rydh
 */

int gcd( int a, int b ) {
  if( b==0 )
    return a;
  else
    return gcd( b, a%b );
}
