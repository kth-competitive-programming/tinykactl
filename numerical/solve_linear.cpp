/* KTH ACM Contest Template Library
 *
 * Numerical problems/Linear Algebra/Solve Ax=b
 *
 * Credit:
 *   Carl Friedrich Gauss
 *   By David Rydh
 */

template< class T, int N >
int solve_linear( T A[N][N], T x[N], T b[N], int nR, int nC ) {
  bool proc[N] = {false};

  for( int c=0; c<nC; c++ ) {
    for( int r=0; r<nR; r++ ) {
      if( proc[r] ) continue;

//    if( abs(A[r][c]) >= 1e-8 ) { // if T=double
      if( A[r][c] != 0 ) {
	// Eliminate column c using row r
	proc[r] = true;

	T f = A[r][c];
	for( int j=0; j<nC; j++ )
	  A[r][j] /= f;
	b[r] /= f;

	for( int i=0; i<nR; i++ ) {
	  if( i==r ) continue;
	  f = A[i][c];
	  for( int j=0; j<nC; j++ )
	    A[i][j] -= A[r][j]*f;
	  b[i] -= b[r]*f;
	}
	break;
      }
    }
  }

  int nFree = nC;

  for( int r=0; r<nR; r++ ) {
    if( !proc[r] ) {
      if( b[r] != 0 )
	return -1;
    } else {
      for( int c=0; c<nC; c++ ) {
//      if( abs(A[r][c]) >= 1e-8 ) { // if T=double
	if( A[r][c] != 0 ) {
	  x[c] = b[r];
	  break;
	}
      }
      nFree --;
    }
  }
  return nFree;
}
