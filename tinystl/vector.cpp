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

  vector( int _n=0, const T &val=T() ) {
    n = a = _n;
    b = new T[a];
    fill( b, b+n, val );
  }
  ~vector() { delete b; }
  vector<T> &operator=( const &vector<T> x ) {
    resize(x.n); copy(x.begin(),x.end(),begin());
    return this;
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

  void push_back(const T &v) { insert( end(), v ); }
  void pop_back() { n--; }
  T *insert( T *pos, const T &v ) { return insert(pos,1,v); }
  T *insert( T *pos, int num, const T &v ) {
    int off = pos-b;
    resize( n+num );
    copy_backward( b+off, b+n-num, b+n );
    fill( b+off, num, v );
    return b+off;
  }
  T *erase( T *pos ) { copy(pos+1,end(),pos); n--; return pos; }
  T *erase( T *f, T *l ) { copy(l,end(),f); n-=(l-f); return f; }

  void clear() { resize(0); }
  void resize( int ns, const T &v=T() ) {
    if( ns<=n ) n=ns;
    else {
      if( ns>a ) {
	T *bn = new T[a=2*ns];
	copy( b, b+n, bn );
	delete[] b;
	b = bn;	a = 2*ns;
      }
      while( n<ns ) b[n++] = v;
    }
  }
  void swap( vector<T> &x ) { swap(b,x.b); swap(n,x.n); swap(a,x.a); }
};

template<class T>
inline void swap(vector<T> &x, vector<T> &y) { x.swap(y); }
