/* KTH ACM Contest Template Library
 *
 * Numerical/Combinatorics/Stirling numbers of the first kind
 *
 * Credit:
 *   Stirling
 *   By Fredrik Niemelä
 */

template <class T>
T stirling1(T n, T k) {
  if (n < T(1) || n == k)
    return T(n==k ? 1:0);
  else
    return stirling1(n-1, k-1) + (n-1)*stirling1(n-1, k);
}
