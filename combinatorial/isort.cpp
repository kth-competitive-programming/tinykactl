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
#include <algorithm>
#include "indexed_comparator.cpp"

// R, I are RandomAccessIterators to objects/int.
template<class R, class I, class C>
void isort( const R &array, int n, I indexlist, C comp ) {
  for( int i=0; i<n; i++ )
    indexlist[i] = i;
  sort( indexlist+0, indexlist+n, indexed_comparator<R,C>(array, comp) );
}

template<class R, class S>
void isort( const R &array, int n, S indexlist ) {
  isort( array, n, indexlist, less<typename iterator_traits<R>::value_type>());
}
