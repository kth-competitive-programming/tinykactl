/******************************************
 *
 * @JUDGE_ID: 16100CR 10358 C++
 *
 * Problem 10358 "Matrix"
 *
 * David Rydh, <f99-dry@nada.kth.se>
 * POPUP TÅ‰vling 3 (Valladolid), 2002-09-13
 *****************************************/

#include <iostream>
#include <cstdio>
#include <algorithm>
//#include <string>
#include <queue>
//#include <set>
//#include <map>
//#include <cmath>

using namespace std;

const int N = 0;

int wins[64][64][64][3]; // M, A1, A2
int nrs[64][64][64][3]; // M, A1, A2

int wall[64], phone[64];

bool solve(int P);

int main() {
  //for-solve
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
    solve(i);

  return 0;
}


queue<int> s;

void calc( int pos[3], int t, int w ) {
  bool p = false;

  if( wall[pos[t]] )
    return;

  if( wins[pos[0]][pos[1]][pos[2]][t] < 0 )
    return;

  if( t!=0 ) {
    if( w==3 ) {
      wins[pos[0]][pos[1]][pos[2]][t] = -1;
      p = true;
    } else {
      wins[pos[0]][pos[1]][pos[2]][t]++;
      if( wins[pos[0]][pos[1]][pos[2]][t] == nrs[pos[0]][pos[1]][pos[2]][t] ) {
	wins[pos[0]][pos[1]][pos[2]][t] = -2;
	p = true;
      }
    }
  } else {
    if( w==1 ) {
      wins[pos[0]][pos[1]][pos[2]][t] = -1;
      p = true;
    } else {
      wins[pos[0]][pos[1]][pos[2]][t]++;
      if( wins[pos[0]][pos[1]][pos[2]][t] == nrs[pos[0]][pos[1]][pos[2]][t] ) {
	wins[pos[0]][pos[1]][pos[2]][t] = -2;
	p = true;
      }
    }
  }

  if( p ) {
    //    cout << pos[0] << ' ' << pos[1] << ' ' << pos[2] << ' ' << t << ' ' <<
    //      wins[pos[0]][pos[1]][pos[2]][t] << endl;
    s.push( pos[0]*64*64*3 + pos[1]*64*3 + pos[2]*3 + t );
  }
}

bool solve(int P) {
  int i = 0;
  int start[3], a=1;

  memset( wins, 0, 64*64*64*3*sizeof(int) );

  //  s.clear();

  for( int r=0; r<8; r++ ) {
    for( int c=0; c<8; c++, i++ ) {
      char ch;

      cin >> ch;
      wall[i] = (ch=='#' ? 1:0);
      if( ch=='A' )
	start[a++] = i;
      else if( ch=='M' )
	start[0] = i;

      phone[i] = (ch=='P' ? 1:0);

    }
  }

  for( int i=0; i<64; i++ ) {
    if( wall[i] )
      continue;
    for( int a=0; a<64; a++ ) {
      if( wall[a] )
	continue;
      for( int b=0; b<64; b++ ) {
	if( wall[b] )
	  continue;
	for( int t=0; t<3; t++ ) {
	  if( a==i || b==i )
	    wins[i][a][b][t] = (t==0 ? -2:-1);
	  else if( phone[i] )
	    wins[i][a][b][t] = (t==0 ? -1:-2);
	  else
	    wins[i][a][b][t] = 0;

	  if( wins[i][a][b][t] != 0 )
	    s.push( i*64*64*3 + a*64*3 + b*3 + t );

	  // Count out-degree
	  int k = t==0?i:(t==1?a:b);
	  int n = 0;

	  if( k>=8 && !wall[k-8] ) n++;
	  if( k<56 && !wall[k+8] ) n++;
	  if( k%8>0 && !wall[k-1] ) n++;
	  if( k%8<7 && !wall[k+1] ) n++;
	  nrs[i][a][b][t] = n;
	}
      }
    }
  }

  while( !s.empty() ) {
    int x = s.front();
    int pos[3], t, turn;
    int w;
    s.pop();

    pos[0] = x/64/64/3;
    pos[1] = (x/64/3)%64;
    pos[2] = (x/3)%64;
    turn = x%3;
    w = wins[pos[0]][pos[1]][pos[2]][turn];
    if( turn==0 )
      w = w==-1 ? 1:3;
    else
      w = w==-1 ? 3:1;

    t = (turn+2)%3;

    if( pos[t]>=8 ) {
      pos[t]-=8;
      calc( pos, t, w );
      pos[t]+=8;
    }
    if( pos[t]<56 ) {
      pos[t]+=8;
      calc( pos, t, w );
      pos[t]-=8;
    }
    if( pos[t]%8 > 0 ) {
      pos[t]--;
      calc( pos, t, w );
      pos[t]++;
    }
    if( pos[t]%8 < 7 ) {
      pos[t]++;
      calc( pos, t, w );
      pos[t]--;
    }
  }
  /*
  for( int i=0; i<64; i++ )
    cout << wall[i];
  cout << endl;
  */

  int res = wins[start[0]][start[1]][start[2]][0];
  if( res == -1 )
    cout << "You can escape." << endl;
  else if( res == -2 )
    cout << "You are eliminated." << endl;
  else
    cout << "You are trapped in the Matrix." << endl;

  //  cout << res << endl;

  return true;
}

