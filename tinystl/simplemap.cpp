/* KTH ACM Contest Template Library
 *
 * tinystl/map/simple map
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By David Rydh
 */

#include "pair.cpp"
#include "function.cpp"
#include "sort.cpp"
#include "binary_search.cpp"

template <class K, class V, class C = less<K> >
struct map {
  typedef K key_type;
  //  typedef pair<const K, V> value_type;
  typedef pair<K, V> value_type;
  typedef const value_type &const_reference;
  typedef vector<value_type>::iterator iterator;
  typedef const value_type &vR;
  typedef const key_type &kR;
  typedef C key_compare;

  struct value_comp { // : public binary_function<V, V, bool>
    C c; value_comp(C _c) : c(_c) { }
    bool operator()(vR x, vR y) { return c(x.first, y.first); }
    bool operator()(vR x, kR y) { return c(x.first, y); }
    bool operator()(kR x, vR y) { return c(x, y.first); }
    bool operator()(kR x, kR y) { return c(x, y); }
  } comp;

  vector<value_type> v;
  bool need_sort;

  map(C key_comp=C()) : comp(value_comp(key_comp)) { need_sort = false; }

  void swap( map<K,V,C> &x ) { v.swap(x.v); }

  void sort() {
    if( need_sort )
      ::sort(v.begin(),v.end(),comp), need_sort=false;
  }

  // NB! No const-iterators (not possible)
  iterator begin() { sort(); return v.begin(); }
  iterator end() { sort(); return v.end(); }

  iterator find( kR k ) {
    sort();
    iterator i = lower_bound(v.begin(),v.end(),k,comp);
    if( i!=v.end() && comp(k,i->first) ) i = v.end();
    return i;
  }
  size_t count( kR k ) { sort(); return find(k)!=v.end() ? 1:0;  }

  V &operator[]( kR k) {
    iterator i = find(k);
    if( i == v.end() ) i = insert( value_type(k, V()) ).first;
    return i->second;
  }

  pair<iterator,bool> insert( vR x ) {
    iterator i = find(x.first);
    if( i != v.end() ) return make_pair(i,false);
    v.push_back( x );
    need_sort = true;
    return make_pair(v.end()-1,true);
  }

  size_t erase( kR k ) {
    iterator i = find(k);
    if( i != v.end() ) { v.erase(i); return 1; }
    else return 0;
  }

  void clear() { v.clear(); }
};
