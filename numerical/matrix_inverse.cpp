#define MAXS 100

const double EPS = 1e-12;
double A[MAXS][MAXS]

/* Invert matrix A.  Result is stored in A. */
bool matrix_inverse(int n) {
  bool singular = false;
  int row[MAXS], col[MAXS];
  double tmp[MAXS][MAXS] ;
  memset(tmp, 0, sizeof(tmp));
  
  for (int i = 0; i < n; ++i)
    tmp[i][i] = 1, row[i] = col[i] = i;
  
  // forward pass:
  for (int i = 0; i < n; ++i) {
    int r = i, c = i;
    // find pivot
    for (int j = i; j < n; ++j)
      for (int k = i; k < n; ++k)
	if (fabs(A[row[j]][col[k]]) > fabs(A[row[r]][col[c]]))
	  r = j, c = k;
    // pivot found?
    if (fabs(A[row[r]][col[c]]) < EPS)
      return false; // if singular
    // pivot
    if (i != r) row[i] ^= row[r] ^= row[i] ^= row[r];
    if (i != c) col[i] ^= col[c] ^= col[i] ^= col[c];
    // eliminate forward
    double v = A[row[i]][col[i]];
    for (int j = i+1; j < n; ++j) {
      double f = A[row[j]][col[i]] / v;
      A[row[j]][col[i]] = 0;
      for (int k = i+1; k < n; ++k)
        A[row[j]][col[k]] -= f*A[row[i]][col[k]];
      for (int k = 0; k < n; ++k)
        tmp[row[j]][col[k]] -= f*tmp[row[i]][col[k]];
    }
    // normalize row
    for (int j = i+1; j < n; ++j)
      A[row[i]][col[j]] /= v;
    for (int j = 0; j < n; ++j)
      tmp[row[i]][col[j]] /= v;
    A[row[i]][col[i]] = 1;
  }

  // backward pass:
  for (int i = n-1; i > 0; --i)
    for (int j = i-1; j >= 0; --j) {
      double v = A[row[j]][col[i]];
      // don't care about A at this point, just eliminate tmp backward
      for (int k = 0; k < n; ++k)
        tmp[row[j]][col[k]] -= v*tmp[row[i]][col[k]];
    }
  
  int invcol[n];
  for (int i = 0; i < n; ++i)
    invcol[col[i]] = i;
  
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      A[i][j] = tmp[row[invcol[i]]][j];
  return true;
}
