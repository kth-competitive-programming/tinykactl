#include <iostream>
#include "../geometry/3_convex_hull.cpp"
#include "../geometry/hull/3_line_hull_intersect.cpp"

typedef point<double> Pt;

const int N = 10;

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
    int r = convex_hull(a, idx, N + 1);
    indexed<Pt> b(a, idx);
    Pt p1(-1, 0.7), p2(0, 0.7);
    Pt p3(-1, 1.5), p4(1, 1);
    int i1, i2, i3, i4;
    bool isect1 = line_hull_intersect(b, r, p1, p2, i1, i2);
    bool isect2 = line_hull_intersect(b, r, p3, p4, i3, i4);
    cout << isect1 << " " << i1 << "-" << i2 << ", " <<
      isect2 << " " << i3 << "-" << i4 << endl;
  }
  return 0;
}
