/* KTH ACM Contest Template Library
 *
 * Numerical/Combinatorics/Second-order Eulerian numbers
 *
 * Credit:
 *   Euler
 *   By Fredrik Niemelä
 */

template <class T>
T euler2(T n, T k) {
  if (n < T(1) || n == k)
    return T(k==0 ? 1:0);
  else
    return (2n-1-k)*euler2(n-1, k-1) + (k+1)*euler2(n-1, k);
}
