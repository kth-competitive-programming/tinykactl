/* KTH ACM Contest Template Library
 *
 * Numerical/Combinatorics/No of permutations (multinomial numbers)
 *
 * Feature:
 * # Makes best possible use of the inttype's capacity by cancelling
 *   out common factors before making any multiplication.
 *
 * Credit:
 *   By Per Austrin, 2002-09-26
 */

#include <algorithm>
#include <string>

#define INT int
typedef unsigned int uint;

INT gcd(INT a, INT b) {
  INT r = b;
  do {
    b = r;
    r = a % b;
    a = b;
  } while (r != 0);
  return b;
}

/* Calculates the number of permutations of the string s.
 */
INT n_perms(string s) {
  int num[s.length()], den[s.length()];
  sort(s.begin(), s.end());
  for (uint i = 0; i < s.length(); ++i) {
    num[i] = i + 1;
    den[i] = 1;
    if (i > 0 && s[i] == s[i-1])
      den[i] = den[i-1]+1;
  }

  for (uint i = 0; i < s.length(); ++i) {
    for (uint j = 0; j < s.length(); ++j) {
      if (den[i] == 1)
	break;
      int x = gcd(num[j], den[i]);
      if (x > 1) {
	num[j] /= x;
	den[i] /= x;
      }
    }
  }
  INT res = 1;
  for (uint i = 0; i < s.length(); i++)
    res *= num[i];
  return res;
}
