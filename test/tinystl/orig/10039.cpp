/******************************************
 *
 * @JUDGE_ID: 25719RJ 10039 C++ ""
 *
 * Problem 10039 "Railroads"
 *
 * David Rydh, <f99-dry@nada.kth.se>
 * October 2002
 *
 * Popup 02, Karmosin, 2002-10-07
 *****************************************/

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
//#include <set>
#include <map>
//#include <sstream>
//#include <cmath>

#include <set>

using namespace std;

template <class E, class M, class P, class D>
void dijkstra_prim(E &edges, M &min, P &path, int start, int n, D distfun,
		   bool mst = false) {
  typedef typename M::value_type T;
  //  T inf(1<<29);

  set< pair<T, int> > q; // use a set as a modifiable priority queue

  for (int i = 0; i < n; i++) {
    //    min[i] = inf;
    path[i] = -1;
  }
  //  min[start] = T();

  q.insert(make_pair(min[start], start));
  while (!q.empty()) {
    int node = q.begin()->second;
    q.erase(q.begin());
    if (mst) min[node] = T(); // only difference between dijkstra and prim
    typedef typename E::value_type L;
    typedef typename L::const_iterator L_iter;

    const L &l = edges[node];
    for (L_iter it = l.begin(); it != l.end(); ++it) {
      pair<int, T> p = distfun(*it, min[node]);
      int dest = p.first; T dist = min[node] + p.second;
      if (dist < min[dest]) {
	q.erase(make_pair(min[dest], dest)); //
	min[dest] = dist; // update dest in the queue
	q.insert(make_pair(min[dest], dest)); //
	path[dest] = node;
      }
    }
  }
}

template<class T, T inf>
pair<int, T> step_dist(const pair<int, pair<int,int> > &edge, T t) {
  return make_pair(edge.first, edge.second.first < t ? inf:
		   (edge.second.first-t + edge.second.second));
}



const int N = 0;
const bool debug = true;

void init();
bool solve(int P);

int m_to_t( int t ) {
  return t/60*100 + t%60;
}

int t_to_m( int t ) {
  t %= 2400;
  return t%100 + (t/100*60);
}

int main() {
  init();

  // for-solve
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i)
    solve(i);

  return 0;
}

void init() {
}

map< string, int > cities;
vector< vector<pair<int,pair<int,int> > > > edges;

int midnight = 24*60;

bool solve(int P) {
  string s;
  int C, T;

  cities.clear();
  edges.clear();

  cin >> C;
  getline( cin, s );
  for( int i=1; i<=C; i++ ) {
    getline( cin, s );
    cities[s] = i;
  }

  edges.resize( C+1 );

  cin >> T;
  for( int i=0; i<T; i++ ) {
    int n;
    int lastT, lastCity=-1;

    cin >> n;
    getline( cin, s );
    for( int i=0; i<n; i++ ) {
      int t, j;
      cin >> t;
      t = t_to_m( t );
      getline( cin, s );

      for( j=0; j<(int)s.length() && s[j]==' '; j++ )
	;
      s = s.substr( j );
      j = cities[s];
      if( j==0 ) // Check for erroneous input
	t /= j;
      //      cout << m_to_t(midnight-t) << endl;

      if( t==0 )
	j /= t;

      if( lastCity >= 0 && t>=lastT )
	edges[j].push_back( make_pair(lastCity,
				      make_pair(midnight-t,t-lastT)) );

      lastT = t;
      lastCity = j;
    }
  }

  string source_s, dest_s;
  int earliest, source, dest;
  cin >> earliest;
  earliest = t_to_m( earliest );

  getline( cin, s );
  getline( cin, source_s );
  source = cities[source_s];
  getline( cin, dest_s );
  dest = cities[dest_s];

  T /= source; // Check for erroneous input
  T /= dest;   //

  int bestarr = -1;
  int bestdep = -1;

  for( int i=0; i<(int)edges[dest].size(); i++ ) {
    vector<int> mins(C+1, 1<<29), path(C+1);
    mins[dest] = edges[dest][i].second.first;

    if( mins[dest] <= 0 ) // After midnight
      continue;

    dijkstra_prim( edges, mins, path, dest, C+1, step_dist<int, 1<<29> );

    //    printf( "%d %d\n", m_to_t(midnight-mins[source]),
    //    	    m_to_t(midnight-mins[dest]) );

    if( mins[source] <= midnight-earliest ) {
      if( mins[dest] > bestarr ) {
	bestarr = mins[dest];
	bestdep = mins[source];
      } else if( mins[dest] == bestarr )
	bestdep = min(bestdep, mins[source]);
    }
  }

  printf( "Scenario %d\n", P+1 );

  if( bestarr < 0 )
    printf( "No connection\n" );
  else {
    printf( "Departure %04d %s\n", m_to_t(midnight-bestdep),source_s.c_str() );
    printf( "Arrival   %04d %s\n", m_to_t(midnight-bestarr),dest_s.c_str() );
  }
  printf( "\n" );

  return true;
}
