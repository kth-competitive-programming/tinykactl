/*****************************************************************************
 * 
 * Geometry1: inside_poly
 * ======================
 *
 * Determine if a point is inside/outside or on the edge of a polygon.
 *
 * INPUT
 * -----
 * p:    An array of size n representing the polygon, given as points either
 *       in cw or ccw order. (the start/end point should not be repeated)
 * n:    the number of vertices
 * t:    The test point
 *
 * OUTPUT
 * ------
 * +1    inside
 * 0     on the edge
 * -1    outside
 *
 * COMPLEXITY  O( n )
 *
 * REQUIRES  geometry.h, pointline.cpp (onedge)
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

#include "pointline.cpp"

template<class V, class P>
double winding_nr(const V &p, int n, P t, bool &onEdge) {
  double wind = 0;

  onEdge = false;

  for (int i=0, j=n-1; i<n; j=i++) {
    if( onsegment(p[i], p[j], t) ) {
      onEdge = true;
      continue;
    }
    double t1 = theta(t-p[i]), t2 = theta(t-p[j]);
    double dt = t1-t2;
    if( dt > 2 ) dt -= 4;
    if( dt < -2 ) dt += 4;
    wind += dt;
  }

  return wind;
}

template<class P, class V>     // V is vector/array of point<T>s
int inside_poly(P t, const V &p, int n) {
  bool edge;
  double wind = winding_nr(p,n,t, edge);

  if( edge ) return wind>4 ? 1:0;

  // Not on edge, i.e. wind is (approx) 4*nr of turns.
  return wind > 2 ? 1:-1;
}
