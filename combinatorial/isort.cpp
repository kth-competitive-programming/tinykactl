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
#include <iterator>
#include <functional>
#include "indexed_comparator.cpp"

// V is a datastructure (vector) or RAI.
// I is RandomAccessIterator to objects/int.
template<class V, class I, class C>
void isort( const V &array, int n, I indexlist, C comp ) {
  for( int i=0; i<n; i++ )
    indexlist[i] = i;
  sort( indexlist+0, indexlist+n, indexed_comparator<V,C>(array, comp) );
}

template<class V, class I>
void isort( const V &array, int n, I indexlist ) {
  isort( array, n, indexlist, less<typename iterator_traits<V>::value_type>());
}
