/* KTH ACM Contest Template Library
 *
 * Numerical problems/Linear Algebra/Integral Determinant
 *
 * Calculates determinant by using elementary operations to
 * transform matrix into an upper diagonal form.
 *
 * Credit:
 *   By David Rydh
 */

#include "euclid.cpp"

template< class T, int N >
T int_determinant( T m[N][N], int n ) {
  for( int c=0; c<n; c++ ) {
    for( int r=c; r<n; r++ ) {
      if( m[r][c] !=0 ) {
	if( r!=c ) {    	// Eliminate column c with row r
	  for( int j=0; j<n; j++ ) {
	    swap( m[c][j], m[r][j] );
	    m[r][j] = -m[r][j];
	  }
	}
	for( r++; r<n; r++ ) {
	  T x,y;
	  T d = euclid( m[c][c], m[r][c], x,y );
	  T x2 = -m[r][c]/d, y2 = m[c][c]/d;

	  for( int j=c; j<n; j++ ) {
	    T u = x*m[c][j]+y*m[r][j];
	    T v = x2*m[c][j]+y2*m[r][j];
	    m[c][j] = u;  m[r][j] = v;
	  }
	}
      }
    }
  }
  // Matrix is now in upper-diagonal form
  T det = 1;
  for( int i=0; i<n; i++ )
    det *= m[i][i];
  return det;
}
