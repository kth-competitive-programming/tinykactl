#include "testplate.cpp"
#include "../geometry/point.cpp"
#include "../geometry/point_ops.cpp"
#include "../geometry/poly_cut.cpp"


typedef point<double> Pt;
typedef vector<Pt> V;

void init() {
}

// In:
// p0x p0y p1x p1y
// n qx qy ...(n)

// Out:
// n cx cy ...(n)

bool solve(int P) {
  Pt p0, p1;
  cin >> p0.x >> p0.y;
  cin >> p1.x >> p1.y;
  int n; cin >> n;
  if (!cin || n == 0) return false;
  V v;
  for (int i = 0; i < n; ++i) {
    Pt p; cin >> p.x >> p.y;
    v.push_back(p);
  }
  V r(v.size());
  V::iterator end = poly_cut(v.begin(), v.end(), p0, p1, r.begin());
  cout << end - r.begin();
  for (V::iterator i = r.begin(); i != end; ++i)
    cout << ' ' << i->x << ' ' << i->y;
  cout << endl;
  return true;
}
