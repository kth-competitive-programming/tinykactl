#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

#include "../geometry/geometry.h.cpp"
#include "../geometry/point.cpp"
#include "../geometry/inside.cpp"
#include "../geometry/winding_number.cpp"

typedef point<double> Pt;

const int N = 400;

Pt a[N];

int main() {
  a[0] = Pt(-1, 3);
  a[1] = Pt(3, -1);
  a[2] = Pt(3, 3);
  for (int i = 0; i < 5; i++)
    cout << i << "," << i << ": " << inside(a,3, Pt(i, i)) << " "
	 << inside_wn(a, 3, Pt(i,i)) << endl;
  for (int i = 3; i < N; i++)
    a[i] = Pt(cos(i * pi / N) * 2 + 1, sin(i * pi / N) + 3);
  a[N / 2] = Pt(1, 4);
  for (int i = -1; i < 10; i++) {
    Pt p = Pt(3 - i / 2.5, -1 + i);
    cout << p.x << "," << p.y << ": " << inside(a,N, p) << " "
	 << inside_wn(a,N, p) << endl;
  }

  cout << endl;

  vector< point<int> > poly;

  poly.push_back( point<int>(0,2) );
  poly.push_back( point<int>(8,2) );
  poly.push_back( point<int>(8,8) );
  poly.push_back( point<int>(2,8) );
  poly.push_back( point<int>(2,0) );
  poly.push_back( point<int>(4,0) );
  poly.push_back( point<int>(4,6) );
  poly.push_back( point<int>(6,6) );
  poly.push_back( point<int>(6,4) );
  poly.push_back( point<int>(0,4) );


  for( int y=9; y>=-1; y-- ) {
    for( int x=-1; x<=9; x++ )
      cout << setw(2)
	   << inside(poly.begin(),poly.size(),point<int>(x,y)) << ','
	   << inside_wn(poly.begin(),poly.size(),point<int>(x,y)) << ' ';
    cout << "   ";

    bool onEdge;
    for( int x=-1; x<=9; x++ )
      cout << (int)(winding_nr(poly.begin(),poly.size(),
				    point<int>(x,y), onEdge)+0.5) << ' ';
    cout << endl;
  }

  return 0;
}
