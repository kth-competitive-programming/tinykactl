/* KTH ACM Contest Template Library
 *
 * tinystl/base (parts of algobase)
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By Mattias de Zalenski
 */

#ifndef __TS_BASE__
#define __TS_BASE__

template <class T>
inline void swap(T &a, T &b) { T t = a; a = b; b = t; }
//inline void swap(int &a, int &b) { a ^= b ^= a ^= b; }

template <class T> const T &min(const T &a, const T &b) { return b<a?b:a; }
template <class T> const T &max(const T &a, const T &b) { return a<b?b:a; }

#endif
