/* KTH ACM Contest Template Library
 *
 * Numerical problems/Number Theory/Euclid's Algorithm
 *
 * Credit:
 *   Euclid
 *   Based on [Intro to Algorithms 8th ed, p. 810]
 *   Variation of numerical/gcd.cpp
 *   By David Rydh
 */

template <class Z> Z euclid(Z a, Z b, Z &x, Z &y) {
  if (b) {  Z d = euclid(b, a % b, y, x);
            return y -= a/b * x, d;  }
  return x = 1, y = 0, a;
}
