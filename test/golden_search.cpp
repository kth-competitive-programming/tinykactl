#include <iostream>
#include <functional>
#include "../combinatorial/golden_search.cpp"

using namespace std;

const int X = 1000;
const int Y = 1000;

double sx, sy, wd;

double f(int x, int y) {
  double dx = (double) x / X - sx;
  double dy = (double) y / Y - sy;
  return -exp(-(dx * dx + dy * dy) / wd / wd);
  //return sqrt(dx * dx + dy * dy) + 1;
}

struct fx : unary_function<int, double> {
  int &last_x;
  fx(int &x) : last_x(x) { }
  double operator()(int y) const {
    double r;
    last_x = golden_search(bind2nd(ptr_fun(f), y), -X, X, r);
    return r;
  }
};

int main() {
  const int N = 10;
  int x;
  fx g(x);
  double r;
  for (int i = 0; i < N; i++) {
    sx = 3.0 * i / N - 1, sy = 2.0 * i / N - 1, wd = (double) N / i;
    int y = golden_search(g, -Y, Y, r);
    g(y);
    cout << x << "," << y << " = " << r << " = " << f(x, y) << endl;
  }
  return 0;
}
