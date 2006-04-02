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
 *   Revised for World Finals, Prague, 31 Mar 2004
 *   Per Austrin, Max Bennedich, Gunnar Kreitz
 *
 *****************************************************************************/

#include "point_line_relations.cpp"

template <class It, class P>
int inside_hull_sub(It begin, It end, It i1, It i2, const P&t) {
  if (i2 - i1 <= 2) {
    int s0 = sideof(*begin, *i1, t);
    int s1 = sideof(*i1, *i2, t);
    int s2 = sideof(*i2, *begin, t);
    if (s0 < 0 || s1 < 0 || s2 < 0) return -1;
    if (i1 == begin+1 && s0 == 0 || s1 == 0 || 
	i2 == end - 1 && s2 == 0)
      return 0;
    return 1;
  }
  It i = (i1 + i2) / 2; //??
  int side = sideof(p[0], p[i], t);
  if (side > 0) return inside_hull_sub(begin, end, i, i2, t);
  else return inside_hull_sub(begin, end, i1, i, t);
}

template <class It, class P>
int inside_hull(It begin, It end, const P &t) {
  if (end - begin < 3) 
    return onsegment(*begin, end[-1], t) ? 0 : -1;
  else return inside_hull_sub(begin, end, begin+1, end-1, t);
}
