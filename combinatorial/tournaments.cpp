/* KTH ACM Contest Template Library
 *
 * Combinatorial/Math Puzzles/Tournament Scheduling
 *
 * Credit:
 *   By Per Austrin
 */

template <class M>
int tournaments(int n, M& sched) {
  int N = n + (n&1);
  for (int i = 0; i < N-1; ++i)
    for (int j = 0; j < N-1; ++j)
      if ((sched[i][j] = (N+i-j-1) % (N-1)) == j)
	sched[i][j] = n == N ? (sched[i][n-1] = j), n-1 : -1;
  return N-1;
}
