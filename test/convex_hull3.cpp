/******************************************
 *
 * @JUDGE_ID: 16100CR 10078 C++
 *
 * Problem 10078 "The Art Gallery"
 *
 * David Rydh, <f99-dry@nada.kth.se>
 * March 2002
 *****************************************/

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

#include "../geometry/point.cpp"
#include "../geometry/point_ops.cpp"
#include "../geometry/hull/convex_hull_idx.cpp"


int main( void ) {
  vector< point<int> >  points;
  vector< int >         hull;

  while( true ) {
    int n;

    cin >> n;

    if( n==0 )
      break;

    points.resize( n );
    for( int i=0; i<n; i++ )
      cin >> points[i].x >> points[i].y;

    hull.resize( n );
    int r = convex_hull( points.begin(), hull.begin(), n );

    cout << (r<n ? "Yes" : "No") << endl;
  }

  return 0;
}
