/* KTH ACM Contest Template Library
 *
 * Geometry/Closest Pair/Closest Pair
 *
 * Credit:
 *   By Per Austrin
 */

template <class It>
double closest_pair(It begin, It end) {
  sort(begin, end);
  double best = 1e99;
  for (It p = end; p-- != begin; )
    for (It l = p; l-- != begin && sqr(l->x - p->x) < best; )
      best <?= p->dist2(*l);
  return best;
}
