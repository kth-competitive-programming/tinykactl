#include <iostream>
using namespace std;
#include "../numerical/pseudo.cpp"

int divs[1<<15], rest[1<<15];
const int N = 1000000;

int main( void ) {
  for( int i=0; i<N; i++ ) {
    int r = pseudo();
    divs[r/(1<<15)%(1<<15)]++;
    rest[r%(1<<15)]++;
  }

  for( int i=0; i<(1<<15); i++ ) {
    if( rest[i] < 10 || rest[i] > 60 )
      cout << i << endl;
    if( divs[i] < 10 || divs[i] > 60 )
      cout << i << endl;
  }
}
