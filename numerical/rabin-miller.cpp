/* KTH ACM Contest Template Library
 *
 * Numerical/Number Theory/rabin-miller
 *
 * Credit:
 *   G. Miller & M.O. Rabin
 *   By source from Jimmy (written by one in his team)
 *   Based upon "Introduction to Algorithms"
 *   Modified by David Rydh
 */

#include "mulmod.cpp"
#include "pseudo.cpp"

unsigned long long witness(unsigned long long a, unsigned long long n) {
  int i;
  unsigned long long t, d, pn, x, p;

  p = n-1;
  i=0; t=p; pn=1;
  while( t ) {
    t = t >> 1;
    pn = pn << 1;
    i++;
  }
  pn = pn >> 1;

  d = 1;
  while (i--) {
    x = d;

    d = n>0x80000000ULL ? mulmod(d,d,n) : (d*d%n);
    if ((d==1) && (x != 1) && (x != n-1)) return 1;
    if (p&pn)
      d = n>0x80000000ULL ? mulmod(d,a,n) : (d*a%n);
    p = p << 1;
  }
  if (d!=1) return 1;

  return 0;
}


int isprime_rabin_miller( unsigned long long n, int s ) {
  unsigned long long a;

  // Note: Make sure n > 1.
  for (int i=0;i<s;i++) {
    a = ulpseudo()%(n-1)+1; // ulpseudo may be changed to rand
    if (witness(a, n))
      return 0;
  }
  return 1;
}
