/* KTH ACM Contest Template Library
 *
 * Numerical problems/Linear Algebra/Determinant
 *
 * Calculates determinant by using elementary operations to
 * transform matrix into an upper diagonal form.
 *
 * Credit:
 *   By David Rydh
 */

template< int N >
double determinant( double m[N][N], int n ) {
  for( int c=0; c<n; c++ ) {
    for( int r=c; r<n; r++ ) {
      if( abs(m[r][c]) >= 1e-8 ) {
	if( r!=c ) {	  // Eliminate column c with row r
	  for( int j=0; j<n; j++ ) {
	    swap( m[c][j], m[r][j] );
	    m[r][j] = -m[r][j];
	  }
	}
	for( r++; r<n; r++ ) {
	  double mul = m[r][c]/m[c][c];
          for( int j=0; j<n; j++ )
            m[r][j] -= m[c][j]*mul;
	}
      }
    }
  }
  // Matrix is now in upper-diagonal form
  double det = 1;
  for( int i=0; i<n; i++ )
    det *= m[i][i];
  return det;
}
