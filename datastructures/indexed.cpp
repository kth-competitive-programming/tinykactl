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

#include <functional>

template<class R, class I> // R is a random_access_iterator to a T-array
                           // I is a r_a_i to a const index-array
struct indexed {
  typedef typename iterator_traits<R>::value_type T;
  R array; I index;
  indexed( R a, I i ) : array(a), index(i) { }
  T &operator[]( int i ) { return array[index[i]]; }
  const T & operator[]( int i ) const { return array[index[i]]; }
};
