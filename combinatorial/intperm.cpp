/* KTH ACM Contest Template Library
 *
 * Numerical/Combinatorics/Bijection between integers and permutations
 *
 * Credit:
 *   By Per Austrin
 */

#include <algorithm>  // Needed for nth_element and swap.

/* May well be replaced by a factorial lookup table, with the
 * appropriate changes in perm_to_int and int_to_perm. */
template <class Z> 
Z factorial(int n) {
  Z r = Z(1);
  for (int i = n; i >= 2; --i) r *= i;
  return r;
}

/* Z is the number class, typically int or long long
 * It does not have to be RandomAccess!!
 * Complexity: O(n^2), where n is the number of elements in the permutation. */
template <class Z, class It>
void perm_to_int(Z& val, It begin, It end) {
  int x = 0, n = 0;
  for (It i = begin; i != end; ++i, ++n)
    if (*i < *begin) ++x;
  if (n > 2) perm_to_int<Z>(val, ++begin, end);
  else val = 0;
  val += factorial<Z>(n-1)*x;
}

/* Z is the number class, typically int or long long
 * It must be RandomAccess, but the range [begin, end) does not have
 * to be sorted. */
template <class Z, class It>
void int_to_perm(Z val, It begin, It end) {
  Z fac = factorial<Z>(end - begin - 1);
  // Note that the result of this division will fit in an integer!
  int x = val / fac;
  nth_element(begin, begin + x, end);
  swap(*begin, *(begin + x));
  if (end - begin > 2) int_to_perm(val % fac, ++begin, end);
}
