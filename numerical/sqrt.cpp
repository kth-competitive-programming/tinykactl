/* KTH ACM Contest Template Library
 *
 * Numerical/BigInt/bigint_full
 *
 * Credit:
 *   By David Rydh
 */

// Newton-Raphson's method. y' = y-(y^2-x)/(2y) = (y+x/y)/2.
// ans should contain a guess >= actual answer, e.g. x0/2.
template< class T >
void sqrt(const T &x0, T &ans) {
  T x = x0;
  if (x0 > 1) {
    while(true) {
      T d = x0; d /= ans; d += ans; d /= 2;
      if(!(d < ans)) break;
      ans = d;
    }
  }
}
