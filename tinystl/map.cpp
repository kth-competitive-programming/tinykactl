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

template <class K, class V, class C = less<K>, bool multi=false >
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
  Tree t;
  typedef splay_node_iterator<value_type, false> iterator;
  typedef splay_node_iterator<value_type, true> reverse_iterator;

  map(C key_comp = C()) : comp(value_compare(key_comp)), t(comp) { }

  // accessors
  key_compare key_comp() const { return comp.comp; }
  value_compare value_comp() const { return comp; }
  iterator begin() { return iterator::begin(t.root); }
  iterator end() { return iterator::end(); }
  reverse_iterator rbegin() { return reverse_iterator::begin(t.root); }
  reverse_iterator rend() { return reverse_iterator::end(); }
  bool empty() const { return t.empty(); }
  unsigned size() const { return t.n; }
  V &operator[](const K &k) {
    return (*insert(make_pair(k, V())).first).second;
  }

  // insert/erase
  pair<iterator, bool> insert(vR x) {
    bool f = !t.find(x);
    if (f || multi) t.insert(x);
    return make_pair(iterator(t.root), f);
  }
  //iterator insert(iterator pos, vR x) { return insert(x).first; }
  void erase(iterator pos) { t.erase(pos); }
  unsigned erase(const K &k) { // return number of erased elements?? (/stl)
    value_type v(k, V());
    unsigned count = 0;
    while (t.find(v)) t.erase(t.root), ++count;
    return count;
  }

  // map operations
  iterator find(const K &k, bool left = true) { // return first match?? (/stl)
    return iterator(t.find(value_type(k, V()), left));
  }
  unsigned count(const K &k) {
    if (multi) {
      unsigned count = 0;
      iterator i = find(k);
      while (i != end() && *i == k)
	++count, ++i;
      return count;
    }
    else
      return find(k) == end() ? 0 : 1;
  }
  iterator lower_bound(const K &k) {
    find(k, true); iterator i(t.root);
    if (key_comp()(i->first, k)) ++i;
    return i;
  }
  iterator upper_bound(const K &k) {
    find(k, false); iterator i(t.root);
    if (!key_comp()(k, i->first)) ++i;
    return i;
  }
  pair<iterator, iterator> equal_range(const K &k) {
    return make_pair(lower_bound(k), upper_bound(k));
  }
};

template <class K, class V, class C = less<K> >
struct multimap : public map<K, V, C, true> {
  multimap(C key_comp=C()) : map<K, V, C, true>(key_comp) { }
};
