void solve_linear_per() {
  double matr[N][N], rhs[N];      // input
  int rows[N], cols[N], undef[N];

  for (int i = 0; i < N; ++i) {
    rows[i] = i;
    cols[i] = i;
    undef[i] = false;
  }
  
  int rank = 0;
  for (int i = 0; i < N; rank = ++i) {
    int bestr = i, bestc = i;
    double v, bestv = abs(matr[rows[i]][cols[i]]);
    for (int r = i; r < N; ++r)
      for (int c = i; c < N; ++c)
	if ((v = abs(matr[rows[r]][cols[c]])) > bestv)
	  bestr = r, bestc = c, bestv = v;
    if (bestv < 1e-12) break;
    if (i != bestr) rows[i] ^= rows[bestr] ^= rows[i] ^= rows[bestr];
    if (i != bestc) cols[i] ^= cols[bestc] ^= cols[i] ^= cols[bestc];
    for (int j = i + 1; j < N; ++j) {
      double fac = matr[rows[j]][cols[i]] / matr[rows[i]][cols[i]];
      matr[rows[j]][cols[i]] = 0;
      for (int k = i + 1; k < N; ++k)
	matr[rows[j]][cols[k]] -= fac * matr[rows[i]][cols[k]];
      rhs[rows[j]] -= fac * rhs[rows[i]];
    }
  }

  for (int i = rank; i-- ; ) {
    rhs[rows[i]] /= matr[rows[i]][cols[i]];
    matr[rows[i]][cols[i]] = 1;
    for (int j = rank; j < N; ++j)
      if (abs(matr[rows[i]][cols[j]]) > 1e-12)
	undef[i] = true;
    for (int j = i - 1; j >= 0; --j) {
      if (undef[i] && abs(matr[rows[j]][cols[i]]) > 1e-12)
	undef[j] = true;
      else {
	rhs[rows[j]] -= matr[rows[j]][cols[i]] * rhs[rows[i]];
	matr[rows[j]][cols[i]] = 0;
      }
    }
  }

  int invrow[N];
  for (int i = 0; i < N; ++i)
    invrow[rows[i]] = i;
  for (int i = 0; i < N; ++i)
    if (invrow[i] >= rank || undef[invrow[i]])
      rhs[i] = -1;   // undefined
  
  int decol[N];
  for (int i = 0; i < n; ++i)
    decol[cols[i]] = i;

  // rhs[rows[decol[i]]] is element i of solution
}
