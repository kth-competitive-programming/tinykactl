/* KTH ACM Contest Template Library
 *
 * Numerical problems/Number Theory/Euclid's Algorithm
 *
 * Credit:
 *   Euclid
 *   Based on [Intro to Algorithms 8th ed, p. 810]
 *   Variation of numerical/gcd.cpp
 *   By David Rydh
 */

int euclid( int a, int b, int &x, int &y ) {
  if( b==0 ) {
    x = 1;
    y = 0;
    return a;
  } else {
    int d = euclid( b, a%b, y, x );
    y -= a/b*x;
    return d;
  }
}
