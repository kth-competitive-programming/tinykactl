#include <iostream>
#include <vector>
#include <utility>

using namespace std;

#include "../geometry/point.cpp"
#include "../geometry/point_ops.cpp"
#include "../geometry/hull/convex_hull.cpp"
#include "../geometry/hull/convex_hull_robust_idx.cpp"

int main( void ) {
  vector< point<int> >  points;
  vector< int >         hull;

  for( int x=-5; x<=5; x++ ) {
    for( int y=-5; y<=5; y++ ) {
      if( x*x+y*y <=25 )
	points.push_back( point<int>(x,y) );
    }
  }

  int n = points.size(), r;
  hull.resize( n );

  //  r = convex_hull( points.begin(), hull.begin(), n );
  r = convex_hull_robust( points.begin(), hull.begin(), n );

  for( int i=0; i<r; i++ )
    cout << "(" << points[hull[i]].x << "," << points[hull[i]].y << ")"<< endl;

  return 0;
}
