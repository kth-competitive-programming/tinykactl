#include <iostream>
#include <vector>

using namespace std;

#include "../pattern/kmp.cpp"

int main( void ) {
  vector<char> text;
  char line[500];

  while( cin.getline(line, 500) ) {
    for( int i=0; line[i]; i++ )
      text.push_back( line[i] );
    text.push_back( '\n' );
  }

  int i = 0;

  while( true ) {
    int j = kmp( &text[i], "push" );
    if( j<0 )
      break;
    cout << i+j << " " << text[i+j] << endl;
    i += j+1;
  }

  return 0;
}
