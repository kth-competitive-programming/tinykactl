/* KTH ACM Contest Template Library
 *
 * tinystl/rotate
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By David Rydh
 */

#include "reverse.cpp"

template<class R>
void rotate(R first, R middle, R last) {
  if( first == middle || last == middle ) return;
  reverse( first, middle );
  reverse( middle, last );
  reverse( first, last );
}
