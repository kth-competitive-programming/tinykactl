/* @JUDGE_ID:  16100CR  10111  C++  "" */

// Popuptävling 23/9 2002

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <algorithm>
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <cmath>

using namespace std;

const int N = 0;
const bool deBug = true;

bool solve(int P);

int main() {
  // while-solve
  int n = 0;
  while (solve(n))
    n++;

  return 0;
}

const int W = 3*3*3*3 *3*3*3*3 *3*3*3*3;

int n;
int empty[12];
signed char dyn[W];
char board[16];

int rows[4], cols[4], dia1[7], dia2[7];

int find( int x, bool turnX ) {
  if( dyn[x]!=99 )
    return dyn[x];

  int count = 0;
  int mul2 = 1;
  for( int i=0; i<n; i++ ) {
    int j = empty[i];

    if( board[j] == '.' ) {
      int mul = turnX ? 1:-1;
      int r, c, d1, d2;

      board[j] = turnX ? 'x':'o';
      r = j/4;
      c = j%4;
      d1 = (j%4)+(j/4);
      d2 = (j/4)+3-(j%4);
      rows[r] += mul;
      cols[c] += mul;
      dia1[d1] += mul;
      dia2[d2] += mul;

      if( rows[r] == 4*mul || cols[c] == 4*mul ||
	  dia1[d1] == 4*mul || dia2[d2] == 4*mul )
      {
	board[j] = '.';
	rows[r] -= mul;
	cols[c] -= mul;
	dia1[d1] -= mul;
	dia2[d2] -= mul;

	if( turnX )
	  return dyn[x]=j;
	else
	  return dyn[x]=100;
      }
      int res = find( turnX ? (x + mul2):(x+2*mul2), !turnX );

      board[j] = '.';
      rows[r] -= mul;
      cols[c] -= mul;
      dia1[d1] -= mul;
      dia2[d2] -= mul;

      if( res != 100 ) {
	if( turnX )
	  return dyn[x]=j;
	else
	  count++;
      } else {
	if( !turnX )
	  return dyn[x]=100;
      }
    }

    mul2 *= 3;
  }

  if( count > 0 )
    return dyn[x]=0; // Value doesn't matter as long as it is 0-15

  return dyn[x]=100;
}

bool solve(int P) {
  char c;

  cin >> c;

  if( c=='$' )
    return false;

  for( int i=0; i<4; i++ )
    rows[i] = cols[i] = 0;
  for( int i=0; i<6; i++ )
    dia1[i] = dia2[i] = 0;

  n = 0;
  for( int i=0; i<16; i++ ) {
    int r,c,d1,d2;

    r = i/4;
    c = i%4;
    d1 = (i%4)+(i/4);
    d2 = (i/4)+3-(i%4);

    cin >> board[i];
    if( board[i] == '.' )
      empty[n++] = i;
    else {
      int mul = (board[i] == 'x') ? 1:-1;

      rows[r]+=mul;
      cols[c]+=mul;
      dia1[d1]+=mul;
      dia2[d2]+=mul;
    }
  }

  memset( dyn, 99, sizeof(dyn)*sizeof(*dyn) );

  int x = find( 0, true );

  if( x==100 )
    cout << "#####" << endl;
  else
    cout << '(' << x/4 << ',' << x%4 << ')' << endl;

  return true;
}
