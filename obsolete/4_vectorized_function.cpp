#if defined(__BORLANDC__) || __GLIBC__ < 3
#include <iterator.h>
#else
#include <backward/iterator.h>
#endif

template <class T>
struct fn_traits { typedef typename T::return_type return_type; };
template <class T, class A>
struct fn_traits<T (*)(A)> { typedef T return_type; };


template< class T >
class fn_iter : public random_access_iterator<int, int> {
  T    fn;
  int  off;

public:
  fn_iter() : fn((T)0), off(0) {}
  fn_iter( T _fn, int _off ) : fn(_fn), off(_off) {}

  typename fn_traits<T>::return_type operator*() { return fn(off); }
  fn_iter<T> &operator++() { off++; return *this; }
  fn_iter<T> &operator--() { off--; return *this; }
  fn_iter<T> &operator+=( int d ) { off+=d; return *this; }
  fn_iter<T> &operator-=( int d ) { off+=d; return *this; }
  int operator-( const fn_iter<T> &x ) { return off-x.off; }
  /*
  bool operator==( const fn_iter<T> &x ) { return off==x.off; }
  */

  int offset() { return off; }
};

template<class T>
fn_iter<T> make_fn_iter( T f, int off ) { return fn_iter<T>(f,off); }



template< class T >
class vectorized_fn {
  const int lower, upper;
  const T   fun;

public:
  vectorized_fn( int low, int upp, T f ) :
    lower(low), upper(upp), fun(f) {}

  fn_iter<T> begin() const { return fn_iter<T>(lower,fun); }
  fn_iter<T> end() const { return fn_iter<T>(upper,fun); }

  operator fn_iter<T>() { return begin(); }
};
