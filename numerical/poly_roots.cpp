/* KTH ACM Contest Template Library
 *
 * Numerical/Optimization/Roots of Polynomials
 *
 * Credit:
 *   Isaac Newton
 *   By David Rydh
 */

#include <cmath>

#include "polynom.cpp"

template< class T >
double find_root_newton( double xmin, const T &calc, double eps=1e-5 )
{
  double x, newx;

  newx = xmin;
  do {
    x = newx;

    double xval = calc(x);
    newx = x - xval/calc.deriv(x);
  } while( fabs(x-newx) > eps );

  return newx;
}


void find_roots( const polynom &p, double xmin, vector<double> &roots )
{
  polynom p2 = p;
  double root;

  // Find roots repeatedly from the left.
  // No double-roots are allowed.
  while( p2.n > 0 ) {
    root = find_root_newton( xmin, p2 );
    roots.push_back( root );
    p2.divroot( root );
    xmin = root;
  }
}
