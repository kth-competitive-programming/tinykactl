/* KTH ACM Contest Template Library
 *
 * tinystl/function objects/comparisons
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By Mattias de Zalenski
 */

template <class T> struct equal_to //: public binpred<T>
{ bool operator()(const T &x, const T &y) { return x == y; } };

template <class T> struct not_equal_to //: public binpred<T>
{ bool operator()(const T &x, const T &y) { return x!=y; } };

template <class T> struct greater //: public binpred<T>
{ bool operator()(const T &x, const T &y) { return x > y; } };

template <class T> struct less //: public binpred<T>
{ bool operator()(const T &x, const T &y) { return x < y; } };

template <class T> struct greater_equal //: public binpred<T>
{ bool operator()(const T &x, const T &y) { return x>=y; } };

template <class T> struct less_equal //: public binpred<T>
{ bool operator()(const T &x, const T &y) { return x <= y; } };
