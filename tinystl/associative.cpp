/* KTH ACM Contest Template Library
 *
 * tinystl/map/splay tree implementation
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By Mattias de Zalenski, David Rydh
 */
#ifndef __TS_ASSOCIATIVE__
#define __TS_ASSOCIATIVE__

#include "pair.cpp"
#include "splay_tree.cpp"

template <class K, class V, class C, bool multi >
struct associative {
  typedef K key_type;
  typedef V value_type;
  typedef const value_type &VR;

  typedef splay_tree<V, C> Tree;
  Tree t;
  typedef Tree::iterator iterator;
  typedef Tree::reverse_iterator reverse_iterator;

  associative(C comp = C()) : t(comp) { }
  virtual ~associative() {}
  virtual V k2v(const K &k) = 0;

  // accessors
  iterator begin() { return t.begin(); }
  iterator end() { return t.end(); }
  reverse_iterator rbegin() { return t.rbegin(); }
  reverse_iterator rend() { return t.rend(); }
  bool empty() const { return t.empty(); }
  unsigned size() const { return t.n; }

  // insert/erase
  pair<iterator, bool> insert(VR x) {
    bool f = t.find(x, false) == t.end();
    if (f || multi) t.insert(x);
    return make_pair(iterator(t.root, t), f);
  }
  //iterator insert(iterator pos, VR x) { return insert(x).first; }
  void clear() { t.clear(); }
  void erase(iterator pos) { t.erase(pos.p); }
  unsigned erase(const K &k) { return t.erase(k2v(k)); }

  // associative operations
  iterator find(const K &k, bool left = true) { // return first match?? (/stl)
    return t.find(k2v(k), left);
  }
  unsigned count(const K &k) { return t.count(k2v(k)); }
  iterator lower_bound(const K &k) { return t.lower_bound(k2v(k)); }
  iterator upper_bound(const K &k) { return t.upper_bound(k2v(k)); }
  pair<iterator, iterator> equal_range(const K &k) {
    return make_pair(lower_bound(k), upper_bound(k));
  }
};

#endif
