#include <iostream>
#include <vector>
#include <bitset>
using namespace std;


#include "hopcroft.cpp"

template <class T>
vector<vector<T> > dfa(int n, int m) {
  vector<T> r(n);
  vector<vector<T> > v(m, r);
  return v;
}

template <class T>
void trans(vector<vector<T> > &dfa, int x, int a, int y) {
  dfa[x][a] |= T(1) << y;
}

int main() {
  typedef bitset<111> B;
  vector<vector<B> > d = dfa<B>(2, 4);
  trans(d, 0, 0, 0);
  trans(d, 0, 1, 1);
  trans(d, 1, 0, 2);
  trans(d, 1, 1, 3);
  trans(d, 2, 0, 0);
  trans(d, 2, 1, 1);
  trans(d, 3, 0, 2);
  trans(d, 3, 1, 2);

  B q(0xf), f(0xa);
  set<B> s = hopcroft(q, f, 2, 4, d);
  for (set<B>::iterator it = s.begin(); it != s.end(); ++it)
    cout << *it << endl;
}
