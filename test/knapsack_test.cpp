/* Solves problem F from NADA Open 2002.
 */


#include <iostream>
#include <vector>
#include "../combinatorial/knapsack.cpp"

#define doubt if (debug) cerr

const enum {SIMPLE, FOR, WHILE} mode = FOR;
const bool debug = false;

bool solve(int P) {
  int n, C;
  cin >> n >> C;
  if (!cin /* || stopcond*/) return false;
  vector<int> val(n), cost(n);
  for (int i = 0; i < n; ++i)
    cin >> val[i];
  for (int i = 0; i < n; ++i)
    cin >> cost[i];

  int res = knapsack<int>(n, C, cost, val, 90000);
  cout << res << endl;
  return true;
}

int main() {
  int n = mode == SIMPLE ? 1 : 1<<30;
  if (mode == FOR) cin >> n;
  for (int i = 0; i < n && solve(i); ++i);
  return 0;
}

