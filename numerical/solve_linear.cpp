#define MAXS 100

const double NAN = 0.0/0.0;
const double EPS = 1e-12;

double A[MAXS][MAXS], b[MAXS], x[MAXS];

// Solves A*x = b, or as much of x as possible. Returns rank.
int solve_linear(int n) {
  int row[n], col[n], undef[n], invrow[n], invcol[n];

  for (int i = 0; i < n; ++i)
    row[i] = col[i] = i, undef[i] = false;
  
  int rank = 0;
  for (int i = 0; i < n; rank = ++i) {
    int br = i, bc = i;
    double v, bv = abs(A[row[i]][col[i]]);
    for (int r = i; r < n; ++r)
      for (int c = i; c < n; ++c)
	if ((v = abs(A[row[r]][col[c]])) > bestv)
	  br = r, bc = c, bv = v;
    if (bv < EPS) break;
    if (i != br) row[i] ^= row[br] ^= row[i] ^= row[br];
    if (i != bc) col[i] ^= col[bc] ^= col[i] ^= col[bc];
    for (int j = i + 1; j < n; ++j) {
      double fac = A[row[j]][col[i]] / bv;
      A[row[j]][col[i]] = 0;
      b[row[j]] -= fac * b[row[i]];
      for (int k = i + 1; k < n; ++k)
	A[row[j]][col[k]] -= fac * A[row[i]][col[k]];
    }
  }

  for (int i = rank; i-- ; ) {
    b[row[i]] /= A[row[i]][col[i]];
    A[row[i]][col[i]] = 1;
    for (int j = rank; j < n; ++j)
      if (abs(A[row[i]][col[j]]) > EPS)
	undef[i] = true;
    for (int j = i - 1; j >= 0; --j) {
      if (undef[i] && abs(A[row[j]][col[i]]) > EPS)
	undef[j] = true;
      else {
	b[row[j]] -= A[row[j]][col[i]] * b[row[i]];
	A[row[j]][col[i]] = 0;
      }
    }
  }

  for (int i = 0; i < n; ++i)
    invrow[row[i]] = i, invcol[col[i]] = i;
  for (int i = 0; i < n; ++i)
    if (invrow[i] >= rank || undef[invrow[i]])
      b[i] = NAN;   // undefined
  for (int i = 0; i < n; ++i)
    x[i] = b[row[invcol[i]]];
  return rank;
}
