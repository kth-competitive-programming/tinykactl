/* KTH ACM Contest Template Library
 *
 * Geometry/Primitives/CCW line segment intersection test
 *
 * Credit:
 *   Based on Sedgewick
 *   By David Rydh
 *   Updated and moved by Mattias de Zalenski
 */

#include "ccw.cpp"

template <class P>
bool isect_test( P p1, P p2, P q1, P q2) {
  int c11, c12, c21, c22;

  c11 = ccw( p1, p2, q1 );
  c12 = ccw( p1, p2, q2 );
  c21 = ccw( q1, q2, p1 );
  c22 = ccw( q1, q2, p2 );

  if( c11*c12<=0 && c21*c22<=0 )
    return true;

  return c11*c12*c21*c22==0;
}
