#include <iostream>

#include "../geometry/5_closestpair.cpp"
#include "../geometry/6_closestpair_simple.cpp"

const int N=500000;

int main() {
  vector< point<int> > points;
  double d;
  int i1, i2;

  for( int i=0; i<N; i++ )
    points.push_back( point<int>(rand(), rand()) );

  d = closestpair( points.begin(), N, i1, i2 );
  cout << d << " " << i1 << "-" << i2 << endl;
  d = closestpair_simple( points.begin(), N, i1, i2 );
  cout << d << " " << i1 << "-" << i2 << endl;

  /*
  double minDist = 1e40;
  for( int i=0; i<N; i++ )
    for( int j=i+1; j<N; j++ )
      minDist = min(minDist,dist2(points[i],points[j]));

  cout << sqrt(minDist) << endl;
  */

  return 0;
}
