// ACM-ICPC World Finals, Honolulu, 23 Mar 2002
//
// Template for KTH-NADA, Ballons'R'Us, ACM 2001-2002
//   David Rydh, Mattias de Zalenski, Fredrik Niemelä
//
// Problem: 

#include <iostream>
#include <algorithm>

using namespace std;

const int N = 0;

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
  int i = 0;
  while (solve(i))
    i++;

  return 0;
}

void init() {
}

bool solve(int P) {
  if (!cin.good()) return false;
  return true;
}
