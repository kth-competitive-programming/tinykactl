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

template <class K, class V, class C, bool multi >
struct associative {
  typedef K key_type;
  typedef V value_type;
  typedef const value_type &vR;

  typedef splay_tree<value_type, value_compare> Tree;
  Tree t;
  typedef splay_node_iterator<value_type, false> iterator;
  typedef splay_node_iterator<value_type, true> reverse_iterator;

  associative(C _comp = C()) : comp(_comp), t(_comp) { }

  virtual V k2v(const K &k) = 0;

  // accessors
  iterator begin() { return iterator::begin(t.root); }
  iterator end() { return iterator::end(t.root); }
  reverse_iterator rbegin() { return reverse_iterator::begin(t.root); }
  reverse_iterator rend() { return reverse_iterator::end(t.root); }
  bool empty() const { return t.empty(); }
  unsigned size() const { return t.n; }

  // insert/erase
  pair<iterator, bool> insert(vR x) {
    bool f = !t.find(x);
    if (f || multi) t.insert(x);
    return make_pair(iterator(t.root), f);
  }
  //iterator insert(iterator pos, vR x) { return insert(x).first; }
  void clear() { t.clear(); }
  void erase(iterator pos) { t.erase(pos.p); }
  unsigned erase(const K &k) { // return number of erased elements?? (/stl)
    value_type v(k, V());
    unsigned count = 0;
    while (t.find(v)) t.erase(t.root), ++count;
    return count;
  }

  // map operations
  iterator find(const K &k, bool left = true) { // return first match?? (/stl)
    return iterator(t.find(k2v(k), left), t.root);
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
    if (comp(i, k2v(k))) ++i;
    return i;
  }
  iterator upper_bound(const K &k) {
    find(k, false); iterator i(t.root);
    if (!comp(k2v(k), i)) ++i;
    return i;
  }
  pair<iterator, iterator> equal_range(const K &k) {
    return make_pair(lower_bound(k), upper_bound(k));
  }
};

template <class vR, class C>
struct map_compare { // : binary_function<V, V, bool>
  C comp; map_compare(C _comp) : comp(_comp) { }
  bool operator()(vR x, vR y) { return comp(x.first, y.first); }
} comp;


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

template <class T, class C = less<T>, bool multi=false,
  class A = associative<T, T, C, multi>
struct set : A {
  virtual T k2v(const T &k) { return k; }
};



template <class K, class V, class C = less<K>, class M = map<K, V, C, true> >
struct multimap : M { multimap(C key_comp = C()) : M(key_comp) { } };

template <class T, class C = less<T>, class S = set<T, C, true> >
struct multiset : S { multiset(C comp = C()) : S(comp) { } };
