#include "Testplate.cpp"

#include "../geometry/point.cpp"
#include "../geometry/point_ops.cpp"
#include "../geometry/hull/convex_hull.cpp"

void init() { }

typedef point<double> Pt;
typedef vector<Pt> V;

// In/out:
// n x y ...(n)

bool solve(int P) {
  int n; cin >> n;
  if (!cin || n == 0) return false;
  V v;
  for (int i = 0; i < n; ++i) {
    Pt p; cin >> p.x >> p.y;
    v.push_back(p);
  }
  V::iterator e = convex_hull(v.begin(), v.end());
  cout << e - v.begin();
  for (V::iterator i = v.begin(); i != e; ++i)
    cout << ' ' << i->x << ' ' << i->y;
  cout << endl;
  return true;
}
