// ACM-Contest, Location, Date
//
// Template for KTH-NADA, Ballons'R'Us, ACM 2001-2002
//   David Rydh, Mattias de Zalenski, Fredrik Niemelä
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
const bool deBug = false;

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
  if (deBug) cerr << n << endl;
  return true;
}
