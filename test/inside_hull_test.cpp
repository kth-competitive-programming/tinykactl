#include <iostream>
#include "../geometry/hull/1_inside_hull.cpp"

typedef point<double> Pt;

const int N = 400;

Pt a[N];

int main() {
  a[0] = Pt(-1, 3);
  a[1] = Pt(3, -1);
  a[2] = Pt(3, 3);
  for (int i = 0; i < 5; i++)
    cout << i << "," << i << ": " << inside_hull(a, 3, Pt(i, i)) << endl;
  for (int i = 3; i < N; i++)
    a[i] = Pt(cos(i * pi / N) * 2 + 1, sin(i * pi / N) + 3);
  a[N / 2] = Pt(1, 4);
  for (int i = -1; i < 10; i++) {
    Pt p = Pt(3 - i / 2.5, -1 + i);
    cout << p.x << "," << p.y << ": " << inside_hull(a, N, p) << endl;
  }
  return 0;
}
