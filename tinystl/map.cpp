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
struct map {
  typedef K key_type;
  typedef pair<const K, V> value_type;
  typedef const value_type &vR;
  typedef C key_compare;

  struct value_compare { // : public binary_function<V, V, bool>
    C comp; value_compare(C _comp) : comp(_comp) { }
    bool operator()(vR x, vR y) { return comp(x.first, y.first); }
  } comp;

  typedef splay_tree<value_type, value_compare> Tree; 
  Tree t; unsigned n;
  typedef splay_node_iterator<value_type, false> iterator;
  typedef splay_node_iterator<value_type, true> reverse_iterator;

  map(C key_comp = C()) : comp(value_compare(key_comp)), t(comp), n(0) { }

  // accessors
  key_compare key_comp() const { return comp.comp; }
  value_compare value_comp() const { return comp; }
  iterator begin() { return iterator::begin(t.root); }
  iterator end() { return iterator::end(); }
  reverse_iterator rbegin() { return reverse_iterator::begin(t.root); }
  reverse_iterator rend() { return reverse_iterator::end(); }
  bool empty() const { return t.empty(); }
  unsigned size() const { return n; }
  V &operator[](const K &k) {
    return (*insert(make_pair(k, V())).first).second;
  }

  // insert/erase
  pair<iterator, bool> insert(vR x) {
    bool f = !t.find(x);
    if (f) t.insert(x), ++n;
    return make_pair(iterator(t.root), f);
  }
  iterator insert(iterator pos, vR x) { return insert(x).first; }
  void erase(iterator pos) { t.erase(pos); --n; }
  unsigned erase(const K &k) {
    value_type v(k, V());
    if (t.find(v)) t.erase(t.root), --n;
    return n;
  }

  // map operations
  iterator find(const K &k) { return iterator(t.find(value_type(k, V()))); }
  unsigned count(const K &k) { return find(k) == end() ? 0 : 1; }
  iterator lower_bound(const K &k) { find(k); return iterator(t.root); }
  iterator upper_bound(const K &k) {
    find(k); iterator i(t.root);
    if (i != end() && !key_comp()(k, *i.first)) ++i;
    return i;
  }
  pair<iterator, iterator> equal_range(const K &k) {
    return make_pair(lower_bound(k), upper_bound(k));
  }
};
