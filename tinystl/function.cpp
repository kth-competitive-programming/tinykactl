/* KTH ACM Contest Template Library
 *
 * tinystl/function objects
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By Mattias de Zalenski
 */

/*
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

template <class T> struct logical_and //: public binpred<T>
{ bool operator()(const T &x, const T &y) { return x && y; } };
template <class T> struct logical_or //: public binpred<T>
{ bool operator()(const T &x, const T &y) { return x || y; } };
template <class T> struct logical_not //: public unpred<T>
{ bool operator()(const T &x) { return !x; } };


/*
template <class P, class A = P::argument_type>
struct unary_negate : public unary_function<A, bool> {
  P p; explicit unary_negate(const P &x) : p(x) { }
  bool operator()(const A &x) const { return !p(x); }
};
template <class P>
inline unary_negate<P> not1(const P &p) { return unary_negate<P>(p); }

...
*/
