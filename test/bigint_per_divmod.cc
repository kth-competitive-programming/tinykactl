#include "../datastructures/numbers/bigint_per.cpp"

int main(void) {
  bigint a, b, r;
  while (cin >> a >> b) {
    cout << "divmod(" << a << ", " << b << ") = ";
    divmod(a, b, r);
    cout << "(" << a << ", " << r << ")" << endl;
  }
  return 0;
}
