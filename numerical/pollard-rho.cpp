/* KTH ACM Contest Template Library
 *
 * Numerical/Number Theory/Pollard Rho Factoring Algorithm
 *
 * Credit:
 *   Pollard.
 *   By Per Austrin
 */

#include "gcd.h"
#include "mulmod.h"

/* calculates x^2+1 (mod N) */
template <class T>
inline T pollard_step(T x, T N) {
  T r = mulmod(x, x, N);
  if (++r == N) r = 0;
  return r;
}

/*
 * Returns a non-trivial factor of N, if any.  (Note that if N is
 * prime, pollard_rho never returns, so this should be checked first.)
 */
template <class T>
inline T pollard_rho(T N, int maxiter = 500) {
  /* replace rand by random number generator of choice. */
  T x = rand() % N, y = x;
  T d;
  int iter = 0;

  /* Check factor 2 */
  if (!(N & 1)) return 2;

  /* Check for a small factor. While this _shouldn't_ be necessary,
   * for some weird reason there is trouble factoring the number "25"
   * otherwise. Also, this gives a _considerable_ speed increase.
   */
  for (d = 3; d <= 9997; d += 2)
    if (!(N % d))
      return d;

  d = 1;
  while (d == 1) {
    /* Reseed if too many iterations passed. This shouldn't be
     * necessary either, but seemed to increase stability for
     * Valladolid 10290 ("sum{i++} = N")
     */
    if (iter++ == maxiter) {
      /* replace rand by random number generator of choice. */
      x = y = rand() % N;
      iter = 0;
    }
    x = pollard_step(x, N);
    y = pollard_step(pollard_step(y, N), N);
    d = gcd(y - x, N);
    if (d == N) d = 1;
  }
  return d;
}
