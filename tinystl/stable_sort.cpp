/* KTH ACM Contest Template Library
 *
 * tinystl/stable_sort
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By David Rydh
 */

template<class T>
void stable_sort(T *first, T *last) {
  stable_sort( first, last, first, T() );
}

template<class R>
void merge( R first, R middle, R last, R dest ) {
  R i = first, j = middle;

  while( i < middle || j < last ) {
    while( i < middle && (j==last || *i < *j) ) *dest++ = *i++;
    while( j < last && (i==middle || *j < *i) ) *dest++ = *j++;
  }
}

template<class R, class T>
void stable_sort(R first, R last, R dest, const T &dummy ) {
  R middle = first + (last-first)/2;

  if( dest == first ) {
    T *buf = new T[last-first];
    T *buf_m = buf+(middle-first);
    T *buf_l = buf+(last-first);

    stable_sort( first, middle, buf, dummy );
    stable_sort( middle, last, buf_m, dummy );
    merge( buf, buf_m, buf_l, first );
  } else {
    stable_sort( first, middle, first, dummy );
    stable_sort( middle, last, middle, dummy );
    merge( first, middle, last, dest );
  }
}
