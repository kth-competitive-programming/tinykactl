/* KTH ACM Contest Template Library
 *
 * tinystl/vector
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By David Rydh
 */

#include "copy.cpp"

template< class T >
struct vector {
  T *b; int n, a;

  typedef T value_type;
  typedef T *iterator;
  typedef const T *const_iterator;
  typedef vector S;

  vector( int _n=0, const T &val=T() ) : n(_n), a(_n), b(new T[_n]) {
    fill( b, b+n, val );
  }
  vector( const S &x ) : n(x.n), a(x.n), b(new T[x.n]) {
    copy(x.begin(),x.end(),begin());
  }
  ~vector() { delete[] b; }
  S &operator=( const S &x ) {
    resize(x.n); copy(x.begin(),x.end(),begin());
    return *this;
  }

  T *begin() { return b; }
  T *end() { return b+n; }
  const T *begin() const { return b; }
  const T *end() const { return b+n; }
  int size() { return n; }

  T &front() { return b[0]; }
  const T &front() const { return b[0]; }
  T &back() { return b[n-1]; }
  const T &back() const { return b[n-1]; }

  T &operator[](int k) { return b[k]; }
  const T &operator[](int k) const { return b[k]; }

  void push_back(const T &v) { resize(n+1); b[n-1]=v; }
  void pop_back() { n--; }
  T *insert( T *pos, const T &v ) { return insert(pos,1,v); }
  T *insert( T *pos, int num, const T &v ) {
    int off = pos-b;
    resize( n+num );
    copy_backward( b+off, b+n-num, b+n );
    fill_n( b+off, num, v );
    return b+off;
  }
  T *erase( T *pos ) { copy(pos+1,end(),pos); n--; return pos; }
  T *erase( T *f, T *l ) { copy(l,end(),f); n-=(l-f); return f; }

  void clear() { resize(0); }
  void reserve( int na ) {
    if( na>a ) {
      T *bn = new T[a=na];
      copy( b, b+n, bn );
      delete[] b;
      b = bn;
    }
  }
  void resize( int ns, const T &v=T() ) {
    if( ns>a ) reserve( 2*ns );
    while( n<ns ) b[n++] = v;
    n = ns;
  }

  void swap( S &x ) { swap(b,x.b); swap(n,x.n); swap(a,x.a); }
};

template<class T>
inline void swap(vector<T> &x, vector<T> &y) { x.swap(y); }
