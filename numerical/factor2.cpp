/* KTH ACM Contest Template Library
 *
 * Numerical/Number Theory/Prime Factorization
 *
 * Credit:
 *   By Per Austrin
 */


#include "miller-rabin.h"
#include "pollard-rho.h"


/* Factors N into prime factors.  The factors are returned in the
 * "factors" vector.
 */
template <class T>
void factor(T N, vector<T>& factors) {
  vector<T> pending; // the pending vector is used as a stack
  if (N >= 2) {
    pending.push_back(N);
    while (!pending.empty()) {
      T x = pending.back();
      pending.pop_back();
      if (miller_rabin(x)) {
	factors.push_back(x);
      } else {
	T fac = pollard_rho(x);
	pending.push_back(fac);
	pending.push_back(x / fac);
      }
    }
  } else
    factors.push_back(N); // note that this adds 0 or 1 as single factor
  // if factors are wanted in order
  sort(factors.begin(), factors.end());
}
