#include <iostream>
#include "../geometry/6_geometry_ops.cpp"

int main() {
  const int N = 16;
  for (int i = -1; i <= N; i++) {
    double a = i * 2 * pi / N;
    double c = cos(a), s = sin(a);
    if (i < 0) c = s = 0;
    point<int> p(int(c * 3), int(s * 3));
    point<int> q(int(c * N), int(s * N));
    cout << p.x << "," << p.y << " - " << q.x << "," << q.y << " :" << endl;
    cout << "  dx" << dx(p, q) << " dy" << dy(p, q) << endl;
    cout << "  d=" << dist(p, q) << " a=" << angle(p, q) << endl;
    cout << "  t=" << theta(p, q) << " af=" << angle(p, q) * 2 / pi << endl;
  }
  return 0;
}
