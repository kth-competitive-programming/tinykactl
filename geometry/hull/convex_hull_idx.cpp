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

#include "../ccw.cpp"
#include "../../combinatorial/isort.cpp"
#include "../../datastructures/indexed.cpp"

// Define an ordering on the points given by their angle
template<class P>
struct ch_sweep {
  P &p;
  ch_sweep(P &_p) : p(_p) {}
  ch_sweep(const ch_sweep<P> &x) : p(x.p) {}

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
