/* KTH ACM Contest Template Library
 *
 * Numerical/Division/divmod
 *
 * Credit:
 *   By Mattias de Zalenski
 */

template <class T>
T div(T n, T &d) {
  T r = n, q = 0, m = 1;
  while (d <= r) d *= 2, m *= 2;
  while (T(1) < m) {
    d /= 2, m /= 2;
    if (r >= d) r -= d, q += m;
  }
  d = r; // return remainder in d
  return q;
}
