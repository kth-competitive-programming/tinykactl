void matrix_inverse() {
  bool singular = false;
  double A[n][n];     // input
  double inv[n][n];
  int row[n], col[n];
  memset(inv, 0, sizeof(inv));
  
  for (int i = 0; i < n; ++i) {
    inv[i][i] = 1;
    row[i] = i;
    col[i] = i;
  }
  
  // forward pass:
  for (int i = 0; i < n; ++i) {
    int r = i, c = i;
    // find pivot
    /*
      for (int j = i; j < n; ++j)
      for (int k = i; k < n; ++k)
      if (fabs(A[row[j]][col[k]]) > fabs(A[row[r]][col[c]]))
      r = j, c = k;
    */
    // pivot found?
    if (fabs(A[row[r]][col[c]]) < 1e-12) {
      singular = true; break;
    }
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
        inv[row[j]][col[k]] -= f*inv[row[i]][col[k]];
    }
    // normalize row
    for (int j = i+1; j < n; ++j)
      A[row[i]][col[j]] /= v;
    for (int j = 0; j < n; ++j)
      inv[row[i]][col[j]] /= v;
    A[row[i]][col[i]] = 1;
  }

  // backward pass:
  for (int i = n-1; i > 0; --i)
    for (int j = i-1; j >= 0; --j) {
      double v = A[row[j]][col[i]];
      // don't care about A at this point, just eliminate inv backward
      for (int k = 0; k < n; ++k)
        inv[row[j]][col[k]] -= v*inv[row[i]][col[k]];
    }

  int decol[n];
  for (int i = 0; i < n; ++i)
    decol[col[i]] = i;
  
  // inv[row[decol[i]]][j] is element (i,j) of solution (unless singular)
}
