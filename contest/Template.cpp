// Contest, Location, Date
//
// Template for KTH-NADA, Team Name
//   Team Captain, Team Member, Team Member
//
// Problem: _

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
const bool debug = true;

void init();
bool solve(int P);

int main() {
  init();
  
  // simple-solve
  solve(0);
  
  // for-solve
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
    solve(i);
  
  // while-solve
  int n = 0;
  while (solve(n))
    n++;
  
  return 0;
}

void init() {
}

bool solve(int P) {
  int n;
  cin >> n;
  if (cin.fail() || n == 0) return false;
  // remember: if (debug) cerr << ...; !!
  return true;
}
