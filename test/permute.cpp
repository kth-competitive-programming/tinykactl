#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

#include "../combinatorial/permute.cpp"
//#include "../tinystl/permutation.cpp"
//#include "../tinystl/base.cpp"
#include <algorithm>

int main() {
  char x[100];
  int d, n;

  cin >> d >> x;
  n = strlen(x);

  if( d==1 )
    permute( x+0, x+0, x+n );
  else do {
    for( int i=0; i<n; i++ )
      cout << x[i];
    cout << endl;
  } while( next_permutation(x+0, x+n) );

  return 0;
}
