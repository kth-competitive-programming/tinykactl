/******************************************
 *
 * @JUDGE_ID: 16100CR 10181 C++ ""
 *
 * Problem 10181 "15-puzzle Problem"
 *
 * David Rydh, <f99-dry@nada.kth.se>
 * September 2002
 *****************************************/

#include <cstdlib>
#include <cstdio>

#include <algorithm>

using namespace std;

int g[16];
int sol[100], sold;
int best_sol[100];
bool unsol;

bool dfs( int e_pos, int old, int depth, int heur ) {
  int eh = 0;

  if( depth+heur+eh >= sold )
    return false;

  if( heur == 0 ) {
    sold = depth;
    memcpy( best_sol, sol, depth*sizeof(int) );
    return (depth<=50);
  }

  for( int i=0; i<16; i++ ) {
    int d=abs(i-e_pos);
    if( i==old )
      continue;

    if( d==1 && i/4==e_pos/4 || d==4 && i%4==e_pos%4 ) {
      int nh = heur;

      sol[depth] = i;

      nh -= abs(i/4-g[i]/4) + abs(i%4-g[i]%4);
      nh += abs(e_pos/4-g[i]/4) + abs(e_pos%4-g[i]%4);

      swap( g[e_pos], g[i] );
      if( dfs( i, e_pos, depth+1, nh ) )
	return true;
      swap( g[e_pos], g[i] );
    }
  }
  return false;
}

int main() {
  int n;

  scanf( "%d", &n );
  for( int N=0; N<n; N++ ) {
    int heur = 0;
    int e_pos = -1;

    for( int i=0; i<16; i++ ) {
      scanf( "%d", &g[i] );
      g[i]--;
      if( g[i] == -1 ) {
	g[i] = -1;
	e_pos = i;
      } else
      	heur += abs(i/4-g[i]/4) + abs(i%4-g[i]%4);
    }

    int sum = e_pos/4+1;
    for( int i=0; i<16; i++ ) {
      if( g[i] == -1 )
	continue;
      for( int j=i+1; j<16; j++ ) {
	if( g[j] == -1 )
	  continue;

	if( g[i] > g[j] )
	  sum++;
      }
    }

    if( (sum & 1) == 0 ) {
      unsol = true;

      sold = 51;

      dfs( e_pos, -1, 0, heur);
      if( sold < 51 )
	unsol = false;
    } else
      unsol = true;

    if( unsol )
      printf( "This puzzle is not solvable." );
    else {
      int s = e_pos;
      for( int i=0; i<sold; i++ ) {
	char d = 'X';

	if( best_sol[i] == s+1 )
	  d = 'R';
	else if( best_sol[i] == s-1 )
	  d = 'L';
	else if( best_sol[i] == s-4 )
	  d = 'U';
	else if( best_sol[i] == s+4 )
	  d = 'D';

	printf( "%c", d );
	s = best_sol[i];
      }
    }
    printf( "\n" );
  }
  return 0;
}
