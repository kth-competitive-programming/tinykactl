/* KTH ACM Contest Template Library
 *
 * Numerical/Number Theory/Repeated Prime Factorization
 *
 * Credit:
 *   By Per Austrin
 */


#include <vector>

typedef pair<int, int> pii;
typedef vector<pii> vpii;

const vpii& Factor(int n) {
  static vector<vpii> factors;

  if (factors.size() <= (size_t)n)
    factors.resize(n+1);
  vpii& res = factors[n];
  if (res.empty() && n >= 2) {
    int fac = 2, count = 1;
    if (~n & 1) {
      while (~(n >>= 1) & 1) ++count;
    } else {
      fac = 3;
      while (n % fac) {
	fac += 2;
	if (fac*fac > n)
	  fac = n;
      }
      while (!((n /= fac) % fac)) ++count;
    }
    res.push_back(pii(fac, count));
    res.insert(res.end(), Factor(n).begin(), Factor(n).end());
  }
  return res;
}
