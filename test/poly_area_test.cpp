#include <iostream>

const int N = 1000;

#include "../geometry/4_polyarea.cpp"

int main() {
  point<int> a[4];
  point<float> b[5];
  point<double> c[N];
  a[0] = point<int>(4, 4);
  a[1] = point<int>(8, 4);
  a[2] = point<int>(8, 8);
  a[3] = point<int>(4, 8);

  for (int i = 0; i < 4; i++)
    cout << a[i].x << endl;

  cout << "a: 16=" << poly_area(a, 4) << endl;

  b[0] = point<float>(0, 5);
  b[1] = point<float>(4, 7);
  b[2] = point<float>(4, 2);
  b[3] = point<float>(7, 5);
  b[4] = point<float>(3, 11);

  cout << "b: " << poly_area(b, 5) << endl;

  for (int i = 0; i < N; i++)
    c[i] = point<double>(cos(i * 2 * pi / N), sin(i * 2 * pi / N));
  
  cout << "c: " << poly_area(c, N) << endl;

  return 0;
}
