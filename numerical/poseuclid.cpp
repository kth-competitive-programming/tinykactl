/* KTH ACM Contest Template Library
 *
 * Numerical problems/Number Theory/Euclid's Algorithm
 *
 * Credit:
 *   Euclid
 *   Based on [Intro to Algorithms 8th ed, p. 810]
 *   Variation of numerical/gcd.cpp
 *   By Mattias de Zalenski
 */

template <class T>
T poseuclid( T a, T b, T &x, T &y ) {
  if( b==T(0) )
    return x = T(1), y = T(0), a;
  else {
    T d = poseuclid( b, a%b, y, x );
    y += a/b*x;
    return d;
  }
}
