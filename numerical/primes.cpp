/* KTH ACM Contest Template Library
 *
 * Numerical/Number Theory/Primes, prime factorisation
 *
 * Credit:
 *   By Mattias de Zalenski
 */

#include <vector>

using namespace std;

template <class T>
struct primes {
  typedef vector<int> V;
  V v; // primes vector
  int k; // next number to check
  primes() : k(3) { v.push_back(2); }

  void generate(T n2) {
    while ((T) k * k <= n2) {
      if ((int) factor(k) == k)
	v.push_back(k);
      k += 2;
    }
  }

  T factor(T n) {
    generate(n);
    for (V::iterator i = v.begin(); i != v.end() && (*i) * (*i) <= n; i++)
      if (n % (*i) == 0) return (*i);
    return n;
  }
};
