#include <iostream>
#include <algorithm>

using namespace std;

#include "../obsolete/4_vectorized_function.cpp"


int square( int a ) { return a*a; }

int main( void ) {
  /*  vectorized_fn<int (*)(int)> vfn( 0, 100, square );

  int i = lower_bound( vfn.begin(), vfn.end(), 25 )-vfn.begin();
  */

  int i = lower_bound( make_fn_iter(square,0),
		       make_fn_iter(square,100), 36 ).offset();

  cout << i;
}
