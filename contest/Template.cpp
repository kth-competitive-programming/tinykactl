// Contest, Location, Date
//
// Template for KTH-NADA, Team Name
//   Team Captain, Team Member, Team Member
//
// Problem: %P

#include <iostream>
#include <algorithm>
//#include <string>
//#include <map>
//#include <vector>
//#include <cmath>


typedef enum {SIMPLE, FOR, WHILE} solve_mode;
#define doubt if (debug) cerr

void init() {  }

const solve_mode mode = SIMPLE;
const bool debug = false;

bool solve(int P) {
  int n;
  if (!(cin >> n)  || n == 0) return false;
  return true;
}

int main() {
  int n = 1<<30;
  init();
  if (mode == FOR)
    cin >> n;
  if (mode == SIMPLE)
    solve(0);
  else
    for (int i = 0; i < n && solve(i); ++i);
  return 0;
}
