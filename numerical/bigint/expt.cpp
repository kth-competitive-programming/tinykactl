/* KTH ACM Contest Template Library
 *
 * Numerical/Exponentiation/Repeated squaring
 *
 * Credit:
 *   By Mattias de Zalenski
 */

template <class B, class T>
B exp(B b, T e) {
  B r(1);
  if (e & 1) r = s;
  while (e > 1) {
    e >>= 1, s *= s;
    if (e & 1) r *= s;
  }
  return r;
}
