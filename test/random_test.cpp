#include "../general/7_random.cpp"
#include <iostream>

int div[1<<15], rest[1<<15];
const int N = 1000000;

int main( void ) {
  for( int i=0; i<N; i++ ) {
    int r = pseudo();
    div[r/(1<<15)%(1<<15)]++;
    rest[r%(1<<15)]++;
  }

  for( int i=0; i<(1<<15); i++ ) {
    if( rest[i] < 10 || rest[i] > 60 )
      cout << i << endl;
    if( div[i] < 10 || div[i] > 60 )
      cout << i << endl;
  }
}
