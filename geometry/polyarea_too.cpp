/*****************************************************************************
 * 
 * Geometry4: polygon area
 * =======================
 *
 * Returns area with orientation (positive if ccw)
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

#include <iterator>
#include "geometry.h"


template <class V>
double poly_area(V p, int n) {
  int j = n - 1;
  typename iterator_traits<V>::value_type::coord_type a = 0;
  for (int i = 0; i < n; i++) {
    a += (p[j].x - p[i].x) * (p[j].y + p[i].y);
    j = i;
  }
  return (double) a / 2;
}

