/* KTH ACM Contest Template Library
 *
 * Numerical/Combinatorics/Eulerian numbers
 *
 * Credit:
 *   Euler
 *   By Fredrik Niemelä
 */

template <class T>
T euler(T n, T k) {
  if (n < T(1) || n == k)
    return T(k==0 ? 1:0);
  else
    return (n-k)*euler(n-1, k-1) + (k+1)*euler(n-1, k);
}
