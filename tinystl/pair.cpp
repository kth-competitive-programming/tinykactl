/* KTH ACM Contest Template Library
 *
 * tinystl/pair
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By Mattias de Zalenski
 */
#ifndef __TS_PAIR__
#define __TS_PAIR__

template <class S, class T>
struct pair {
  typedef S first_type;
  typedef T second_type;
  typedef const pair<S, T> &R;
  S first; T second; pair() : first(S()), second(T()) { }
  pair(const S &s, const T &t) : first(s), second(t) { }
  // E.g. needed for pair<S,T> to pair<const S,T> conversion...
  template <class U, class V>
  pair(const pair<U,V> &p) : first(p.first), second(p.second) { }
  bool operator==(R p) const { return first==p.first && second==p.second; }
  bool operator<(R p) const { return first<p.first ||
				    first<=p.first && second<p.second; }
};

template <class S, class T>
pair<S, T> make_pair(const S& s, const T &t) { return pair<S, T>(s, t); }

#endif
