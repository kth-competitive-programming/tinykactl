/* KTH ACM Contest Template Library
 *
 * tinystl/stable_sort
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By David Rydh
 */

template<class T> void stable_sort(T *first, T *last)
{ stable_sort( first, last, first, T() ); }

template<class R>
void merge( R first, R middle, R last, R dest ) {
  R i = first, j = middle;

  while( i < middle || j < last ) {
    while( i < middle && (j==last || !(*j < *i)) ) *dest++ = *i++;
    while( j < last && (i==middle || *j < *i) ) *dest++ = *j++;
  }
}

template<class R, class T>
void stable_sort(R first, R last, R dest, const T &dummy ) {
  int l = last-first, hl = l/2;
  R middle = first + hl;

  if( l==0 ) return;
  else if( l==1 ) { *dest = *first; return; }
  else if( l==2 ) {
    if( *middle < *first ) swap(*first,*middle);
    *dest++ = *first;
    *dest++ = *middle;
    return;
  }

  if( dest == first ) {
    T *buf = new T[l], *buf_m = buf+hl, *buf_l = buf+l;

    stable_sort( first, middle, buf, dummy );
    stable_sort( middle, last, buf_m, dummy );
    merge( buf, buf_m, buf_l, first );
    delete[] buf;
  } else {
    stable_sort( first, middle, first, dummy );
    stable_sort( middle, last, middle, dummy );
    merge( first, middle, last, dest );
  }
}
