/* KTH ACM Contest Template Library
 *
 * tinystl/function objects/comparisons
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By Mattias de Zalenski
 */

#ifndef __TS_COMPARISONS__
#define __TS_COMPARISONS__

template <class T> struct equal_to //: public binpred<T>
{ bool operator()(const T &x, const T &y) const { return x == y; } };

template <class T> struct not_equal_to //: public binpred<T>
{ bool operator()(const T &x, const T &y) const { return x!=y; } };

template <class T> struct greater //: public binpred<T>
{ bool operator()(const T &x, const T &y) const { return x > y; } };

template <class T> struct less //: public binpred<T>
{ bool operator()(const T &x, const T &y) const { return x < y; } };

template <class T> struct greater_equal //: public binpred<T>
{ bool operator()(const T &x, const T &y) const { return x>=y; } };

template <class T> struct less_equal //: public binpred<T>
{ bool operator()(const T &x, const T &y) const { return x <= y; } };

#endif
