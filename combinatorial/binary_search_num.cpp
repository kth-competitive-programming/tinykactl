/* KTH ACM Contest Template Library
 *
 * Combinatorial/Binary Search Num
 *
 * Credit:
 *   By Mattias de Zalenski, David Rydh
 */

// This is only indented for double and may not work with ints.
// P is a predicate which should be equal to (a>m) for some m in [a,b],
// i.e. a step-function, and binary_search_num returns this m.
template <class T, class P>
T binary_search_num(T a, T b, P p, T eps = T(1e-13)) {
  T m;

  while (b-a > eps) {
    m = (a + b) / 2;
    if (p(m)) {
      if (b==m) break;
      b = m;
    } else {
      if (a==m) break;
      a = m;
    }
  }
  return m;
}
