/*****************************************************************************
 * 
 * Geometry2: pointline
 * ====================
 *
 * sideof: Determine on which side of a line a point is (+/- 1 or 0)
 * onsegment: Determine if a point is on a line segment (incl the end points).
 * linedist: Get a measure of the distance of a point from a line (0 on the
 *           line and positive/negative on the different sides).
 * lineisect: Line intersection.
 * ivalisect: Interval intersection.
 * rectisect: Rectangle intersection.
 *
 * INPUT
 * -----
 * p1, p2: A line.
 * t:      The test point.
 *
 * OUTPUT
 * ------
 * sideof: int
 *     +1 if left of directed line, -1 if right of dir line and 0 if on line.
 * onsegment: bool
 *     true if the point is on the segment.
 * lineisect: bool, intersection point reference
 *     true if lines intersect.
 * ivalisect: bool, ordered overlapping interval references
 *     true if intervals overlap.
 * rectisect: bool, ordered overlapping rect references 
 *     true if rectangles overlap.
 *
 * COMPLEXITY  O( n )
 *
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

template <class T>
int sideof(const point<T> &p0, const point<T> &p1, const point<T> &t) {
  T nx = -dy(p0,p1), ny = dx(p0,p1); // normal
  T dtx = dx(p0,t), dty = dy(p0,t);
  T d = nx*dtx + ny*dty;  // projection * factor

  return d > 0 ? 1 : d < 0 ? -1 : 0;
}

template<class T>
bool onsegment(const point<T> &p0, const point<T> &p1, const point<T> &t) {
  // Check if point is outside line segment rectangle.
  if( dx(t,p0)*dx(t,p1) > 0 || dy(t,p0)*dy(t,p1) > 0 )
    return false;

  // Check if point is on line (not line segment)
  return dx(t,p0)*dy(t,p1) == dx(t,p1)*dy(t,p0);
}

template <class T>
T linedist(const point<T> &p0, const point<T> &p1, const point<T> &t) {
  return -dy(p0, p1) * dx(p0, t) + dx(p0, p1) * dy(p0, t);
}

template <class T, class R>
bool lineisect(const point<T> &p0, const point<T> &p1,
	       const point<T> &q0, const point<T> &q1, point<R> &x) {
  T mx = -dy(p0,p1), my = dx(p0,p1); // normal
  T nx = -dy(q0,q1), ny = dx(q0,q1); // normal
  T det = mx*ny - nx*my;

  if( det == 0 )
    return false;

  T a = mx*p0.x+my*p0.y, b = nx*q0.x+ny*q0.y;

  x.x = (R)(ny*a-my*b)/det;
  x.y = (R)(-nx*a-mx*b)/det;

  return true;
}

template <class T>
bool ivalisect(const T &p0, const T &p1, const T &q0, const T &q1,
		   T &r0, T &r1) {
  T pmin = min(p0, p1), pmax = max(p0, p1);
  T qmin = min(q0, q1), qmax = max(q0, q1);
  r0 = max(pmin, qmin), r1 = min(pmax, qmax);
  return r0 <= r1;
}

template <class T>
bool rectisect(const point<T> &p0, const point<T> &p1,
	       const point<T> &q0, const point<T> &q1,
	       point<T> &r0, point<T> &r1) {
  bool xflag = ivalisect(p0.x, p1.x, q0.x, q1.x, r0.x, r1.x);
  bool yflag = ivalisect(p0.y, p1.y, q0.y, q1.y, r0.y, r1.y);
  return xflag && yflag;
}
