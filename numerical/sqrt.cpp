/* KTH ACM Contest Template Library
 *
 * Numerical/BigInt/bigint_full
 *
 * Credit:
 *   By David Rydh
 */

template< class T >
T sqrt( const T &x0 ) {
  T x = x0;
  // Newton-Raphson's method. Recursion: y' = y-(y^2-x)/(2y) = (y+x/y)/2
  // special case for x=0,1 in sqrt(x) since x/2 is 0 in that case.
  // Recursion gives descending sequence x_0 > x_1 > x_2 > ... The sequence
  // may not be stabile due to rounding errors, but when it increases it is
  // at floor(sqrt(x)).

  if( x != 0 && x != 1 ) {
    x /= 2;
    while( true ) {
      T d = x0; d /= x; d += x; d /= 2;

      if( !(d<x) ) break;
      x = d;
    }
  }
  return x;
}

template< class T >
T sqrt2( const T &x0 ) {
  T x=1, y=2;

  while(x0<x*x || !(x0<y*y)) {
    x=(x+x0/x)/2;
    y=x+1;
  }
  return x;
}

