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
  { return p1.x < p2.x; }
};

// Gives square distance of closest pair.
template<class V, class R>
double closestpair_sub(const V &p, int n, R xa, R ya, int &i1, int &i2) {
  typedef typename iterator_traits<V>::value_type P;
  vector< int > lefty, righty;

  // 2 or 3 points
  if( n <= 3 ) {
    // Largest dist is either between the two farthest in x or y.
    double a = dist2( p[xa[1]]-p[xa[0]] );
    if( n == 3 ) {
      double b = dist2( p[xa[2]]-p[xa[0]] );
      double c = dist2( p[xa[2]]-p[xa[1]] );

      return min(a,min(b,c));
    } else
      return a;
  }

  // Divide
  int split = n/2;
  double splitx = p[xa[split]].x;

  for( int i=0; i<n; i++ ) {
    if( p[ya[i]].x < splitx )
      lefty.push_back( ya[i] );
    else
      righty.push_back( ya[i] );
  }

  // Conquer
  int j1,j2;
  double a = closestpair_sub( p, split, xa, lefty.begin(), i1, i2 );
  double b = closestpair_sub( p, n-split, xa+split, righty.begin(), j1, j2 );

  if( b<a ) a = b, i1=j1, i2=j2;

  // Combine: Create strip (with sorted y)
  vector<int> stripy;

  for( int i=0; i<n; i++ ) {
    double x = p[ya[i]].x;

    if( x >= splitx-a && x <= splitx+a )
      stripy.push_back( ya[i] );
  }

  int nStrip = stripy.size();
  double a2 = a*a;

  //  cout << "Combining " << nStrip << " points...";
  //  cout.flush();

  for( int i=0; i<nStrip; i++ ) {
    P &p1 = p[stripy[i]];

    for( int j=i+1; j<nStrip; j++ ) { // This loop will be run <8 times/"i"
      P &p2 = p[stripy[j]];

      if( dy(p1,p2) > a )
	break;

      double d2 = dist2(p2-p1);
      if( d2<a2 ) {
	i1 = stripy[i];
	i2 = stripy[j];
	a2 = d2;
      }
    }
  }

  //  cout << " done" << endl;
  return sqrt(a2);
}

template<class V>     // R is random access iterators of point<T>s
double closestpair( const V &p, int n, int &i1, int &i2 ) {
  vector< int > xa, ya;

  if( n < 2 )
    throw "closestpair called with less than 2 points";

  xa.resize( n );
  ya.resize( n );
  isort( p, n, xa.begin(), x_sort() );
  isort( p, n, ya.begin(), y_sort() );

  return closestpair_sub( p, n, xa.begin(), ya.begin(), i1, i2 );
}
