/* KTH ACM Contest Template Library
 *
 * tinystl/reverse
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By David Rydh
 */

template<class R>
void reverse(R first, R last) {
  while( first < last )
    swap( *first++, *--last);
}
