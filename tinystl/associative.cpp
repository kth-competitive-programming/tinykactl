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
  typedef const value_type &vR;

  typedef splay_tree<value_type, C> Tree;
  C comp; Tree t;
  typedef Tree::iterator iterator;
  typedef Tree::reverse_iterator reverse_iterator;

  associative(C _comp = C()) : comp(_comp), t(_comp) { }
  virtual ~associative() {}
  virtual V k2v(const K &k) = 0;

  // accessors
  iterator begin() { return iterator::begin(t); }
  iterator end() { return iterator::end(t); }
  reverse_iterator rbegin() { return reverse_iterator::begin(t); }
  reverse_iterator rend() { return reverse_iterator::end(t); }
  bool empty() const { return t.empty(); }
  unsigned size() const { return t.n; }

  // insert/erase
  pair<iterator, bool> insert(vR x) {
    bool f = !t.find(x);
    if (f || multi) t.insert(x);
    return make_pair(iterator(t.root, t), f);
  }
  //iterator insert(iterator pos, vR x) { return insert(x).first; }
  void clear() { t.clear(); }
  void erase(iterator pos) { t.erase(pos.p); }
  unsigned erase(const K &k) { // return number of erased elements?? (/stl)
    V v = k2v(k);
    unsigned count = 0;
    while (t.find(v)) t.erase(t.root), ++count;
    return count;
  }

  // map operations
  iterator find(const K &k, bool left = true) { // return first match?? (/stl)
    return iterator(t.find(k2v(k), left), t);
  }
  unsigned count(const K &k) {
    if (multi) {
      unsigned count = 0;
      iterator i = find(k);
      V v = k2v(k);
      while (i != end() && *i == v)
	++count, ++i;
      return count;
    }
    else
      return find(k) == end() ? 0 : 1;
  }
  iterator lower_bound(const K &k) {
    find(k, true); iterator i(t.root, t);
    if (comp(i, k2v(k))) ++i;
    return i;
  }
  iterator upper_bound(const K &k) {
    find(k, false); iterator i(t.root, t);
    if (!comp(k2v(k), i)) ++i;
    return i;
  }
  pair<iterator, iterator> equal_range(const K &k) {
    return make_pair(lower_bound(k), upper_bound(k));
  }
};

#endif
