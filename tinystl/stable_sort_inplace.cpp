/* KTH ACM Contest Template Library
 *
 * tinystl/inplace_stable_sort
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By David Rydh
 */

#include "rotate.cpp"
#include "binary_search.cpp"

template<class R>
void inplace_stable_sort(R first, R last ) {
  R middle = first + (last-first)/2;
  if( middle-first>1 ) inplace_stable_sort( first, middle );
  if( last-middle>1 ) inplace_stable_sort( middle, last );
  inplace_merge( first, middle, last, middle-first, last-middle );
}

template<class R>
void inplace_merge( R first, R middle, R last, int l1, int l2 ) {
  if( l1 == 0 || l2 == 0 ) return;
  if( l1+l2 == 2 ) {
    if( *middle < *first ) swap( *first, *middle );
    return;
  }
  R fc = first, sc = middle;
  int l11 = 0, l22 = 0;
  if( l1 > l2 ) {
    fc += (l11=l1/2);
    sc = lower_bound( middle, last, *fc );
    l22 = sc-middle;
  } else {
    sc += (l22=l2/2);
    fc = upper_bound( first, middle, *sc );
    l11 = fc-first;
  }
  rotate( fc, middle, sc );
  R new_middle = fc+(sc-middle);
  inplace_merge( first, fc, new_middle, l11, l22 );
  inplace_merge( new_middle, sc, last, l1-l11, l2-l22 );
}

