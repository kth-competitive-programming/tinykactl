/* KTH ACM Contest Template Library
 *
 * tinystl/deque
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By David Rydh
 */

const int _deque_node_size = 512;

template< class T, class TR, class TP >
struct deque_iter {
  typedef deque_iter<T,T&,T*> iterator;
  typedef deque_iter<T,const T&, const T*> const_iterator;
  typedef T value_type;
  typedef TR reference;
  typedef TP pointer;
  typedef deque_iter S; // self

  T *first, *last, *cur;
  T **nd;
  const int node_size = _deque_node_size;

  deque_iter( T *_x, T **_nd) : cur(_x) { set_node(_nd); }
  deque_iter() : cur(0),first(0),last(0),nd(0) {}
  deque_iter( const iterator & x) : cur(x.cur) { set_map(x.nd); }
  void set_map( T **_nd ) { nd = _nd; first = *_nd; end = first+node_size; }

  reference operator*() const { return *cur; }
  pointer operator->() const { return cur; }

  int operator-(const S &x) const {
    return node_size*(nd-x.nd-1)+(cur-first)+(x.last-x.cur);
  }

  S & operator++() {
    if( ++cur == last ) {
      set_node( nd+1 );
      cur = first;
    }
    return *this; 
  }
  S & operator--() {
    if( cur == first ) {
      set_node( nd-1 );
      cur = last;
    }
    --cur;
    return *this;
  }

  S operator++(int) { S tmp = *this; ++*this; return tmp; }
  S operator--(int) { S tmp = *this; --*this; return tmp; }

  S & operator+=( int n ) {
    n += (cur-first);
    if( n>=node_size ) { set_node( nd+n/node_size ); n %= node_size; }
    if( n<0 ) { set_node( nd-(-n-1)/node_size-1 ); n = n%node_size+node_size; }
    cur = first+n;
    return *this;
  }
  S & operator-=( int n) { return *this += -n; }
   S operator+( int n) const { S tmp = *this; return tmp += n; }
  S operator-( int n) const { S tmp = *this; return tmp -= n; }

  reference operator[]( int n) const { return *(*this + n); }

  bool operator==(const S& x) const { return cur == x.cur; }
  bool operator!=(const S& x) const { return cur != x.cur; }
  bool operator<(const S& x) const { return nd==x.nd ? cur<x.cur : m<x.m; }
  bool operator>(const S& x) const  { return x < *this; }
  bool operator<=(const S& x) const { return !(x < *this); }
  bool operator>=(const S& x) const { return !(*this < x); }
};

template<class T>
struct deque {
  typedef deque_iter<T,T&,T*> iterator;
  typedef deque_iter<T,const T&,const T*> const_iterator;

  const int node_size = _deque_node_size;
  T **map;
  int nodes;
  iterator b, e;

  deque( int n=0 ) : b(), e() { init_map(n); }
  ~deque() {}

  void init_map( int n ) {
    nodes = n/node_size+1;
    ...
  }
};
