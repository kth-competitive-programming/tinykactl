/* KTH ACM Contest Template Library
 *
 * Numeric/Unsigned Big Integer/Simple
 *
 * Features:
 * # read/write in base 10 from/to i-/ostream
 * # cmp/add/sub
 * # multiplication [dependancy: addition]
 * # division and modulo [dependancy for arbitrary denominator: add, sub]
 * # exponentiation [dependancy: multiplication]
 * # find n:th root of (SLOW) [dependancy: exp., division, comparison]
 * # grows dynamically when In Need.
 *
 * What's bad?
 * # not bit-oriented, therefore no bit ops
 *   (e.g. and, not, shift, etc)
 * # no I/O in other bases (easy to implement naively though)
 * # far from the Fastest Thing Possible (TM).
 *
 *
 * Credit:
 *   By
 *        Per Austrin, pego@kth.se 2002-09-15
 *   Updated by
 *        Per Austrin, Christer Stålstrand, 2002-09-26
 *   Bugfixes (fix in modulo and input/output)
 *        Per Austrin, 2002-10-05
 *   Bugfixes and update (fixes in add and sub, code compression)
 *        Per Austrin, 2003-03-14
 *   Update (the long called-for divmod with arbitrary denominator!!
 *           and more code compression of course)
 *        Per Austrin, 2003-09-22
 *
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

/* if long longs are disallowed, use the following alternative
 * definitions (the rest should work by magic):
 * #define LSIZE 10000
 * #define LIMBDIGS 4
 * typedef int limb;     */

#define LSIZE 1000000000 /* 10^9 */
#define LIMBDIGS 9

/* in order for subtraction to work properly, limb needs to be signed. */
typedef long long limb;
typedef vector<limb> bigint;
typedef bigint::const_iterator bcit;
typedef bigint::reverse_iterator brit;
typedef bigint::const_reverse_iterator bcrit;
typedef bigint::iterator bit;


bigint BigInt(limb i) {
  bigint res;
  do res.push_back(i % LSIZE);
  while (i /= LSIZE);
  return res;
}

istream& operator>>(istream& i, bigint& n) {
  string s;
  i >> s;
  int l = s.length();
  n.clear();
  while (l > 0) {
    int j = 0;
    for (int k = l > LIMBDIGS ? l-LIMBDIGS: 0; k < l; ++k)
      j = 10*j + s[k]-'0';
    n.push_back(j);
    l -= LIMBDIGS;
  }
  return i;
}

/* Warning: the ostream must be configured to print things with right
 * justification, lest output be ooky.    */
ostream& operator<<(ostream& o, const bigint& n) {
  int began = 0, ofill = o.fill();
  o.fill('0');
  for (bcrit i = n.rbegin(); i != n.rend(); ++i) {
    if (began) o << setw(LIMBDIGS);
    if (*i) began = 1;
    if (began) o << *i;
  }
  if (!began) o << "0";
  o.fill(ofill);
  return o;
}

/* The base comparison function. semantics like strcmp(...).   */
int cmp(const bigint& n1, const bigint& n2) {
  int x = n2.size() - n1.size();
  bcit i = n1.end() - 1, j = n2.end() - 1;
  while (x-- > 0) if (*j--) return -1;
  while (++x < 0) if (*i--) return 1;
  // above replace below (untested)
  /*
  if (x > 0) {
    while (x--)
      if (*j--) return -1;
  } else if (x < 0) {
    while (x++)
      if (*i--) return 1;
  }
  */
  for (; i + 1 != n1.begin(); --i, --j)
    if (*i != *j)
      return *i-*j;
  return 0;
}

/* The other operators will be automatically defined by STL */
bool operator==(const bigint& n1, const bigint& n2) { return !cmp(n1,n2); }
bool operator<(const bigint& n1, const bigint& n2) { return cmp(n1,n2) < 0; }

bigint& operator+=(bigint& a, const bigint& b) {
  if (a.size() < b.size()) a.resize(b.size());
  limb cy = 0;
  bit i = a.begin();
  for (bcit j = b.begin(); i != a.end() && (cy || j < b.end()); ++j, ++i)
    cy += *i + (j < b.end() ? *j : 0), *i = cy % LSIZE, cy /= LSIZE;
  if (cy) a.push_back(cy);
  return a;
}

/* Returns true if sign changed   */
bool sub(bigint& a, const bigint& b) {
  if (a.size() < b.size()) a.resize(b.size());
  limb cy = 0;
  bit i = a.begin();
  for (bcit j = b.begin(); i != a.end() && (cy || j < b.end()); ++j, ++i) {
    *i -= cy + (j < b.end() ? *j : 0);
    if ((cy = *i < 0)) *i += LSIZE;
  }
  /* If sign changed, flip all digits.  These three lines can be
   * ignored if it is known that the sign will not change, e.g. when
   * using bigint in conjunction with sign.cpp, in the divmod method,
   * or in many combinatorial counting problems.  */
  if (cy)
    while (i-- > a.begin())
      *i = LSIZE - *i;
  return cy;
}
bigint& operator-=(bigint& a, const bigint& b) { sub(a, b); return a; }

bigint& operator*=(bigint& a, limb b) {
  limb cy = 0;
  for (bit i = a.begin(); i != a.end(); ++i)
    cy = cy / LSIZE + *i * b, *i = cy % LSIZE;
  while (cy /= LSIZE) a.push_back(cy % LSIZE);
  return a;
}

bigint& operator*=(bigint& a, const bigint& b) {
  bigint x = a, y, bb = b;
  a.clear();
  for (bcit i = bb.begin(); i != bb.end(); ++i)
    (y = x) *= *i, a += y, x.insert(x.begin(), 0);
  return a;
}

/* a will hold floor(a/b), rest will hold a % b  */
bigint& divmod(bigint& a, limb b, limb* rest = NULL) {
  limb cy = 0;
  for (brit i = a.rbegin(); i != a.rend(); ++i)
    cy += *i, *i = cy / b, cy = (cy % b) * LSIZE;
  if (rest)
    *rest = cy / LSIZE;
  return a;
}

/* a will hold a % b (and is returned), quo will hold floor(a/b).
 * NB!! different semantics from one-limb divmod!!
 * NB!! quo should be different from a!! */
bigint& divmod(bigint& a, const bigint& b, bigint* quo = NULL) {
  /* If divmod is never called with b the same as a or quo
   * this copying is not necessary. */
  bigint den = b;
  brit j = den.rbegin(), i = a.rbegin();
  for ( ; j != den.rend() && !*j; ++j);
  for ( ; i != a.rend() && !*i; ++i);
  int n = a.rend() - i, m = den.rend() - j;
  if (!m) { /* Division by zero! */ abort(); }
  /* If divisor is limbsized, resort to regular linear-time divmod. */
  if (m == 1) {
    bigint q;
    return (quo ? *quo : q) = a, a.resize(1), 
      divmod(quo ? *quo : q, *j, &a.front()), a;
  }
  
  bigint tmp;
  /* Use first two digits for a good estimate of the quotient.
   * (Though this function could probably be a lot shorter if we just
   * used one digit instead)  */
  limb den0 = (*++j + *--j * LSIZE) + 1;
  if (quo) quo->clear();
  /* Loop invariant: quo * den + a = num */
  while (a >= den) {
    limb num0 = (*++i + *--i * LSIZE), z = num0 / den0, cy = 0;
    /* Silly degenerate case: */
    if (z == 0 && n == m) z = 1;
    tmp.resize(n - m - !z);
    /* Non-silly degenerate case: */
    if (!z) z = num0 / (*j + 1);
    /* Set tmp = z * b^(n-m) and add to quotient */
    if (quo) tmp.push_back(z), *quo += tmp, tmp.pop_back();
    /* Set tmp = den * z * b^(n-m)  */
    for (bcit j = den.begin(); j != den.end(); ++j)
      cy += *j * z, tmp.push_back(cy % LSIZE), cy /= LSIZE;
    if (cy) tmp.push_back(cy);
    /* Note that we rely on the important fact that tmp doesn't have
     * more limbs than a, so that a won't be resized, and the iterator
     * i will still valid. */
    if (tmp.size() > a.size()) tmp.resize(a.size());
    sub(a, tmp);
    while (i != a.rend() && !*i) --n, ++i;
  }
  return a; 
}


bigint& operator/=(bigint& a, const bigint& b) {
  bigint q;
  return divmod(a, b, &q), a = q;
}
bigint& operator%=(bigint& a, const bigint& b) { return divmod(a, b, NULL); }

bigint& operator/=(bigint& a, limb b) { return divmod(a, b); }
limb operator%(const bigint& a, limb b) {
  limb res;
  bigint fubar = a;
  return divmod(fubar, b, &res), res;
}


/* Auxilliary stuff which should probably be moved out.
 */ 


/* Exponentiation. */
bigint& operator^=(bigint& a, limb b) {
  bigint aa = a;
  a.clear(); a.push_back(1);
  while (b) {
    if (b & 1) a *= aa;
    aa *= aa;
    b >>= 1;
  }
  return a;
}

/* Finds the e:th root of n in far worse time than necessary.
 * Returns 0 if the root doesn't exist.    */
bigint root(const bigint& n, limb e) {
  int f;
  bigint lo = BigInt(0), hi, m, n2;
  hi = BigInt(LSIZE);
  // let hi ~ LS^(1+log_LS(n))/e) = O(n^(1 + 1/e))
  hi ^= ((n.size()+1) / e) + 1;
  while (1) {
    (m = lo) += hi;
    divmod(m, 2);
    if (m == lo) break;
    (n2 = m) ^= e;
    f = cmp(n, n2);
    if (f < 0) hi = m;
    else if (f > 0) lo = m;
    else return m;
  }
  /* If just an approximation of the root is wanted, change return
   * statement to:
   * return lo;    (for floor(root))
   * return hi;    (for ceil(root))          */
  return BigInt(0);
}

