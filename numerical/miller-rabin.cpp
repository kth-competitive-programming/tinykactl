/* KTH ACM Contest Template Library
 *
 * Numerical/Number Theory/Miller-Rabin
 *
 * Credit:
 *   G. Miller & M.O. Rabin
 *   By Per Austrin
 */

#include "expmod.h"
#include "mulmod.h"

template <class T> bool miller_rabin(T n, int tries = 15) {
  T n1 = n - 1, m = 1;
  int j, k = 0;
  if (n <= 3) return true;
  while (!(n1 & (m << k))) ++k;
  m = n1 >> k;
  for (int i = 0; i < tries; ++i) {
    T a = rand() % n1, b = expmod(++a, m, n);
    if (b == T(1)) continue;
    for (j = 0; j < k && b != n1; ++j)
      b = mulmod(b, b, n);
    if (j == k) return false;
  }
  return true;
}

