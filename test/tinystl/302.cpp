/******************************************
 *
 * @JUDGE_ID: 25719RJ 302 C++
 *
 * Problem 302 "John's trip"
 *
 * David Rydh, <f99-dry@nada.kth.se>
 * December 2001
 *****************************************/

#include <cstdlib>
#include <iostream>

//#include <map>
//#include <vector>
//#include <list>

#include "../../tinystl/associative.cpp"

#include "../../tinystl/vector.cpp"
#include "../../tinystl/list.cpp"
#include "../../tinystl/map.cpp"
#include "../../tinystl/base.cpp"

const int N = 50; // 44

multimap< int, int > adj[N];
typedef pair<int,int> path_type;

void find_path( int start, list< path_type > parent_path,
		list<path_type>::iterator ins_pos )
{
  list< path_type > path;

  for( int node=start; ; ) {
    map<int,int>::iterator   iter = --adj[node].end();
    pair<int,int>            street = *iter;

    adj[node].erase( iter );
    node = street.second;
    adj[node].erase( street.first );

    path.push_back( street );

    /*    if( node == start )
	  break;*/
    if( adj[node].size() == 0 )
      break;
  }

  list<path_type>::iterator prevIter, iter;

  for( prevIter=path.end(), iter=--path.end(); prevIter!=path.begin(); iter-- )
  {
    int node = (*iter).second;

    //    while( adj[node].size() > 0 )
    if( adj[node].size() > 0 )
      find_path( node, path, prevIter );

    prevIter = iter;
  }

  parent_path.splice( ins_pos, path );
}


int main() {
  int start;

  while( true ) {
    int k;

    // clear map
    for( int i=0; i<N; i++ )
      adj[i].clear();

    for( k=0; k<2000; k++ ) {
      int x,y,z;

      cin >> x >> y;

      if( x==0 && y==0 )
	break;

      cin >> z;
      adj[x].insert( make_pair(-z,y) );
      adj[y].insert( make_pair(-z,x) );

      if( k==0 )
	start = min(x,y);
    }

    if( k==0 )
      break;

    bool possible = true;

    for( int i=0; i<N; i++ ) {
      if( adj[i].size() & 1 )
	possible = false;
    }

    if( possible ) {
      list<path_type>           path;
      list<path_type>::iterator iter;
      bool                      first = true;

      if( adj[start].size() > 0 )
	find_path( start, path, path.end() );

      for( iter = path.begin(); iter!=path.end(); iter++ ) {
	if( !first )
	  cout << " ";
	else
	  first = false;
	cout << -(*iter).first;
      }
      cout << endl;
    } else
      cout << "Round trip does not exist." << endl;
    cout << endl;
  }

  return 0;
}
