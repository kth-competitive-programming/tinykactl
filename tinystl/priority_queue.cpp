/* KTH ACM Contest Template Library
 *
 * tinystl/priority_queue
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By David Rydh
 */

#include "base.cpp"
#include "comparisons.cpp"
#include "vector.cpp"

template<class T, class C=less<T> >
struct priority_queue : vector<T> {
  C c;
  priority_queue( const C &_c=C() ) : c(_c) {}

  // empty, size is inherited
  const T &top() const { return front(); }

  void push( const T &x ) { push_back(x); key_inc(end()-1); }
  void pop() { front() = back(); pop_back(); key_dec(begin()); }
  void key_inc( iterator i ) {
    while( i!=b ) {
      iterator j = b+(i-b-1)/2;
      if( !c(*j,*i) ) break;
      ::swap( *i, *j ); i = j;
    }
  }
  void key_dec( iterator i ) {
    while( i<end() ) {
      iterator l = b+(i-b)*2+1, r = l+1, exc = i;

      if( l<end() && c(*exc,*l) ) exc = l;
      if( r<end() && c(*exc,*r) ) exc = r;
      if( exc==i ) break;
      ::swap( *i, *exc ); i = exc;
    }
  }
};
