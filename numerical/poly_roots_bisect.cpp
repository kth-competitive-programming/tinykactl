/* KTH ACM Contest Template Library
 *
 * Numerical/Optimization/Roots of Polynomials
 *
 * Split interval into N sign-changing. Then use Newton's method
 * (with bisective fall-back) or a simple bisective method.
 *
 * Credit:
 *   Isaac Newton
 *   By David Rydh
 */

#include <cmath>

#include "polynom.cpp"

template< class T >
double find_root_newton_bisect( double x1, double x2, const T &calc,
				double eps=1e-5 )
{
  bool p1 = (calc(x1)>0);
  bool p2 = (calc(x2)>0);
  double x, newx;

  // assertion: p1 != p2, i.e. sign-changing interval

  newx = (x1+x2)/2;
  do {
    x = newx;

    double xval = calc(x);
    bool pm = (xval>0);

    if( p1==pm )
      x1 = x;
    else if( p2==pm )
      x2 = x;

    newx = x - xval/calc.deriv(x);
    if( newx<x1 || newx>x2 )
      newx = (x1+x2)/2;
  } while( fabs(x-newx) > eps );

  return newx;
}

template< class T >
double find_root_bisect( double x1, double x2, const T &calc, double eps=1e-5 )
{
  bool p1 = (calc(x1)>0);
  bool p2 = (calc(x2)>0);

  // assertion: p1 != p2, i.e. sign-changing interval

  while( x2-x1 > eps ) {
    double xm = (x1+x2)/2;
    bool pm = (calc(xm)>0);

    if( p1==pm )
      x1 = xm;
    else if( p2==pm )
      x2 = xm;
    else
      return xm;
  }

  return (x1+x2)/2;
}

bool find_roots( const polynom &p, double xmin, double xmax,
		 vector<double> &roots )
{
  int nRoots;
  double step;

  roots.resize( p.n );

  // Find p.n sign-changing intervals
  for( int nInter = 8; ; nInter *= 10 ) {
    double lastVal = p(xmin);
    double lastX = xmin;

    step = (xmax-xmin)/nInter;
    nRoots = 0;

    for( int i=0; i<nInter; i++ ) {
      double x = lastX+step;
      double val = p(x);

      if( lastVal < 0 && val > 0 || lastVal > 0 && val < 0 )
	roots[nRoots++] = lastX;
      lastVal = val;
      lastX = x;
    }
    if( nRoots >= p.n )
      break;
  }
  if( nRoots != p.n )
    return false;

  for( int i=0; i<p.n; i++ )
    //    roots[i] = find_root_newton_bisect(roots[i], roots[i]+step, p);
    roots[i] = find_root_bisect(roots[i], roots[i]+step, p);

  return true;
}

