// Contest, Location, Date
//
// Template for KTH-NADA, Team Name
//   Team Captain, Team Member, Team Member
//
// Problem: ___

#include <cmath>
#include <cstdio>
#include <algorithm>
#include <string>
#include <map>
#include <vector>

using namespace std;
const enum {SIMPLE, FOR, WHILE} mode = NO;
#define dprintf debug && printf
bool debug = false;

void init() {
  // when reading from/writing to files
  freopen("X.in", "r", stdin);
  freopen("X.out", "w", stdout);
  // rebinding cin/cout requires include <fstream>
  cin.rdbuf((new ifstream("Y.in"))->rdbuf()); 
  cout.rdbuf((new ofstream("Y.out"))->rdbuf());
}

bool solve(int P) {
}

int main() {
  init();
  int n = mode == SIMPLE ? 1 : 1<<30;
  if (mode == FOR) scanf("%d", &n);
  for (int i = 0; i < n && solve(i); ++i);
  return 0;
}
