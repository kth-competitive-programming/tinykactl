/* KTH ACM Contest Template Library
 *
 * tinystl/map/associative implementation
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By Mattias de Zalenski, David Rydh
 */
#include "associative.cpp"

template <class vR, class C>
struct map_compare {
  C comp; map_compare(C _comp) : comp(_comp) { }
  bool operator()(vR x, vR y) { return comp(x.first, y.first); }
};

template <class K, class V, class C = less<K>, bool multi=false,
  class KV = pair<const K, V>,
  class AC = map_compare<const KV &, C>,
  class A = associative<K, KV, AC, multi> >
struct map : A {
  map(C key_comp = C()) : A(AC(key_comp)) { }
  V &operator[](const K &k) {
    return (*insert(k2v(k)).first).second;
  }
  virtual KV k2v(const K &k) { return make_pair(k,V()); }
};

template <class K, class V, class C = less<K>, class M = map<K, V, C, true> >
struct multimap : M { multimap(C key_comp = C()) : M(key_comp) { } };
