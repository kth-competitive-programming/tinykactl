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
  pair(S s, T t) : first(s), second(t) { }
};

template <class S, class T>
pair<S, T> make_pair(S s, T t) { return pair<S, T>(s, t); }
