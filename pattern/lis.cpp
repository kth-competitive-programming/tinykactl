/* KTH ACM Contest Template Library
 *
 * Pattern Matching/Sequences/Longest Increasing Subsequence
 *
 * Credit:
 *   By Per Austrin
 */

#include <functional>

/* It needs to be Random Access Iterator */
template <class It>
It long_inc_seq(It begin, It end) {
  return long_inc_seq(begin, end, less<iterator_traits<It>::value_type>());
}

/* It needs to be Random Access Iterator */
template <class It, class Cmp>
It long_inc_seq(It begin, It end, Cmp cmp) {
  int n = end - begin, max[n], forw[n], best = n-1;
  for (int i = n-1; i >= 0; --i) {
    max[i] = 1;
    forw[i] = -1;
    for (int j = i+1; j < n; ++j)
      // Swap i and j in the call to cmp and negate it, if nondecreasing
      // sequences are wanted rather than just increasing.
      if (max[j] + 1 > max[i] && cmp(*(begin + i), *(begin + j)))
	forw[i] = j, max[i] = max[j] + 1;
    if (max[i] > max[best]) best = i;
  }
  It pos = begin;
  while (best != -1) {
    swap(*pos++, *(begin + best));
    best = forw[best];
  }
  return pos;
}
