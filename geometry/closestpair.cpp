/*****************************************************************************
 * 
 * Geometry5: closestpair
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
 * COMPLEXITY  O(n * log n)
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

#include <iterator>
#include <vector>

struct x_sort {
  template<class P>
  bool operator()(const P &p1, const P &p2) const
  { return p1.x < p2.x; }
};
struct y_sort {
  template<class P>
  bool operator()(const P &p1, const P &p2) const
  { return p1.y < p2.y; }
};
struct xy_sort {
  template<class P>
  bool operator()(const P &p1, const P &p2) const
  { return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y); }
};

template<class V, class R>
double closestpair_sub(const V &p, int n, R xa, R ya, int &i1, int &i2) {
  typedef typename V::value_type P;
  vector< int > lefty, righty;

  if( n <= 3 ) {   // base case
    double a = dist( p[xa[1]]-p[xa[0]] );
    if( n == 3 ) {
      double b = dist( p[xa[2]]-p[xa[0]] );
      double c = dist( p[xa[2]]-p[xa[1]] );
      if(a <= b) {
	 i1 = xa[1];
	 if(a <= c) {
	    i2 = xa[0];
	    return a;
	 } else {
	    i2 = xa[2];
	    return c;
	 }
      } else {
	 i1 = xa[2];
	 if(b <= c) {
	    i2 = xa[0];
	    return b;
	 } else {
	    i2 = xa[1];
	    return c;
	 }
      }
    } else {
      i1 = xa[0];
      i2 = xa[1];
      return a;
    }
  }

  int split = n/2;  // Divide
  P splitp = p[xa[split]];

  for( int i=0; i<n; i++ ) {
    if(ya[i] != xa[split] && d2(p[ya[i]],splitp) < 1e-12) {
      i1 = ya[i];
      i2 = xa[split];
      return 0;
    }
    if( p[ya[i]] < splitp )
      lefty.push_back( ya[i] );
    else
      righty.push_back( ya[i] );
  }

  int j1,j2;  // Conquer
  assert(lefty.size() == split);
  double a = closestpair_sub( p, split, xa, lefty.begin(), i1, i2 );
  double b = closestpair_sub( p, n-split, xa+split, righty.begin(), j1, j2 );

  if( b<a ) a = b, i1=j1, i2=j2;

  vector<int> stripy; // Combine: Create strip (with sorted y)
  double splitx = splitp.x;

  for( int i=0; i<n; i++ ) {
    double x = p[ya[i]].x;

    if( x >= splitx-a && x <= splitx+a )
      stripy.push_back( ya[i] );
  }

  int nStrip = stripy.size();
  double a2 = a*a;

  for( int i=0; i<nStrip; i++ ) {
    const P &p1 = p[stripy[i]];

    for( int j=i+1; j<nStrip; j++ ) {
      const P &p2 = p[stripy[j]];

      if( dy(p1,p2) > a )
	break;

      double d2 = dist2(p2-p1);
      if( d2<a2 ) {
	i1 = stripy[i];
	i2 = stripy[j];
	a2 = d2;
        a = sqrt(a2);
      }
    }
  }

  return a;
}

inline double sqr(double a) {
   return a * a;
}

double d2(point<double> p1, point<double> p2) {
   return sqr(p1.x - p2.x) + sqr(p1.y - p2.y);
}

template<class V>     // R is random access iterators of point<T>s
double closestpair( const V &p, int n, int &i1, int &i2 ) {
  vector< int > xa, ya;

  assert(n >= 2);

  xa.resize( n );
  ya.resize( n );
  isort( p, n, xa.begin(), xy_sort() );
  isort( p, n, ya.begin(), y_sort() );

  return closestpair_sub( p, n, xa.begin(), ya.begin(), i1, i2 );
}
