/* KTH ACM Contest Template Library
 *
 * tinystl/binary_search
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By David Rydh
 */

template<class F, class T> // F is Forward-iterator
F lower_bound(F first, F last, const T &val ) {
  while( first<last ) {
    F middle = first+(last-first)/2; // first<=middle<last

    if( !(*middle < val) ) last = middle;
    else first = middle+1;
  }
  return first;
}

template<class F, class T> // F is Forward-iterator
F upper_bound(F first, F last, const T &val ) {
  while( first<last ) {
    F middle = first+(last-first)/2; // first<=middle<last

    if( *middle > val ) last = middle;
    else first = middle+1;
  }
  return first;
}

template<class F, class T> // F is Forward-iterator
bool binary_search( F first, F last, const T &val ) {
  F x = lower_bound(first,last,val);
  returnx != last && !(val < *x);
}
