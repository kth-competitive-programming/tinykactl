#include <cmath>
#include <cstdio>
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
  double a=2.474747474747;
  for( int i=0; i<10; i++ ) {
//	  cout.setf( ios::fixed );
	  cout << setprecision(i) << a << ' ';
	  printf( "%.*f\n", i, a );
  }

  // Kylix rounds in cout when using ios::fixed but not otherwise.
  // Also, setprecision(0) without fixed means 1 digit.

  // GCC always rounds. setprecision(0) means the default number of digits, 6.

  // Both compilers work fine with fixed and printf (then the numbers are
  // always rounded).
	  

  return 0;
}
