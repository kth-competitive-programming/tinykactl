/******************************************
 *
 * @JUDGE_ID: 25719RJ 10382 C++ ""
 *
 * Problem 10382 "Watering Grass"
 *
 * David Rydh, <f99-dry@nada.kth.se>
 * UVA Regional Warmup Competition 24 oct.
 *****************************************/

#include <iostream>
#include <iomanip>
#include <cstdio>
//#include <algorithm>
//#include <vector>
#include "../../tinystl/vector.cpp"
#include "../../tinystl/stable_sort_inplace.cpp"
#include "../../tinystl/stable_sort.cpp"
#include "../../tinystl/sort.cpp"
#include "../../tinystl/pair.cpp"

using namespace std;

const int N = 0;
const bool debug = true;

void init();
bool solve(int P);

int main() {
  init();

  // while-solve
  int n = 0;
  while (solve(n))
    ++n;

  return 0;
}

void init() {
}

vector< pair<double,double> > sprinklers;

bool solve(int P) {
  int n, l, w;
  cin >> n >> l >> w;
  if (!cin ) return false;

  sprinklers.clear();
  for( int i=0; i<n; i++ ) {
    int x, r;
    double dx;

    cin >> x >> r;

    dx = sqrt((double)r*r-(double)w*w/4);
    sprinklers.push_back( make_pair(x-dx,x+dx) );
  }
  inplace_stable_sort( sprinklers.begin(), sprinklers.end() );
  //stable_sort( sprinklers.begin(), sprinklers.end() );
  //sort( sprinklers.begin(), sprinklers.end() );

  double x = 0.0;
  int i = 0;
  int nSprinklers = 0;
  while( x<l && i<n ) {
    double bestX = x;

    for( ; sprinklers[i].first <= x && i<n; i++ ) {
      if( sprinklers[i].second > bestX )
	bestX = sprinklers[i].second;
    }
    if( bestX == x )
      break;

    nSprinklers++;
    x = bestX;
  }

  if( x < l )
    nSprinklers = -1;

  cout << nSprinklers << endl;
  return true;
}
