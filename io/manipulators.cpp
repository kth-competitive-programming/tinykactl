/* KTH ACM Contest Template Library
 *
 * IO/Stream manipulators
 *
 * Credit:
 *   By Fredrik Niemelä
 *   Thanks to Kevlin Henney
 */

#include <iostream>

istream &eatline(istream &in) {
  while (in && in.get() != '\n');
  return in;
}

istream &blankline(istream &in) {
  char c, lastc=0;
  while (in && ((c = in.get()) != '\n' || lastc != '\n')) lastc = c;
  return in;
}

template <class T, bool Z = true>
struct expand {
  T n;

  expand(T _n) : n(_n) {}
  ostream &operator()(ostream &out) const {
    static char const* units[] = {
      "zero", "one", "two", "three", "four",
      "five", "six", "seven", "eight", "nine",
      "ten", "eleven", "twelve", "thirteen", "fourteen",
      "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
    };

    static char const* tens[] = {
      "zero", "ten", "twenty", "thirty", "fourty",
      "fifty", "sixty", "seventy", "eighty", "ninety"
    };

    typedef expand<T, false> E;
    if (n < 0) return out << "minus " << E(-n);
    if (n == 0) return Z ? out << units[n] : out;
    if (n < 20) return out << units[n];
    if (n < 100) return out << tens[n/10] << E(n%10);
    if (n < 1000) return out << E(n/100) << "hundred" << E(n%100); 
    if (n < T(1e6)) return out << E(n/1000) << "thousand" << E(n%1000);
    if (n < T(1e9)) return out << E(n/T(1e6)) << "million" << E(n%T(1e6));
    return out << E(n/T(1e9)) << "billion" << E(n%T(1e9));
  }
};

template <class T>
ostream &operator<<(ostream &out, T x) {
  return x(out);
}

