#include "Testplate.cpp"

using namespace std;

#include "../geometry/point.cpp"
//#include "../geometry/point_ops.cpp"
#include "../geometry/inside.cpp"
#include "../geometry/winding_number.cpp"

typedef point<double> Pt;

void init() {
}

// In:
// px py
// n
// qx qy
// ...(n)

// Out:
// inside / outside (inside.cpp)
// inside / on / outside (winding_number.cpp)

bool solve(int P) {
  Pt q;
  cin >> q.x >> q.y;
  int n;
  cin >> n;
  if (cin.fail() || n == 0) return false;
  vector<Pt> v;
  for (int i = 0; i < n; ++i) {
    Pt p; cin >> p.x >> p.y;
    v.push_back(p);
  }
  if (inside(v, n, q))
    cout << "inside" << endl;
  else
    cout << "outside" << endl;

  int wind = inside_wn(v, n, q);
  switch (wind) {
  case 1: cout << "inside" << endl; break;
  case 0: cout << "on" << endl; break;
  case -1: cout << "outside" << endl; break;
  }
  return true;
}
