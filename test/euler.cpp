#include <iostream>

using namespace std;

#include "../graph/deBruijn.cpp"
#include "../graph/deBruijn_fast.cpp"

int main( void ) {
  //deBruijn( 2, 16, "10" );
  //deBruijn( 3, 7, "ABC" );

  deBruijn_fast( 2, 16, "10" );
  deBruijn_fast( 3, 7, "ABC" );
}
