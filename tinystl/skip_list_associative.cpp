/* KTH ACM Contest Template Library
 *
 * tinystl/dictionaries/associative wrapper for skip list
 *
 * Credit:
 *   By Per Austrin
 */

#include "pair.cpp"
#include "skip_list.cpp"

template <class K, class V, class C, bool multi>
struct associative: skip_list<V, C> {
  typedef skip_list<V, C> L;
  typedef K key_type;
  typedef V value_type;
  typedef const V &VR;
  typedef const K &KR;
  
  associative(C c = C()): L(c) {}
  virtual V k2v(KR k) = 0;

  pair<iterator, bool> insert(VR x) {
    iterator i = L::insert(x, multi);
    return make_pair(i, i != end());
  }

  void erase(iterator x) { L::erase(x); }
  iterator find(KR k) { return L::find(k2v(k)); }

  int count(KR k) {
    int r = 0;
    V v = k2v(k);
    iterator i = find(v);
    while (i != end() && !c(v, *i)) ++r, ++i;
    return r;
  }    

  int erase(KR k) {
    int r = 0;
    pair<iterator, iterator> lu = equal_range(k);
    for (iterator i = lu.first; i != lu.second; ++i, ++r)  erase(i);
    return r;
  }
  
  iterator lower_bound(KR k) {
    iterator i = find(k2v(k));
    return i == end() ? bck[0]->nxt[0] : i;
  }
  
  iterator upper_bound(KR k) {
    iterator i = find(k2v(k, false));
    return (i == end() ? bck[0] : i)->nxt[0];
  }

  pair<iterator, iterator> equal_range(KR k) {
    return make_pair(lower_bound(k), upper_bound(k));
  }
};
