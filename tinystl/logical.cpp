/* KTH ACM Contest Template Library
 *
 * tinystl/function objects
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By Mattias de Zalenski
 */

template <class T> struct logical_and //: public binpred<T>
{ bool operator()(const T &x, const T &y) const { return x && y; } };

template <class T> struct logical_or //: public binpred<T>
{ bool operator()(const T &x, const T &y) const { return x || y; } };

template <class T> struct logical_not //: public unpred<T>
{ bool operator()(const T &x) const { return !x; } };
