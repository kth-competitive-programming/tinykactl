/* KTH ACM Contest Template Library
 *
 * Numerical/Combinatorics/Binomial coefficients
 *
 * Credit:
 *   By Fredrik Niemelä
 */
#include <algorithm>

template <class T>
T choose(int n, int k) {
  k = max(k, n-k);

  T c = 1;
  for (int i = 1; i <= n-k; ++i)
    c *= k+i, c /= i;

  return c;
}

