/*****************************************************************************
 * 
 * 2_hull_diameter: Hull diameter
 * ==============================
 *
 * Longest diameter of a ccw polygon.
 *
 * INPUT
 * -----
 *
 * Polygon, number of polygon points, two int references
 *
 * OUTPUT
 * ------
 *
 * Fills in two indeces to the longest hull diameter points.
 * Returns the longest distance squared.
 *
 * COMPLEXITY  O( n )
 *
 * REQUIRES  geometry.h, dist2 from geometry_ops.cpp
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
#include "../geometry.h"

template <class V>
double hull_diameter2(V p, int n, int &i1, int &i2) {
  if (n < 2) { i1 = i2 = 0; return 0; }
  double m = 0; 
  int i, j = 1, k = 0;
  // wander around
  for (i = 0; i <= k; i++) { 
    // find opposite
    double d2 = dist2(p[i], p[j]);
    while (j + 1 < n) {
      double t = dist2(p[i], p[j + 1]);
      if (t > d2) d2 = t; else break;
      j++;
    }
    if (i == 0) k = j; // remember first opposite index
    if (d2 > m) m = d2, i1 = i, i2 = j;
  }
  //  cout << "first opposite: " << k << endl;
  return m;
}
