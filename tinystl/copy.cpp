/* KTH ACM Contest Template Library
 *
 * tinystl/copy
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By David Rydh
 */

#ifndef __TS_COPY__
#define __TS_COPY__

template<class R, class S>
S copy(R f, R l, S d) {
  while( f<l ) *d++ = *f++;
  return d;
}

template<class R, class S>
S copy_backward(R f, R l, S d) {
  while( f<l ) *--d = *--l;
  return d;
}

template<class R, class T>
void fill(R f, R l, const T &val) {
  while( f<l ) *f++ = val;
}

template<class R, class T>
void fill_n(R f, int n, const T &val) {
  while( n-- > 0 ) *f++ = val;
}

#endif
