/* KTH ACM Contest Template Library
 *
 * tinystl/list
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By David Rydh
 */

template<class T>
struct list_node {
  typedef list_node S;
  T x;
  S *pred, *succ;
  list_node(const T &_x=T()) : x(_x) { link(this); }
  void link(S *y) { succ = y; y->pred=this; }
};

template<class T, class TR, class TP>
struct list_iterator {
  typedef list_iterator S;
  typedef T value_type;
  typedef list_node<T> TN;

  TN *e;
  list_iterator(TN *_e=0) : e(_e) {}
  list_iterator(const S &x) : e(x.e) {}
  S &operator++() { e = e->succ; return *this; }
  S &operator--() { e = e->pred; return *this; }
  S operator++(int) { S t(e); e=e->succ; return t; }
  S operator--(int) { S t(e); e=e->pred; return t; }
  bool operator==(const S&y) const { return e==y.e; }
  bool operator!=(const S&y) const { return e!=y.e; }
  TR operator*() const { return e->x; }
  TP operator->() const { return &(e->x); }
  void link(const S &y) { e->link(y.e); }
};

template<class T>
struct list {
  typedef T value_type;
  typedef list_iterator<T,T&,T*> iterator;
  typedef list_iterator<T,const T&, const T*> const_iterator;
  typedef list_node<T> TN;
  typedef list S;

  TN *node;

  list() { node = new TN(); }
  list(const S&x) { node = new TN(); insert(begin(),x.begin(),x.end()); }
  ~list() { clear(); }

  S &operator=(const S&x) {
    clear(); insert(begin(),x.begin(),x.end());
    return *this;
  }

  iterator begin() { return node->succ; }
  const_iterator begin() const { return node->succ; }
  iterator end() { return node; }
  const_iterator end() const { return node; }

  bool empty() const { return node->succ == node; }
  T& front() { return *begin(); }
  const T& front() const { return *begin(); }
  T& back() { return *(--end()); }
  const T& back() const { return *(--end()); }

  void swap( const S&x ) { swap(node,x.node); }
  iterator insert( iterator p, const T &val=T() ) { // insert BEFORE p
    iterator x = new TN(val);
    iterator y = p; --y;
    y.link(x); x.link(p);
    return x;
  }
  void insert( iterator p, const_iterator b, const_iterator e ) {
    while( b!=e ) { insert(p,*b); ++b; }
  }
  iterator erase( iterator p ) {
    iterator x=p, y=p; --x; ++y;
    x.link(y); delete p.e;
    return y;
  }

  void push_front( const T&val=T() ) { insert(begin(),val); }
  void push_back( const T&val=T() ) { insert(end(),val); }
  void pop_front() { erase(begin()); }
  void pop_back() { erase(--end()); }
  void clear() { while( !empty() ) pop_front(); }

  void splice(iterator p, S &l) { // insert BEFORE p
    if( !l.empty() ) splice(p,l,l.begin(),l.end());
  }
  void splice(iterator p, S &l, iterator i) {
    iterator j=i; ++j;
    if( p!=i && p!=j ) splice(p,l,i,j);
  }
  void splice(iterator p, S &, iterator i, iterator j) {
    if( i==j || p==j ) return;
    iterator x=i, y=j, z=p; --x; --y; --z;
    x.link(j); y.link(p); z.link(i);
  }
};
