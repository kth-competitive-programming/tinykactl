/* KTH ACM Contest Template Library
 *
 * Numerical/Number Theory/Chinese Remainder Theorem
 *
 * Credit:
 *   By Mattias de Zalenski
 *   Non-relatively prime case by Per Austrin
 */

#include "euclid.cpp"

template <class Z> inline Z chinese(Z a, Z m, Z b, Z n) {
  Z x, y;  euclid(m, n, x, y);
  return (a * n * (y < 0 ? y + m : y) + 
	  b * m * (x < 0 ? x + n : x)) % (m*n);
}

template <class Z> inline Z chinese_common(Z a, Z m, Z b, Z n) {
  Z d = gcd(m, n);
  if (((b -= a) %= n) < 0) b += n;
  if (b % d) return -1; // No solution
  return d*chinese(0, m/d, b/d, n/d) + a;
}
