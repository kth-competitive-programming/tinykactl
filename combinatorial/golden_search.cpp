/* KTH ACM Contest Template Library
 *
 * Combinatorial/Golden ratio search
 *
 * Credit:
 *   By Mattias de Zalenski, David Rydh
 */

#include <cmath>

int golden_ratio(int d) {
  const double golden_ratio = 1 - (sqrt(5) - 1) / 2;
  return (int) floor(golden_ratio * d);
}

template <class F, class T>
int golden_search(const F &f, int l, int r, T &v) {
  int d = golden_ratio(r-l);
  int m1 = l + d, m2 = r - d;
  T f1 = f(m1), f2 = f(m2);
  while (d > 0) {
    if (m1 == m2)
      if (m1 > l + 1)
	f1 = f(--m1);
      else
	f2 = f(++m2);
    if (f1 < f2)
      r = m2, m2 = m1, f2 = f1, d = golden_ratio(r-l), m1 = l + d, f1 = f(m1);
    else
      l = m1, m1 = m2, f1 = f2, d = golden_ratio(r-l), m2 = r - d, f2 = f(m2);
  }
  if (m2 - m1 > 1) {
    T f3 = f(m1 + 1);
    if (f3 < f1) f1 = f3, m1++;
  }
  return f1 < f2 ? (v = f1, m1) : (v = f2, m2);
}
