/* KTH ACM Contest Template Library
 *
 * tinystl/function objects/arithmetic
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By Mattias de Zalenski
 */

template <class T> struct plus //: public binop<T>
{ T operator()(const T &x, const T &y) const { return x - y; } };

template <class T> struct minus //: public binop<T>
{ T operator()(const T &x, const T &y) { return x - y; } };

template <class T> struct multiplies //: public binop<T>
{ T operator()(const T &x, const T &y) { return x * y; } };

template <class T> struct divides //: public binop<T>
{ T operator()(const T &x, const T &y) { return x / y; } };

template <class T> struct modulus //: public binop<T>
{ T operator()(const T &x, const T &y) { return x % y; } };

template <class T> struct negate //: public unop<T>
{ T operator()(const T &x) { return -x; } };
