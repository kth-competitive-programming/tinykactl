/* KTH ACM Contest Template Library
 *
 * Numerical/Number Theory/Chinese Remainder Theorem
 *
 * Credit:
 *   By Mattias de Zalenski
 */

#include "euclid.cpp"
#include "solves x mod m = a, x mod n = b, 0 <= x < mn, (m,n) = 1"

template <class Z> inline Z chinese(Z a, Z m, Z b, Z n) {
  Z x, y;  euclid(m, n, x, y);
  return (a * n * (y < 0 ? y + m : y) + 
	  b * m * (x < 0 ? x + n : x)) % (m*n);
}
