#include <iostream>
#include <vector>
using namespace std;

#include "../graph/topo_sort.cpp"


typedef vector<int> E;
typedef vector<E> V;

bool solve(int P);

int main() {
  solve(0);

  return 0;
}

bool solve(int P) {
  int n;
  cin >> n;
  V v;
  v.resize(n);
  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    int d, k;
    cin >> d >> k;
    for (int j = 0; j < k; j++) {
      int s;
      cin >> s;
      v[s - 1].push_back(d - 1);
    }
  }
  E idx;
  idx.resize(n);
  if (!topo_sort(v, idx, n))
    cout << "Cyclic!!!" << endl;
  E o;
  o.resize(n);
  for (int i = 0; i < n; i++)
    o[idx[i]] = i;
  for (int i = 0; i < n; i++) {
    if (i > 0)
      cout << " ";
    cout << o[i] + 1;
  }
  return true;
}
