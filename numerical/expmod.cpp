/* KTH ACM Contest Template Library
 *
 * Numerical/Exponentiation/Repeated squaring, with modulo
 *
 * Credit:
 *   By Mattias de Zalenski
 */

template <class B, class E>
B exp(B b, E e, B mod) {
  B r = 1; b %= mod;
  if (e & 1) r = b;
  while (e > 1) {
    e >>= 1, b *= b, b %= mod; // or mulmod!
    if (e & 1) r *= b, r %= mod; // or mulmod!
  }
  return r;
}
