/* KTH ACM Contest Template Library
 *
 * tinystl/binary_search
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By David Rydh
 */

#ifndef __TS_BINARY_SEARCH__
#define __TS_BINARY_SEARCH__

#include "comparisons.cpp"

template<class F, class T, class C > // F is Forward-iterator
F lower_bound( F first, F last, const T &val, C c ) {
  while( first<last ) {
    F middle = first+(last-first)/2; // first<=middle<last

    if( !c(*middle,val) ) last = middle;
    else first = middle+1;
  }
  return first;
}

template<class F, class T, class C > // F is Forward-iterator
F upper_bound( F first, F last, const T &val, C c ) {
  while( first<last ) {
    F middle = first+(last-first)/2; // first<=middle<last

    if( c(val,*middle) ) last = middle;
    else first = middle+1;
  }
  return first;
}

template<class F, class T, class C > // F is Forward-iterator
bool binary_search( F first, F last, const T &val, C c ) {
  F x = lower_bound(first,last,val,c);
  return x != last && !c(val,*x);
}

template<class F, class T > F lower_bound( F first, F last, const T &val )
{ return lower_bound( first,last,val,less<T>() ); }
template<class F, class T > F upper_bound( F first, F last, const T &val )
{ return upper_bound( first,last,val,less<T>() ); }
template<class F, class T > F binary_search( F first, F last, const T &val )
{ return binary_search( first,last,val,less<T>() ); }

#endif
