/* KTH ACM Contest Template Library
 *
 * Numerical/Combinatorics/Multinomial coefficients
 *
 * Credit:
 *   By Mattias de Zalenski
 *   With great assistance from (in order of appearence)
 *     Fredrik Niemelä
 *     Per Austrin
 *   Spawned by implementation by Max Bennedich
 */

template <class T, class V>
T multinomial(int n, V &k) {
  T c = 1;
  int m = k[0];
  for (int i = 1; i < n; ++i)
    for (int j = 1; j <= k[i]; ++j)
      c *= ++m, c /= j;

  return c;
}
