/******************************************
 *
 * @JUDGE_ID: 25719RJ 195 C++
 *
 * Problem 195 "Anagram"
 *
 * David Rydh, <f99-dry@nada.kth.se>
 * May 2002
 *
 * From ACM Warmup 3 "The Contest" KTH NADA, 2002-03-15
 *****************************************/

#include <cstdlib>
#include <iostream>

//#include <algorithm>
//#include <string>
//#include <vector>
#include "../../tinystl/string.cpp"
#include "../../tinystl/vector.cpp"
#include "../../tinystl/permutation.cpp"
#include "../../tinystl/sort.cpp"

using namespace std;

const int N = 0;


bool solve(int P);

int main() {
  // for-solve
  int n;
  cin >> n;
  string s;
  getline(cin, s);
  for (int i = 0; i < n; i++)
    solve(i);

  return 0;
}

bool solve(int P) {
  string s;
  int l;
  vector<int> t;

  getline(cin, s);
  if (cin.bad()) return false;

  l = s.length();
  t.resize(l);

  for( int i=0; i<l; i++ ) {
    if( s[i]>='A' && s[i]<='Z' )
      t[i] = (s[i]-'A')*2;
    else
      t[i] = (s[i]-'a')*2+1;
  }
  sort(t.begin(), t.end());

  do {
    for( int i=0; i<l; i++ )
      cout << (char)('A'+(t[i]&1)*('a'-'A')+(t[i]>>1));
    cout << endl;
  } while (next_permutation(t.begin(), t.end()));
  return true;
}
