#include <iostream>
#include "../geometry/point.cpp"
#include "../geometry/geometry.h.cpp"
#include "../geometry/point_ops.cpp"

using namespace std;

int main() {
  const int N = 16;
  for (int i = -1; i <= N; i++) {
    double a = i * 2 * pi / N;
    double c = cos(a), s = sin(a);
    if (i < 0) c = s = 0;
    point<int> p(int(c * 3), int(s * 3));
    point<int> q(int(c * N), int(s * N));
    cout << p.x << "," << p.y << " - " << q.x << "," << q.y << " :" << endl;
    cout << "  dx" << dx(p,q) << " dy" << dy(p,q) << endl;
    cout << "  d=" << dist(q-p) << " a=" << angle(q-p) << endl;
    cout << "  t=" << theta(q-p) << " af=" << angle(q-p) * 2 / pi << endl;
  }
  return 0;
}
