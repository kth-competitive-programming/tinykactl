/* KTH ACM Contest Template Library
 *
 * tinystl/map/splay tree implementation
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By Mattias de Zalenski
 */
#include "utility.cpp"
#include "splay_tree.cpp"

template <class K, class V, class C = less<K> >
class map {
  typedef K key_type;
  typedef pair<const K, V> value_type;
  typedef const value_type &const_reference;
  typedef const value_type &vR;
  typedef C key_compare;
  class value_comp { // : public binary_function<V, V, bool>
    C comp; value_comp(C _comp) : comp(_comp) { }
    bool operator()(vR x, vR y) { return c(x.first, y.first); }
  } comp;
  typedef splay_tree<value_type, value_comp> tree;
  tree t;

  map(C key_comp) : comp(value_comp(key_comp)), t(comp) { }

};
