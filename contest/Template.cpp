// Contest, Location, Date
//
// Template for KTH-NADA, Team Name
//   Team Captain, Team Member, Team Member
//
// Problem: ___

#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
//#include <string>
//#include <map>
//#include <vector>

using namespace std;
#define doubt debug && cout

void init() {
}

const enum {SIMPLE, FOR, WHILE} mode = NO;
bool debug = true;

bool solve(int P) {
  int n;
  cin >> n;
  if (!cin /* || stopcond*/) return false;
  return true;
}

int main() {
  init();
  int n = mode == SIMPLE ? 1 : 1<<30;
  if (mode == FOR) cin >> n;
  for (int i = 0; i < n && solve(i); ++i);
  return 0;
}
