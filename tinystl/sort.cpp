/* KTH ACM Contest Template Library
 *
 * tinystl/sort
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By David Rydh
 */

template<class T>
void sort(T *first, T *last ) {
  sort( first, last, T() );
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

template<class R, class T>
void sort(R first, R last, const T &dummy ) {
  if( first == last || first+1 == last )
    return;
  T pivot = _pivot( first, last, dummy );

  // Partition
  R a = first, b = last-1;
  while( a<=b ) {
    while( *a < pivot ) a++;
    while( pivot < *b ) b--;
    if( a>=b ) break;
    swap( *a, *b );
    a++; b--;
  }
  // Divide & conquer
  sort( first, a );
  sort( b+1, last );
}
