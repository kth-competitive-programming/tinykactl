/* KTH ACM Contest Template Library
 *
 * Numeric/Big Integer/Simple
 *
 * Features:
 * # read/write from/to i-/ostream
 * # comparison
 * # addition
 * # multiplication [dependancy: addition]
 * # division and modulus by small integer (max ~10^9)
 * # exponentiation [dependancy: multiplication]
 * # find n:th root of (SLOW) [dependancy: exp., division, comparison]
 * # grows Dajnamickly when In Need.
 *
 * What's bad?
 * # subtraction not yet implemented ;)
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
 *
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

/*                123456789 */
#define LIMBSIZE 1000000000
typedef unsigned long long ull;
typedef vector<ull> bigint;
typedef bigint::const_iterator bcit;
typedef bigint::reverse_iterator brit;
typedef bigint::iterator bit;

bigint BigInt(ull i) {
  bigint res;
  do {
    res.push_back(i % LIMBSIZE);
  } while (i /= LIMBSIZE);
  return res;
}

istream& operator>>(istream& i, bigint& n) {
  string s;
  i >> s;
  int l = s.length();
  n.clear();
  while (l > 0) {
    int j = 0;
    for (int k = l > 9 ? l-9: 0; k < l; ++k)
      j = 10*j + s[k]-'0';
    n.push_back(j);
    l -= 9;
  }
  return i;
}

ostream& operator<<(ostream& o, bigint& n) {
  int began = 0;
  o.fill('0');
  for (brit i = n.rbegin(); i != n.rend(); ++i) {
    if (began) o << setw(9);
    if (*i) began = 1;
    if (began) o << *i;
  }
  if (!began) o << "0";
  return o;
}

/* Uppfyller:  sgn(cmp(n1,n2)) = sgn(n1-n2) */
int cmp(const bigint& n1, const bigint& n2) {
  int x = n2.size() - n1.size();
  bcit i = n1.end()-1;
  bcit j = n2.end()-1;
  while (x) {
    if (x > 0) {
      if (*j) return -1;
      --j; --x;
    } else {
      if (*i) return 1;
      --i; ++x;
    }
  }
  for (; i + 1 != n1.begin(); --i, --j)
    if (*i != *j)
      return *i-*j;
  return 0;
}

int operator!=(const bigint& n1, const bigint& n2) { return cmp(n1,n2); }
int operator==(const bigint& n1, const bigint& n2) { return !cmp(n1,n2); }
int operator<(const bigint& n1, const bigint& n2) { return cmp(n1,n2) < 0; }
int operator>(const bigint& n1, const bigint& n2) { return cmp(n1,n2) > 0; }
int operator<=(const bigint& n1, const bigint& n2) { return cmp(n1,n2) <= 0; }
int operator>=(const bigint& n1, const bigint& n2) { return cmp(n1,n2) >= 0; }


bigint& operator+=(bigint& n1, const bigint& n2) {
  ull mem = 0;
  if (n1.size() < n2.size())
    n1.resize(n2.size());
  bit i = n1.begin();
  for (bcit j = n2.begin(); j != n2.end(); ++j, ++i) {
    mem += *j + *i;
    *i = mem % LIMBSIZE;
    mem /= LIMBSIZE;
  }
  if (mem) {
    if (i == n1.end())
      n1.push_back(mem % LIMBSIZE);
    else
      *i += mem % LIMBSIZE;
  }
  return n1;
}

bigint& operator*=(bigint& n1, ull n2) {
  ull mem = 0;
  for (bit i = n1.begin(); i != n1.end(); ++i) {
    mem = mem / LIMBSIZE + *i * n2;
    *i = mem % LIMBSIZE;
  }
  while (mem /= LIMBSIZE)
    n1.push_back(mem % LIMBSIZE);
  return n1;
}

bigint& operator*=(bigint& n1, const bigint& n2) {
  bigint x = n1;
  n1.clear();
  int j = 0;
  for (bcit i = n2.begin(); i != n2.end(); ++i, ++j) {
    bigint y = x;
    y *= *i;
    for (int k = j; k; --k)
      y.insert(y.begin(), 0);
    n1 += y;
  }
  return n1;
}


bigint& operator^=(bigint& n1, ull n2) {
  bigint a = n1;
  n1.clear();
  n1.push_back(1);
  while (n2) {
    if (n2 & 1)
      n1 *= a;
    a *= bigint(a); /* clone needed. */
    n2 >>= 1;
  }
  return n1;
}

bigint& divmod(bigint& n1, ull n2, ull* rest = NULL) {
  ull mem = 0;
  for (brit i = n1.rbegin(); i != n1.rend(); ++i) {
    mem += *i;
    *i = mem / n2;
    mem = (mem % n2) * LIMBSIZE;
  }
  if (rest)
    *rest = mem;
  return n1;
}

bigint& operator/=(bigint& n1, ull n2) { return divmod(n1, n2); }
ull operator%(const bigint& n1, ull n2) {
  ull res;
  bigint fubar = n1;
  divmod(fubar, n2, &res);
  return res;
}


/* Finds the nth root of p in far worse time than necessary.
 * Returns 0 if the root doesn't exist.
 */
bigint nroot(const bigint& p, ull n) {
  int f;
  bigint lo = BigInt(0), hi, m, p2;
  hi = BigInt(LIMBSIZE);
  hi ^= ((p.size()+1) / n) + 1;
  while (1) {
    (m = lo) += hi;
    divmod(m, 2);
    if (m == lo)
      break;
    (p2 = m) ^= n;
    f = cmp(p, p2);
    if (f < 0)
      hi = m;
    else if (f > 0)
      lo = m;
    else
      return m;
  }
  return BigInt(0);
}
