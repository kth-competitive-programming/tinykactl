/******************************************
 *
 * @JUDGE_ID: 25719RJ 122 C++ ""
 *
 * Problem 122 "Trees on the level"
 *
 * David Rydh, <f99-dry@nada.kth.se>
 * September 2002
 *****************************************/

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

struct my_pair : pair<string, int> {
  my_pair( const string &s, const int &v ) : pair<string,int>(s,v) {} 
  bool operator<( const my_pair &a ) {
    int d = first.length()-a.first.length();
    
    return d==0 ? (first<a.first):(d<0);
  }
};

vector< my_pair > nodes;
map< string, int > cnt;

int main() {
  char s[1000];

  while( true ) {
    nodes.clear();
    cnt.clear();

    int v, nNodes=0;
    while( scanf(" (%d,%s", &v, s) == 2 ) {
      s[strlen(s)-1] = 0;
      nodes.push_back( my_pair(s, v) );
      cnt[s]++;
      nNodes++;
    }
    scanf( ")" );

    if( nNodes == 0 )
      break;
    sort( nodes.begin(), nodes.end() );

    bool complete = true;
    for( int i=0; i<nNodes; i++ ) {
      if( cnt[nodes[i].first] > 1 ) {
	complete = false;
	break;
      } else if( nodes[i].first.length() > 0 ) {
	string anc = nodes[i].first.substr(0,nodes[i].first.length()-1);
	if( cnt[anc] != 1 ) {
	  complete = false;
	  break;
	}
      }
    }

    if( complete ) {
      for( int i=0; i<nNodes; i++ )
	printf( "%d%c", nodes[i].second, i<nNodes-1?' ':'\n' );
    } else
      printf( "not complete\n" );
  }
  return 0;
}
