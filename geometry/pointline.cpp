/*****************************************************************************
 * 
 * Geometry2: pointline
 * ====================
 *
 * sideof: Determine on which side of a line a point is (+/- 1 or 0)
 * onsegment: Determine if a point is on a line segment (incl the end points).
 * linedist: Get a measure of the distance of a point from a line (0 on the
 *           line and positive/negative on the different sides).
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

template <class P>
int sideof(P p0, P p1, P q) {
  P::coord_type d = cross(p1-p0, q-p0);
  return d > 0 ? 1 : d < 0 ? -1 : 0;
}

template<class P>
bool onsegment(P p0, P p1, P q) {
  // Check if point is outside line segment rectangle.
  if( dx(p0,q)*dx(p1,q) > 0 || dy(p0,q)*dy(p1,q) > 0 )
    return false;

  // Check if point is on line (not line segment)
  return cross(p1-p0, q-p0) == 0;
}

template <class P>
T linedist(P p0, P p1, P q) {
  return cross(p1-p0, q-p0);
}
