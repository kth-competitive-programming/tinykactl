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

template <class S, class T>
struct pair {
  typedef S first_type;
  typedef T second_type;
  S first; T second;

  pair() : first(S()), second(T()) { }
  pair(const S &s, const T &t) : first(s), second(t) { }
  template<class U, class V>
  pair(const pair<U,V> &p) : first(p.first), second(p.second) { }

  bool operator==(const S &x ) { return first==x.first && second==x.second; }
  bool operator<( const S &x ) { return first<x.first ||
				   (!(x.first<first) && second < x.second); }
};

template <class S, class T>
pair<S, T> make_pair(const S& s, const T &t) { return pair<S, T>(s, t); }
