/* Solves problem G from NADA Open 2002.
 */

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//#include "../graph/maxflow/max_weight_bipartite_matching.cpp"
#include "../graph/maxflow/max_weight_b_m_of_max_card.cpp"


const enum {SIMPLE, FOR, WHILE} mode = FOR;
const bool debug = false;

struct point {
  int x,y;
};

int dist( point &a, point &b ) {
  int dx = a.x-b.x, dy = a.y-b.y;
  return (int)sqrt((double)dx*dx+(double)dy*dy);
}

bool solve(int P) {
  int u, t;
  cin >> u >> t;

  vector<point> units(u), targets(t);
  vector<int> m(t);
  int tot_miss = 0;

  for( int i=0; i<u; i++ )
    cin >> units[i].x >> units[i].y;
  for( int i=0; i<t; i++ ) {
    cin >> targets[i].x >> targets[i].y >> m[i];
    tot_miss += m[i];
  }

  vector< vector<pair<int,int> > > edges(8*u);
  for( int i=0; i<u; i++ ) {
    int r=0;
    for( int j=0; j<t; j++ ) {
      int d = dist(units[i],targets[j]);
      for( int k=0; k<m[j]; k++ )
	edges[8*i].push_back( make_pair(r++,-d) );
    }
    //    while( r<8*u ) // For non-max-card-matching
    //      edges[8*i].push_back( make_pair(r++,0) );
    for( int j=1; j<8; j++ )
      edges[8*i+j] = edges[8*i];
  }

  int max_weight;
  vector< int > match_b(tot_miss);
  //  max_weight_bipartite_matching( edges, 8*u, tot_miss, match_b,
  //  				 max_weight, false );
  max_weight_b_m_of_max_card( edges, 8*u, tot_miss, match_b, max_weight );
  //vector< int > match_b(8*u);
  //  max_weight_bipartite_matching(edges, 8*u, 8*u, match_b, max_weight,true);
  cout << -max_weight << endl;
  return true;
}

int main() {
  int n = mode == SIMPLE ? 1 : 1<<30;
  if (mode == FOR) cin >> n;
  for (int i = 0; i < n && solve(i); ++i);
  return 0;
}

