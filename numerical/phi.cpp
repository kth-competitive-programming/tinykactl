/* KTH ACM Contest Template Library
 *
 * Numerical/Phi Function/Divide and Conquer ;)
 *
 * Credit:
 *   Euler
 *   By Per Austrin
 *   See for example Valladolid problem #10299
 *   Dedicated to Kutta!!!
 */

template <class T>
void elim(T& n, T i) { while (!(n % i)) n /= i; }

template <class T>
T phi(T n) {
  T i, res = n;
  if (!(n % 2)) {
    elim(n, 2);
    res /= 2;
  }
  i = 3;
  while (i*i <= n) {
    if (!(n % i)) {
      elim(n, i);
      res /= i;
      res *= i-1;
    }
    i+= 2;
  }
  if (n > 1) {
    res /= n;
    res *= n-1;
  }
  return res;
}
