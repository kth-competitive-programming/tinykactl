/*****************************************************************************
 * 
 * Geometry9: centerofmass
 * =======================
 *
 * Calculate the (area-based) center-of-mass for a polygon which
 * does not need to be convex (nor simple?).
 * Polygon should be given in ccw-order.
 *
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

#include <iterator>
#include "geometry.h"

template <class V>
inline double tri_area(V p) { // cross-product / 2
  return ((double)dx(p[0],p[1])*dy(p[0],p[2])-
         (double)dy(p[0],p[1])*dx(p[0],p[2]))/2;
}

template <class V>
void centerofmass( V p, int n, point<double> &com ) {
  com.x = com.y = 0.0;

  if( n<=3 ) {
    // Simple case
    for( int i=0; i<n; i++ ) {
      com.x += p[i].x;
      com.y += p[i].y;
    }
    com.x /= n;
    com.y /= n;
  } else {
    // More difficult case (NB! poly must be in ccw order!)
    typedef typename iterator_traits<V>::value_type::coord_type T;
    point<T> tri[3];

    tri[0] = p[0];

    double totarea=0.0, area;
    point<double> tri_com;
    for( int i=2; i<n; i++ ) {
      tri[1] = p[i-1];
      tri[2] = p[i];
      area = tri_area( tri ); // (with orientation)

      centerofmass( tri, 3, tri_com );
      com.x += area*tri_com.x;
      com.y += area*tri_com.y;
      totarea += area<0 ? -area:area;
    }
    com.x /= totarea;
    com.y /= totarea;
  }
}
