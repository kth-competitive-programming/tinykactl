/* KTH ACM Contest Template Library
 *
 * tinystl/set/associative implementation
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By Mattias de Zalenski, David Rydh
 */
#include "associative.cpp"

template <class T, class C = less<T>, bool multi=false,
  class A = associative<T, T, C, multi> >
struct set : A {
  virtual T k2v(const T &k) { return k; }
};

template <class T, class C = less<T>, class S = set<T, C, true> >
struct multiset : S { multiset(C comp = C()) : S(comp) { } };
