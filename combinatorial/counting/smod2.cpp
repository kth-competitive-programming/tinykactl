/* KTH ACM Contest Template Library
 *
 * Numerical/Combinatorics/Stirling numbers mod 2
 *
 * beräknar stirlingtalet för n,k modulo 2
 *
 * Credit:
 *   Stirling
 *   By Per Austrin
 */


/* Running time: O(log M) */

template <class T>
int stirling_mod_2(T n, T k) {
  T i = (k - 1) / 2;
  T p = 1;
  // let  p = 2^ceil(log2(i+1))
  while (p <= i) p <<= 1;
  T j = (n - k) % p;
  while (i | j) {   // while (i != 0 || j != 0)
    if (i + j >= p) return 0;
    p >>= 1;
    if (i >= p) i -= p;
    if (j >= p) j -= p;
  }
  return 1;
}
