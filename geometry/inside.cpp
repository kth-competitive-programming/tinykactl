/*****************************************************************************
 * 
 * Geometry1: inside
 * =================
 *
 * Determine if a point is inside a polygon. If the point is on the edge the
 * algorithm may return both true and false.
 * To check if the point is really inside or on the edge, use on_edge.
 *
 * INPUT
 * -----
 * t:    The test point
 * p:    An array of size n representing the polygon, given as points either
 *       in cw or ccw order. (the start/end point should not be repeated)
 * n:    the number of vertices
 *
 * OUTPUT
 * ------
 * bool  true if the point is inside the polygon and false otherwise.
 *
 * COMPLEXITY  O( n )
 *
 * REQUIRES  geometry.h
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

template<class P, class V>     // V is vector/array of point<T>s
bool inside(P t, const V &p, int n) {
  bool c = false;

  for (int i=0, j=n-1; i<n; j=i++) {
    if ( ((p[i].y<=t.y && t.y<p[j].y) || (p[j].y<=t.y && t.y<p[i].y)) &&
         (dx(p[i],t) < dx(p[i],p[j])*dy(p[i],t)/dy(p[i],p[j])) )
      c = !c;
  }
  return c;
}
