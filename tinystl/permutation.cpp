/* KTH ACM Contest Template Library
 *
 * tinystl/permutation
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By David Rydh
 */

#include "base.cpp"
#include "reverse.cpp"

template<class R>
bool next_permutation( R f, R l ) {
  if( l-f < 2 ) return false;

  R i,j;
  for( i=l-2, j=l-1; j!=f; j=i-- ) {
    if( *i < *j ) {
      R k = l;
      while( !(*i < *--k) ) ;
      swap( *i, *k );
      break;
    }
  }
  reverse( j, l );
  return (j!=f);
}

template<class R>
bool prev_permutation( R f, R l ) {
  if( l-f < 2 ) return false;

  R i,j;
  for( i=l-2, j=l-1; j!=f; j=i-- ) {
    if( *j < *i ) { // differs from next_permutations
      R k = l;
      while( !(*--k < *i) ) ; // differs from next_permutations
      swap( *i, *k );
      break;
    }
  }
  reverse( j, l );
  return (j!=f);
}
