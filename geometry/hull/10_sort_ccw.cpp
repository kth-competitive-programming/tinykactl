/*****************************************************************************
 * 
 * 10_sort_ccw: Get points from a hull in ccw-order
 * ================================================
 *
 * COMPLEXITY  O( n log n )
 *
 * REQUIRES  geometry.h, general/1_indexed.cpp
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

#include "../geometry.h"
#include "../../general/1_indexed.cpp"

// V should be RandomAccessIterator to point<T>s.
// R should be RandomAccessIterator to ints.
template <class V, class R>
void sort_ccw(V p, R idx, int n) {
  typedef typename iterator_traits<V>::value_type P;
  vector<double> angles;
  P center = P();

  for( int i=0; i<n; i++ )
    center.x += p[i].x, center.y += p[i].y;
  center.x /= n, center.y /= n;

  angles.resize( n );
  for( int i=0; i<n; i++ )
    angles[i] = angle(center,p[i]);

  isort( angles.begin(), n, idx );
}
