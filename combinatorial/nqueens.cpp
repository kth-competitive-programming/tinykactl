/* KTH ACM Contest Template Library
 *
 * Combinatorial/Math Puzzles/The n-queens problem
 *
 * Credit:
 *   By Per Austrin
 */

void N_queens(int N, int *cols) {
  int n = N & ~1, a1 = 1, a2 = 0;
  if (n % 6 == 2) a1 = n/2-1, a2 = n/2+2;
  for (int i = 0; i < n/2; ++i)
    cols[i] = (a1 + 2*i) % n, cols[i+n/2] = (a2 + 2*i) % n;
  if (N & 1) cols[n] = n;
}
