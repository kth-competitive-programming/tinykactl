/* KTH ACM Contest Template Library
 *
 * tinystl/utility
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By Mattias de Zalenski
 */

template <class T>
inline void swap(T &a, T &b) { T t = a; a = b; b = t; }
//inline void swap(int &a, int &b) { a ^= b ^= a ^= b; }

template <class T> const T &min(const T &a, const T &b) { return b<a?b:a; }
template <class T> const T &max(const T &a, const T &b) { return a<b?b:a; }

template <class S, class T>
struct pair {
  typedef S first_type;
  typedef T second_type;
  typedef const pair<S, T> &R;
  S first; T second; pair() : first(S()), second(T()) { }
  pair(const S &s, const T &t) : first(s), second(t) { }

  // E.g. needed for pair<S,T> to pair<const S,T> conversion...
  template <class U,class V>
  pair(const pair<U,V> &p) : first(p.first), second(p.second) { }

  bool operator==(R p) const { return first==p.first && second==p.second; }
  bool operator<(R p) const { return first<p.first ||
			  first<=p.first && second<p.second; }
};
template <class S, class T>
pair<S, T> make_pair(const S& s, const T &t) { return pair<S, T>(s, t); }
