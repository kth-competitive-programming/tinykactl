/* KTH ACM Contest Template Library
 *
 * tinystl/sort
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By David Rydh
 */

template<class T, class C >
void sort(T *first, T *last, C c=less<T>() ) {
  sort( first, last, T(), c );
}

template<class R, class T>
T _pivot(R first, R last, const T &dummy ) {
  // Middle pivot
  return first[(last-first)/2];
  /*
  // Average pivot
  return (*first+*(last-1))/2;

  // 3-Median pivot
  T pivots[3] = { *first, *(last-1), first[(last-first)/2] };
  if( pivots[1] < pivots[0] ) swap( &pivots[0], &pivots[1] );
  if( pivots[2] < pivots[0] ) swap( &pivots[0], &pivots[2] );
  if( pivots[2] < pivots[1] ) swap( &pivots[1], &pivots[2] );
  return pivots[1];
  */
}

template<class R, class T, class C >
void sort(R first, R last, const T &dummy, C c=less<T>() ) {
  if( first == last || first+1 == last )
    return;
  T pivot = _pivot( first, last, dummy );

  // Partition
  R a = first, b = last-1;
  while( a<=b ) {
    while( c(*a,pivot) ) a++;
    while( c(pivot,*b) ) b--;
    if( a>=b ) break;
    swap( *a, *b );
    a++; b--;
  }
  // Divide & conquer
  sort( first, a, dummy, c );
  sort( b+1, last, dummy, c );
}
