/******************************************
 *
 * @JUDGE_ID: 25719RJ 10244 C++
 *
 * Problem 10244 "First Love" (Problem I in ACM Warmup 1, 2002)
 *
 * David Rydh, <f99-dry@nada.kth.se>
 * ACM Warmup competition 2 March 2002
 *****************************************/

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string.h>

//#include <list>
//#include <vector>
#include "../../tinystl/vector.cpp"
#include "../../tinystl/list.cpp"

char s[10];
int  L, numSymbols;
char answer[10000+100];

void solve();

int main() {
  while( true ) {
    s[0] = 0;

    cin >> s;
    if( s[0] == 0 )
      break;

    numSymbols = strlen(s);
    cin >> L;

    long long pathLength;

    pathLength = 1;
    for( int i=0; i<L; i++ )
      pathLength *= numSymbols;
    pathLength += L-1;

    cout << pathLength << endl;

    if( pathLength <= 10000 )
      solve();
    else
      cout << "TOO LONG TO PRINT." << endl;
  }

  return 0;
}


int numNodes;
vector< int > nodes;

list< int > find_path( int node );


list< int > find_path( int s_node ) {
  list<int> path;

  int node = s_node, next_node;

  do {
    int &s = nodes[node];

    if( s == 0 )
      break;

    path.push_back( node );

    for( int i=0; i<numSymbols; i++ ) {
      if( s & (1<<i) ) {
	next_node = (node*numSymbols)%numNodes + i;
	s ^= (1<<i);
	break;
      }
    }

    node = next_node;
  } while( true ); //while( node != s_node );

  list<int>::iterator iter = path.begin();

  while( iter != path.end() ) {
    node = *iter;

    int &s = nodes[node];

    while( s != 0 ) {
      list<int>  extra_list = find_path(node);

      path.splice( iter, extra_list, extra_list.begin(), extra_list.end() );
    }
    ++iter;
  }
  /*  
  {
  cout << endl;
  list<int>::iterator iter = path.begin();

  for( unsigned int i=0; i<path.size(); i++ ) {
    int node = *iter++;

    cout << node << endl;
  }
  cout << endl;
  }
  */

  return path;
}

void solve() {
  list<int> path;

  nodes.clear();

  numNodes = 1;

  for( int i=0; i<L-1; i++ )
    numNodes *= numSymbols;

  nodes.reserve( numNodes );

  for( int i=0; i<numNodes; i++ )
    nodes.push_back( (1<<numSymbols)-1 );

  path = find_path( 0 );

  nodes.clear();


  list<int>::iterator iter = path.begin();
  unsigned int k=0;

  for( unsigned int i=0; iter != path.end(); i++ ) {
    int node = *iter++;

    //    cout << node << endl;
    if( i==0 ) {
      int d = numNodes;

      for( int j=0; j<L-1; j++ ) {
	d/= numSymbols;
	//	cout << s[ node % numSymbols ];
	answer[k++] = s[ node % numSymbols ];
      }
    } else {
      //      cout << s[ node % numSymbols ];
      answer[k++] = s[ node % numSymbols ];
    }
  }
  //  cout << s[ *path.begin() % numSymbols ];
  answer[k++] = s[ *path.begin() % numSymbols ];
  answer[k++] = 0;

  cout << answer << endl;
}

