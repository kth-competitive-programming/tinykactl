/* KTH ACM Contest Template Library
 *
 * Numerical/Data Structures/Polynom
 *
 * Credit:
 *   Isaac Newton
 *   By David Rydh
 */

#include <vector>

struct polynom {
  int n;
  vector<double> a;
  polynom( int _n ) : n(_n), a(n+1) {}

  // Calc value at x
  double operator()( double x ) const {
    double val = 0;

    for( int i=0; i<=n; i++ ) {
      val *= x;
      val += a[i];
    }
    return val;
  }

  // Calc derivative at x
  double deriv( double x ) const {
    double val = 0;

    for( int i=0; i<=n-1; i++ ) {
      val *= x;
      val += (n-i)*a[i];
    }
    return val;
  }

  // Divide this polynom with the factor (t-x) where x is a root...
  // The constant term is ignored (it should be zero but may be non-zero
  // due to rounding errors).
  void divroot( double x ) {
    double val = 0;

    for( int i=0; i<=n-1; i++ ) {
      val *= x;
      val += a[i];
      a[i] = val;
    }
    n--;
    a.resize(n+1);
  }
};
