/******************************************
 *
 * @JUDGE_ID: 16100CR 10073 C++ ""
 *
 * Problem 10073 "Constrained Exchange Sort"
 *
 * David Rydh, <f99-dry@nada.kth.se>
 * September 2002
 *****************************************/

#include <cstdlib>
#include <cstdio>

#include <algorithm>

using namespace std;

int l[12];
int sol[1000];

bool dfs( int l_pos, int old, int depth, int max_depth, int heur ) {
  if( depth+heur > max_depth )
    return false;

  if( heur == 0 )
    return true;

  for( int i=0; i<12; i++ ) {
    int d = abs(l_pos-i);
    int k;

    if( i==old )
      continue;

    if( (d==1 && (k=3) && l_pos/3 == i/3) ||
	(d==3 && (k=6) && l_pos/6 == i/6) ||
	(d==6 && (k=12) && l_pos/12 == i/12) )
    {
      int nh = heur;
      sol[depth] = l[i];

      nh -= abs(l[i]%k/d-i%k/d);
      nh += abs(l[i]%k/d-l_pos%k/d);

      swap( l[l_pos], l[i] );
      bool f = dfs( i, l_pos, depth+1, max_depth, nh );
      swap( l[l_pos], l[i] );
      if( f )
	return true;
    }
  }
  return false;
}

int main() {
  char str[100];
  int n;

  scanf( "%d", &n );
  for( int N=0; N<n; N++ ) {
    scanf( "%s", str );

    int heur = 0;
    int l_pos = -1;

    for( int i=0; i<12; i++ ) {
      l[i] = str[i]-'A';
      if( l[i] == 11 )
	l_pos = i;
      else
	heur += abs(l[i]%3-i%3) + abs(l[i]%6/3-i%6/3) + abs(l[i]/6-i/6);
    }

    int d;
    for( d=1; ; d++ ) {
      //      printf( "%d\n", d );
      if( dfs(l_pos, -1, 0, d, heur) )
	break;
    }

    printf( "Permutation #%d\n", N+1 );
    for( int i=0; i<d; i++ )
      printf( "%c", sol[i]+'A' );
    printf( "\n\n" );
  }
  return 0;
}
