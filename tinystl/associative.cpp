/* KTH ACM Contest Template Library
 *
 * tinystl/dictionaries/associative wrapper for skip list
 *
 * Credit:
 *   By Per Austrin
 */

#include "pair.cpp"
#include "skip_list.cpp"
//#include "splay_tree.cpp"

template <class K, class V, class C, bool multi,
          class P = skip_list<V, C> >
//          class P = splay_tree<V, C> >
struct associative: P {
  typedef typename P::iterator iterator; // only necessary when using -pedantic
  typedef K key_type;
  typedef V value_type;
  typedef const V &VR;
  typedef const K &KR;

  associative(C c = C()): P(c) {}
  virtual V k2v(KR k) = 0;

  pair<iterator, bool> insert(VR x) {
    iterator i = P::insert(x, multi);
    return make_pair(i, i != end());
  }
  void erase(iterator x) { P::erase(x); }
  int erase(KR k) {
    int r = 0;
    pair<iterator, iterator> lu = equal_range(k);
    for (iterator i = lu.first; i != lu.second; ++r)  erase(i++);
    return r;
  }
  
  iterator find(KR k, bool left = true) { return P::find(k2v(k), left); }

  int count(KR k) {
    int r = 0;
    V v = k2v(k);
    iterator i = find(k, true);
    while (i != end() && !c(v, *i)) ++r, ++i;
    return r;
  }

  iterator lower_bound(KR k) { return P::lower_bound(k2v(k)); }
  iterator upper_bound(KR k) { return P::upper_bound(k2v(k)); }

  pair<iterator, iterator> equal_range(KR k) {
    return make_pair(lower_bound(k), upper_bound(k));
  }
};
