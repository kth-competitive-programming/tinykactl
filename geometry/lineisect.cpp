/*****************************************************************************
 * 
 * Geometry2: pointline
 * ====================
 *
 * lineisect: Line intersection.
 *
 * INPUT
 * -----
 * p1, p2: A line.
 * q1, q2: A line.
 *
 * OUTPUT
 * ------
 * lineisect: bool, intersection point reference
 *     true if lines intersect.
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
