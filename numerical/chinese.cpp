/* KTH ACM Contest Template Library
 *
 * Numerical/Number Theory/Chinese Remainder Theorem
 *
 * Credit:
 *   By Mattias de Zalenski
 */

// x=a(mod m), x=b(mod n), find x (mod nm), assuming (n,m)=1
template <class T>
T chinese(T a, T m, T b, T n) {
  T x, y;
  poseuclid(m, n, x, y);
  big a1 = a * y * n;
  big b1 = b * x * m;
  big r = a1 > b1 ? a1 - b1 : b1 - a1;
  if (r % m != a) r = m * n - r % (m * n);
  return r;
}

big chinese(big a, big m, big b, big n, big c, big o) {
  return chinese(a, m, chinese(b, n, c, o), n * o);
}
