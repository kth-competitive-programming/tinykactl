/*****************************************************************************
 * 
 * General1: class indexed_comparator, indexed, function isort
 * ===========================================================
 *
 * ------------------------------------------------------------------------- *
 *
 * NADA acmlib (10 March 2002)
 * Templates for KTH-NADA, Ballons'R'Us, ACM 2001-2002
 *   Swedish competition, Link?ping 6 Oct 2001
 *   Revised for SWERC, Portu, Portugal 17 Nov 2001
 *   Revised for World Finals, Honolulu, 23 Mar 2002
 *   David Rydh, Mattias de Zalenski, Fredrik Niemel?
 *
 *****************************************************************************/

#ifndef INDEXED_CPP
#define INDEXED_CPP

#include <algorithm>
#include <functional>


template<class V, class Comp >
class indexed_comparator {
  const V &array;
  const Comp &c;

public:
  indexed_comparator( const V &a, const Comp _c ) : array(a), c(_c) {}

  bool operator()( const int a, const int b ) const {
    return c(array[a], array[b]);
  }
};


template<class R, class S> // R is a random_access_iterator to a T-array
                           // S is a r_a_i to a const index-array
class indexed {
  typedef typename iterator_traits<R>::value_type T;

  R    array;
  S    index;

public:
  indexed( R a, S i ) : array(a), index(i) {}

  T &operator[]( int i ) { return array[index[i]]; }
  const T & operator[]( int i ) const { return array[index[i]]; }
};


// R, S are RandomAccessIterators to objects/int.
template<class R, class S, class C>
void isort( const R &array, int n, S indexlist, C comp ) {
  for( int i=0; i<n; i++ )
    indexlist[i] = i;

  sort( indexlist+0, indexlist+n, indexed_comparator<R,C>(array, comp) );
}

template<class R, class S>
void isort( const R &array, int n, S indexlist ) {
  isort( array, n, indexlist, less<iterator_traits<R>::value_type>() );
}

#endif
