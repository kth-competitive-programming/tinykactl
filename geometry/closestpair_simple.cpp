/*****************************************************************************
 * 
 * Geometry6: closestpair
 * ======================
 *
 * Return the pair with the shortest distance. The algorithm is
 * a heuristic-optimized version of the simple n^2 algorithm.
 * It sorts the points after the x-coord and only searches a
 * small x-interval.
 *
 * INPUT
 * -----
 * p:      An array of size n with the points.
 * n:      the number of points (>=2).
 * i1, i2: the indices of the points in the closest pair.
 *
 * OUTPUT
 * ------
 * dist:   the distance of the closest pair.
 *
 * COMPLEXITY  worst: O( n^2 ), average: O(n)?
 *
 * REQUIRES  geometry.h, general/indexed.cpp
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
#include "../general/1_indexed.cpp"
#include <iterator>
#include <vector>


template<class V>     // R is random access iterators of point<T>s
double closestpair( const V &p, int n, int &i1, int &i2 ) {
  typedef typename iterator_traits<V>::value_type P;
  vector< int > idx;

  if( n < 2 )
    throw "closestpair called with less than 2 points";

  // Sort points "naturally" (i.e. first after x then after y)
  idx.resize( n );
  isort( p, n, idx.begin() );

  indexed<P> q(p, idx.begin() );

  double minDist = dist2(q[0],q[1]);
  i1 = 0; i2 = 1;
  for( int i=0; i<N; i++ ) {
    double stopX = q[i].x+sqrt(minDist);
    for( int j=i+1; j<N; j++ ) {
      if( q[j].x >= stopX )
	break;
      double d = dist2(q[i],q[j]);
      if( d<minDist ) {
	i1 = i;
	i2 = j;
	minDist = d;
      }
    }
  }

  return sqrt(minDist);
}
