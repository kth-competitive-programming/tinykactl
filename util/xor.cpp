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

/* xor table:
 *             0 1 2 3 4 5 6 7 8 9 a b c d e f
 *             1 0 3 2 5 4 7 6 9 8 b a d c f e
 *             2 3 0 1 6 7 4 5 a b 8 9 e f c d
 *             3 2 1 0 7 6 5 4 b a 9 8 f e d c
 *             4 5 6 7 0 1 2 3 c d e f 8 9 a b
 *             5 4 7 6 1 0 3 2 d c f e 9 8 b a
 *             6 7 4 5 2 3 0 1 e f c d a b 8 9
 *             7 6 5 4 3 2 1 0 f e d c b a 9 8
 *             8 9 a b c d e f 0 1 2 3 4 5 6 7
 *             9 8 b a d c f e 1 0 3 2 5 4 7 6
 *             a b 8 9 e f c d 2 3 0 1 6 7 4 5
 *             b a 9 8 f e d c 3 2 1 0 7 6 5 4
 *             c d e f 8 9 a b 4 5 6 7 0 1 2 3
 *             d c f e 9 8 b a 5 4 7 6 1 0 3 2
 *             e f c d a b 8 9 6 7 4 5 2 3 0 1
 *             f e d c b a 9 8 7 6 5 4 3 2 1 0
 */

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
