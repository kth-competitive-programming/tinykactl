/* KTH ACM Contest Template Library
 *
 * tinystl/function objects
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By Mattias de Zalenski
 */

#ifndef __TS_FUNCTION__
#define __TS_FUNCTION__

//argument_type and result_type typedefs are seldom used.
template <class A, class R>
struct unary_function {
  typedef A argument_type;
  typedef R result_type;
};

template <class A1, class A2, class R>
struct binary_function {
  typedef A1 first_argument_type;
  typedef A2 second_argument_type;
  typedef R result_type;
};

// non-standard shorthand:
template <class T> struct binop : public binary_function<T, T, T> { };
template <class T> struct unop : public unary_function<T, T> { };
template <class T> struct binpred : public binary_function<T, T, bool> { };
template <class T> struct unpred : public unary_function<T, bool> { };

#include "arithmetic.cpp"
#include "comparisons.cpp"
#include "logical.cpp"

/* // Function Adaptors

// Negators, binders, pointers to functions
template <class P, class A = P::argument_type>
struct unary_negate : public unary_function<A, bool> {
  P p; explicit unary_negate(const P &x) : p(x) { }
  bool operator()(const A &x) const { return !p(x); }
};
template <class P>
inline unary_negate<P> not1(const P &p) { return unary_negate<P>(p); }

... not2, bind1st, bind2nd,
pointer_to_unary_function, pointer_to_binary_function
*/

#endif
