/*****************************************************************************
 * 
 * Geometry3: convex_hull
 * ======================
 *
 * Calculate the convex hull.
 *
 * Note that if several points on a hull edge are colinear, all will be
 * included in the hull in ccw order *EXCEPT* for the last edge in which
 * only the 2 outermost points will be included. (the primary sort sorts
 * colinear points in increasing distance from the bottom-left corner which
 * makes the last points on the last edge end up in the wrong order. It is
 * rather easy to fix if necessary.)
 *
 * INPUT
 * -----
 * p:    An array of size n with points.
 * n:    The number of points.
 *
 * OUTPUT
 * ------
 * idx:  An int-array of size n.
 *       On return, the first r indices are the points constituing the
 *       convex hull, given in CCW order.
 * r:    The number of points in the convex hull (return value).
 *
 * COMPLEXITY  O( n log n )
 *
 * REQUIRES  geometry.h, general/1_indexed.cpp
 * ------------------------------------------------------------------------- *
 *
 * NADA acmlib (10 March 2002)
 * Templates for KTH-NADA, Ballons'R'Us, ACM 2001-2002
 *   Swedish competition, Link?ping 6 Oct 2001
 *   Revised for SWERC, Portu, Portugal 17 Nov 2001
 *   Revised for World Finals, Honolulu, 23 Mar 2002
 *   David Rydh, Mattias de Zalenski, Fredrik Niemel?
 *
 *****************************************************************************/

#include "geometry.h"
#include "../general/1_indexed.cpp"

template <class T>
int ccw(point<T> p0, point<T> p1, point<T> p2) {
  T dx1 = dx(p0,p1); T dy1 = dy(p0,p1);
  T dx2 = dx(p0,p2); T dy2 = dy(p0,p2);
  T d = dx1*dy2 - dy1*dx2;

  if( d != 0 ) return d>0 ? 1:-1;

  // Points are on a line

  // If points are on different sides of p1, the angle is 
  // 180 degrees (a degenerated triangle). This is a ambigous
  // case which never occurs for the convex_hull algorithm.
  if (dx1 * dx2 < 0 || dy1 * dy2 < 0) return -1;

  // The correct ordering of 3 points on a row is p0-p1-p2.
  if (dx1 * dx1 + dy1 * dy1 < dx2 * dx2 + dy2 * dy2) return +1;

  // If all three points coincide return 0.
  return 0;
}

template <class T>
bool intersect( line<T> l1, line<T> l2 ) {
  int c11, c12, c21, c22;

  c11 = ccw( l1.p1, l1.p2, l2.p1 );
  c12 = ccw( l1.p1, l1.p2, l2.p2 );
  c21 = ccw( l2.p1, l2.p2, l1.p1 );
  c22 = ccw( l2.p1, l2.p2, l1.p2 );

  if( c11*c12<=0 && c21*c22<=0 )
    return true;

  return c11*c12*c21*c22==0;
}



// Define an ordering on the points given by their angle
template<class P>
struct ch_sweep {
  P &p;
  ch_sweep(P &_p) : p(_p) {}
  ch_sweep(ch_sweep &x) : p(x.p) {}

  bool operator()(const P &p1, const P &p2) const
  { return 0 < ccw(p, p1, p2); }
};

// V should be RandomAccessIterator to point<T>s.
// R should be RandomAccessIterator to ints.
template <class V, class R>
int convex_hull(V p, R idx, int n) {
  typedef typename iterator_traits<V>::value_type P;

  // Find bottom-left point
  int i, m = 0;
  for (i = 1; i < n; i++)
    if (p[i] < p[m])
      m = i;

  isort(p, n, idx, ch_sweep<P>(p[m]));

  int r = 3;
  indexed<V, R> q(p, idx);

  for (i = 3; i < n; i++) {
    while (ccw(q[r - 2], q[r - 1], q[i]) < 0)
      r--;
    idx[r++] = idx[i];
  }
  return r;
}
