// Contest, Location, Date
//
// Template for KTH-NADA, Team Name
//   Team Captain, Team Member, Team Member
//
// Problem: ___

#include <iostream>
#include <algorithm>
#include <fstream>  // When reading/writing from files
//#include <string>
//#include <map>
//#include <vector>
//#include <cmath>

using namespace std;
#define doubt debug && cerr

void init() {
  // Reading from/writing to other files than stdin/stdout:
  cin.rdbuf((new ifstream("___.in"))->rdbuf());
  //cout.rdbuf((new ofstream("___.out"))->rdbuf());
}

const enum {SIMPLE, FOR, WHILE} mode = NO;
const bool debug = true;

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
