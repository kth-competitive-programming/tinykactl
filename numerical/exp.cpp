/* KTH ACM Contest Template Library
 *
 * Numerical/Exponentiation/Repeated squaring
 *
 * Credit:
 *   By Mattias de Zalenski
 */

template <class B, class E>
B exp(B b, E e) {
  B r = 1;
  if (e & 1) r = b;
  while (e > 1) {
    e >>= 1, b *= b;
    if (e & 1) r *= b;
  }
  return r;
}
