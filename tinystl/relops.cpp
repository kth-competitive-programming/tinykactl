/* KTH ACM Contest Template Library
 *
 * tinystl/relops
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By Mattias de Zalenski
 */

template <class T>
inline bool operator!=(const T &x, const T &y) { return !(x == y); }
template <class T>
inline bool operator>(const T &x, const T &y) { return y < x; }
template <class T>
inline bool operator<=(const T &x, const T &y) { return !(y < x); }
template <class T>
inline bool operator>=(const T &x, const T &y) { return !(x < y); }
