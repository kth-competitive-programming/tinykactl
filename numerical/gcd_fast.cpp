/* KTH ACM Contest Template Library
 *
 * Numerical/Number Theory/Fast GCD
 *
 * Credit:
 *   Euclides
 *   Based on lecture in Advanced Algorithms by Stefan Nilsson
 *   By Per Austrin
 */

template<class T>
T gcd_fast(T a, T b) {
  int twos = 0;
  if (a < 0)  a = -a;
  if (b < 0)  b = -b;
  if (!a)     a = 1;
  if (!b)     b = 1;
  while ((~a & 1) && (~b & 1)) {
    ++twos;
    a >>= 1;
    b >>= 1;
  }
  while (~a & 1)  a >>= 1;
  while (~b & 1)  b >>= 1;
  while (a != b) {
    if (a > b) {
      a -= b;
      while (~a & 1)  a >>= 1;
    } else {
      b -= a;
      while (~b & 1)  b >>= 1;
    }
  }
  return a <<= twos;
}
