#include <iostream>
using namespace std;
int main() {  // "Adler-32 by Mark Adler" -> 1092552393
  unsigned long crcbase = 65521, s1 = 1, s2 = 0; unsigned char c;
  while (cin >> c) s1 = (s1 + c) % crcbase, s2 = (s2 + s1) % crcbase;
  cout << (s2 << 16 | s1) << endl; return 0;
}
