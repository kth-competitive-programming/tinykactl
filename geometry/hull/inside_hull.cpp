/*****************************************************************************
 * 
 * 1_inside_hull: Point in hull test
 * =================================
 *
 * INPUT
 * -----
 *
 * OUTPUT
 * ------
 *
 * COMPLEXITY  O( log n )
 *
 * REQUIRES  geometry.h, 2_pointline.cpp
 * ------------------------------------------------------------------------- *
 *
 * NADA acmlib (10 March 2002)
 * Templates for KTH-NADA, Ballons'R'Us, ACM 2001-2002
 *   Swedish competition, Link?ping 6 Oct 2001
 *   Revised for SWERC, Portu, Portugal 17 Nov 2001
 *   Revised for World Finals, Honolulu, 23 Mar 2002
 *   David Rydh, Mattias de Zalenski, Fredrik Niemelä
 *
 *****************************************************************************/

#include "../geometry.h.cpp"
#include "../pointline.cpp"

template <class V, class T>
int inside_hull_sub(const V &p, int n, const point<T> &t, int i1, int i2) {
  if (i2 - i1 <= 2) {
    int s0 = sideof(p[0], p[i1], t);
    int s1 = sideof(p[i1], p[i2], t);
    int s2 = sideof(p[i2], p[0], t);
    if (s0 < 0 || s1 < 0 || s2 < 0)
      return -1;
    if (i1 == 1 && s0 == 0 || s1 == 0 || i2 == n - 1 && s2 == 0)
      return 0;
    return 1;
  }
  int i = (i1 + i2) / 2;
  int side = sideof(p[0], p[i], t);
  if (side > 0)
    return inside_hull_sub(p, n, t, i, i2);
  else
    return inside_hull_sub(p, n, t, i1, i);
}

template <class V, class T>
int inside_hull(const V &p, int n, const point<T> &t) {
  if (n < 3)
    return onsegment(p[0], p[n - 1], t) ? 0 : -1;
  else
    return inside_hull_sub(p, n, t, 1, n - 1);
}
