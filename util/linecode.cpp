/* KTH ACM Contest Template Library
 *
 * Utility/Code Library Document/Line code
 *
 * Credit:
 *   Hamming (inspired by the Hamming error correcting code)
 *   Checksum from util/adler.cpp
 *   By Mattias de Zalenski
 */
// Failure probabilities:
//(of not detecting a single correct erroneous line number)
// Error on 1 line: 1/2^16 < 16ppm
//         2 lines: (2/4)^16 < 16ppm
//         3 lines: (5/8)^16 < .06%
//         4 lines: (12/16)^16 < 1.01%
//         5 lines: (27/32)^16 < 6.6%
//         6 lines: (58/64)^16 < 21%

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
#include <iostream>
#include <iomanip>
#if __GNUC__ >= 3
#include <sstream>
#else
#include <strstream>
#include <string>
struct istringstream : istrstream {
  istringstream( const string &s ) : istrstream( s.c_str(), s.length() ) {}
};
#endif

// copy util/adler.cpp to get most of the adler function!!!
using namespace std;
int adler(istream &in) {  // "Adler-32 by Mark Adler" -> 411f06c9
  unsigned long crcbase = 65521, s1 = 1, s2 = 0; unsigned char c;
  while (in >> c) s1 = (s1 + c) % crcbase, s2 = (s2 + s1) % crcbase;
  return s2 << 16 | s1;
}

int par[32];
int main() {
  string s; int lines = 0; // for every line's checksum,
  while (getline(cin, s)) { lines++; // for every bit of the sum,
    istringstream in(s); int sum = adler(in); // construct a parity
    for (int i = 0; i < 32; i++) if (sum & 1 << i) par[i] ^= lines;
  }
  cout << lines << " lines" << hex;
  for (int i = 0; i < 32; i++) if (!(i & 8)) cout << ',' << setw(2) << par[i];
  cout << endl;
  return 0; // when two numers differ, xor them to get a line number
}
