#include <iostream>
#include <iomanip>
#include <cstdio>

using namespace std;

#include "../geometry/point.cpp"
#include "../geometry/geometry.h.cpp"
#include "../geometry/hull/convex_hull_idx.cpp"
#include "../geometry/hull/hull_diameter.cpp"

typedef point<double> Pt;

int main() {
  const int N = 200;
  const int M = 17;
  Pt a[N + 1];
  int idx[N + 1];
  int i;
  for (i = 0; i < N; i++)
    a[i] = Pt(cos(i * 2 * pi / N), sin(i * 2 * pi / N));

  for (i = 0; i < M; i++) {
    a[N] = Pt(cos(i * 2 * pi / M) * 2, sin(i * 2 * pi / M) * 2);
    int i1, i2;
    int r = convex_hull(a, idx, N + 1);
    indexed<Pt*, int*> b(a+0, idx+0);
    double d = hull_diameter2(b, r, i1, i2);
    printf( "r=%d %d: dist2(a[%d],a[%d])=%g\n", r, i, idx[i1], idx[i2], d );
  }
  return 0;
}
