// Contest, Location, Date
//
// NWERC02 Template for KTH-NADA, Team Name
//   Team Captain, Team Member, Team Member
//
// Problem: ___

#include <iostream.h>
#include <fstream.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <math.h>
//#include <ctype.h>

#define doubt if (debug) cerr

void init() {
  cin.rdbuf((new ifstream("!!!.in"))->rdbuf());
}

const enum {SIMPLE, FOR, WHILE} mode = NO;
const bool debug = false;

bool solve(int P) {
  int n; cin >> n;
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
