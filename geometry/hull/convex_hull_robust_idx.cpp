/*****************************************************************************
 * 
 * Geometry12: convex_hull_robust
 * ==============================
 *
 * Calculate the convex hull.
 *
 * The convex hull includes all colinear points on its edges even
 * if it is a degenerated hull (i.e. a segment).
 *
 * The first point of the hull is the lexically ordered (leftmost) point.
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
 * NADA acmlib (3 April 2002)
 * Templates for KTH-NADA, Ballons'R'Us, ACM 2001-2002
 *   Swedish competition, Link?ping 6 Oct 2001
 *   Revised for SWERC, Portu, Portugal 17 Nov 2001
 *   Revised for World Finals, Honolulu, 23 Mar 2002
 *   David Rydh, Mattias de Zalenski, Fredrik Niemel?
 *
 *****************************************************************************/

#include "../../datastructures/indexed.cpp"
#include "../../combinatorial/isort.cpp"

template <class T>
int ccw_simple(point<T> p0, point<T> p1, point<T> p2) {
  T d = dx(p0,p1)*dy(p0,p2)-dy(p0,p1)*dx(p0,p2);

  return d!=0 ? d>0 ? 1:-1:0;
}

// V should be RandomAccessIterator to point<T>s.
// R should be RandomAccessIterator to ints.
template <class V, class R, class T>
void sort_ccw(V p, R idx, int n, const point<T> &center ) {
}


// V should be RandomAccessIterator to point<T>s.
// R should be RandomAccessIterator to ints.
template <class V, class R>
int convex_hull_robust(V p, R idx, int n) {
  typedef typename iterator_traits<V>::value_type P;
  P center = P();

  // Take an arbitrary point that is *strictly* inside the hull.
  int m = 0;
  for( int i=0; i<n; i++ ) {
    center.x += p[i].x, center.y += p[i].y;
    if( p[i] < p[m] )
      m = i;
  }
  center.x /= n, center.y /= n;


  /* Sofisticated total ordering of points:
   *
   * Sort first on angle to startpoint (m), then on angle to center and
   * finally if the points are on the line m-center, sort on distance.
   */
  vector< pair<double,double> > angles;
  angles.reserve( n );

  for( int i=0; i<n; i++ ) {
    if( p[m].x == p[i].x && p[m].y == p[i].y )
      angles.push_back( make_pair(-100,0) );
    else if( ccw_simple(p[m],center,p[i]) == 0 )
      angles.push_back( make_pair(angle(p[i]-p[m]), dist2(p[i]-p[m])) );
    else
      angles.push_back( make_pair(angle(p[i]-p[m]), angle(p[i]-center)) );
  }

  isort( angles.begin(), n, idx );


  int r = 3;
  indexed<V, R> q(p, idx);

  // Change <0 to <=0 if colinear points on the hull are not desired.
  for (int i = 3; i < n; i++) {
    while (ccw_simple(q[r - 2], q[r - 1], q[i]) < 0)
      r--;
    idx[r++] = idx[i];
  }
  return r;
}
