/* KTH ACM Contest Template Library
 *
 * Util/Checksum/xor table & calculator to find line numbers from line codes
 *
 * Credit:
 *   By Mattias de Zalenski
 */
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
  for (int i = 0; i < 16; i++) { // xor table
    for (int j = 0; j < 16; j++) {
      if (j > 0) cout << ' ';
      cout << hex << (i ^ j);
    }
    cout << endl;
  }
  int a, b;
  while (cin >> hex >> a >> hex >> b) // xor calculator
    cout << hex << (a ^ b) << ' ' << dec << (a ^ b) << endl;
  return 0;
}
