/* KTH ACM Contest Template Library
 *
 * Numeric/Unsigned Big Integer/Simple
 *
 * Features:
 * # read/write from/to i-/ostream
 * # comparison
 * # addition
 * # subtraction
 * # multiplication [dependancy: addition]
 * # division and modulus by small integer (max ~10^9)
 * # exponentiation [dependancy: multiplication]
 * # find n:th root of (SLOW) [dependancy: exp., division, comparison]
 * # grows Dajnamickly when In Need.
 *
 * What's bad?
 * # division by arbitrary integer not possible
 * # not bit-oriented, therefore no bit ops
 *   (e.g. and, not, shift, etc)
 * # quite far from the Fastest Thing Possible.
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
 *
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

/* in order for subtraction to work properly, limb needs to be signed. */
typedef long long limb;
typedef vector<limb> bigint;
typedef bigint::const_iterator bcit;
typedef bigint::reverse_iterator brit;
typedef bigint::const_reverse_iterator bcrit;
typedef bigint::iterator bit;

/* size of limbs
 *             123456789  */
#define LSIZE 1000000000
#define LIMBDIGS 9

bigint BigInt(limb i) {
  bigint res;
  do {
    res.push_back(i % LSIZE);
  } while (i /= LSIZE);
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
 * justification.    */
ostream& operator<<(ostream& o, const bigint& n) {
  int began = 0;
  char ofill = o.fill();
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
  bcit i = n1.end()-1;
  bcit j = n2.end()-1;
  if (x > 0) {
    while (x--)
      if (*j--) return -1;
  } else if (x < 0) {
    while (x++)
      if (*i--) return 1;
  }
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
   * using bigint in conjunction with sign.cpp or in many
   * combinatorial counting problems.          */
  if (cy)
    while (i > a.begin())
      *i = LSIZE - *--i;
  return cy;
}

bigint& operator-=(bigint& a, const bigint& b) {
  sub(a, b);
  return a;
}

bigint& operator*=(bigint& a, limb b) {
  limb cy = 0;
  for (bit i = a.begin(); i != a.end(); ++i)
    cy = cy / LSIZE + *i * b, *i = cy % LSIZE;
  while (cy /= LSIZE)
    a.push_back(cy % LSIZE);
  return a;
}

bigint& operator*=(bigint& a, const bigint& b) {
  bigint x = a, y, bb = b;
  a.clear();
  for (bcit i = bb.begin(); i != bb.end(); ++i, ++j)
    (y = x) *= *i, a += y, x.insert(x.begin(), 0);
  return a;
}


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


bigint& divmod(bigint& a, limb b, limb* rest = NULL) {
  limb cy = 0;
  for (brit i = a.rbegin(); i != a.rend(); ++i)
    cy += *i, *i = cy / b, cy = (cy % b) * LSIZE;
  if (rest)
    *rest = cy / LSIZE;
  return a;
}

bigint& operator/=(bigint& a, limb b) { return divmod(a, b); }
limb operator%(const bigint& a, limb b) {
  limb res;
  bigint fubar = a;
  divmod(fubar, b, &res);
  return res;
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
    if (m == lo)
      break;
    (n2 = m) ^= e;
    f = cmp(n, n2);
    if (f < 0)
      hi = m;
    else if (f > 0)
      lo = m;
    else
      return m;
  }
  /* If just an approximation of the root is wanted, change return
   * statement to:
   * return lo;    (for floor(root))
   * return hi;    (for ceil(root))          */
  return BigInt(0);
}

