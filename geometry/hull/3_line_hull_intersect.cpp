/*****************************************************************************
 * 
 * 3_line_hull_intersect: Line hull intersection
 * =============================================
 *
 * <explanation>
 *
 * INPUT
 * -----
 *
 * OUTPUT
 * ------
 *
 * COMPLEXITY  -
 *
 * REQUIRES  geometry.h, 2_linepoint.cpp
 * ------------------------------------------------------------------------- *
 *
 * NADA acmlib (10 March 2002)
 * Templates for KTH-NADA, Ballons'R'Us, ACM 2001-2002
 *   Swedish competition, Linköping 6 Oct 2001
 *   Revised for SWERC, Portu, Portugal 17 Nov 2001
 *   Revised for World Finals, Honolulu, 23 Mar 2002
 *   David Rydh, Mattias de Zalenski, Fredrik Niemelä
 *
 *****************************************************************************/

#include "../geometry.h"
#include "../2_pointline.cpp"

template <class V, class T>
struct line_hull_isct {
  const V &p;
  int n;
  const point<T> &p1, &p2;
  int &s1, &s2;
  line_hull_isct(const V &_p, int _n, const point<T> &_p1, const point<T> &_p2,
		 int &_s1, int &_s2)
    : p(_p), n(_n), p1(_p1), p2(_p2), s1(_s1), s2(_s2) {
  }
  
// assumes 0 <= md <= i1d, i2d
  bool isct(int i1, int m, int i2, double md) {
    if (md <= 0) {
      s1 = findisct(i1, m) % n;
      s2 = findisct(i2, m) % n;
      return true;
    }
    if( i2-i1 <= 2 )
      return false;
    int l = (i1 + m) / 2;
    int r = (m + i2) / 2;
    double ld = linedist(p1, p2, p[l % n]);
    double rd = linedist(p1, p2, p[r % n]);
    if (ld <= md && ld <= rd)
      return isct(i1, l, m, ld);
    if (rd <= md && rd <= ld)
      return isct(m, r, i2, rd);
    else
      return isct(l, m, r, md);
  }
  int findisct(int pos, int neg) {
    int m = (pos + neg) / 2;
    if (m == pos) return pos;
    if (m == neg) return neg;
    double d = linedist(p1, p2, p[m % n]);
    if (d <= 0)
      return findisct(pos, m);
    else
      return findisct(m, neg);
  }
};

template <class V, class T>
bool line_hull_intersect(const V &p, int n,
			 const point<T> &p1, const point<T> &p2,
			 int &s1, int &s2) {
  double d = linedist(p1, p2, p[0]);
  if (d >= 0)
    return line_hull_isct<V, T>(p, n, p1, p2, s1, s2).isct(0, n, 2 * n, d);
  else
    return line_hull_isct<V, T>(p, n, p2, p1, s1, s2).isct(0, n, 2 * n, -d);
}
