#include "Testplate.cpp"
#include "../geometry/point.cpp"
#include "../geometry/point_ops.cpp"
#include "../geometry/incircle.cpp"

void init() { }

// In: x y (4)
// Out: "incircle" determinant "enclosing centre" x y "radius" r "err" err

typedef point<double> Pt;

bool solve(int P) {
  Pt a, b, c, p;
  cin >> a.x >> a.y >> b.x >> b.y;
  cin >> c.x >> c.y >> p.x >> p.y;
  double d = incircle(a, b, c, p);
  cout << "incircle " << d;
  bool f = enclosing_centre(a, b, c, p);
  cout << " enclosing centre ";
  if (f)
    cout << p.x << " " << p.y;
  else
    cout << "no";
  double r;
  bool g = enclosing_radius(a, b, c, r);
  cout << " radius ";
  if (g)
    cout << r;
  else
    cout << "no";
  if (f && g) {
    cout << " err";
    cout << " " << dist(a-p)-r;
    cout << " " << dist(b-p)-r;
    cout << " " << dist(c-p)-r;
  }
  cout << endl;
  return true;
}
