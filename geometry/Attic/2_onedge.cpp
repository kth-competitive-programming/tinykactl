/*****************************************************************************
 * 
 * Geometry2: onedge
 * =================
 *
 * Determine if a point is on the edge of a polygon.
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
 * bool  true if the point is on the edge of the polygon.
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

template<class T, class V>      // V is vector/array of point<T>s
bool on_edge(const point<T> &t, const V &p, int n) {
  for (int i=0, j=n-1; i<n; j=i++) {
    if ( p[i].y == p[j].y ) {
      if ( t.y == p[i].y && ( (p[i].x<=t.x && t.x<=p[j].x)
			   || (p[j].x<=t.x && t.x<=p[i].x) )
        return true;
    } else if ( ((p[i].y<=t.y && t.y<p[j].y) || (p[j].y<=t.y && t.y<p[i].y)) &&
        (t.x == p[i].x + (p[j].x - p[i].x)*(t.y - p[i].y)/(p[j].y - p[i].y)) )
      return true;
  }

  return false;
}

