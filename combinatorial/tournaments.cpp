/* KTH ACM Contest Template Library
 *
 * Combinatorial/Math Puzzles/Tournament Scheduling
 *
 * Credit:
 *   By Per Austrin
 */

template <class M> int tournaments(int n, M& sched) {
  int d = n-1 + (n & 1);
  for (int i = 0; i < d; ++i)
    for (int j = 0; j < d; ++j)
      if ((sched[i][j] = (d+i-j) % d) == j)
	sched[i][j] = (n & 1) ? -1 : (sched[i][d] = j), d;
  return d;
}
