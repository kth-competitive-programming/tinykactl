/* KTH ACM Contest Template Library
 *
 * Testing/Template
 *
 * Credit:
 *   By Mattias de Zalenski
 */

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

void init();
bool solve(int P);

int main() {
  init();
  
  // while-solve
  int n = 0;
  char c;
  while (cin >> c) {
    //if (n > 0) cout << endl;
    string s; getline(cin, s);
    cout << s << endl;
    solve(n);
    n++;
  }
  
  return 0;
}

/*
void init() {
}

bool solve(int P) {
  int n; cin >> n;
  if (cin.fail() || n == 0) return false;
  return true;
}
*/
