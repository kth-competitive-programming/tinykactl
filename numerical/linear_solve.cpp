/* KTH ACM Contest Template Library
 *
 * Linear equation solver/Solve Ax = b/Gaussian elimination with column pivoting
 *
 * Credit:
 *   Carl Friedrich Gauss  1+2+...+n = n*(n+1)/2
 *   Based on [Intro to Algorithms, pp. xx-yy,zz]
 *   Variation of [KTH.ACM.CTL. ff.cpp]
 *   Sketch by nn
 *   By Tomas Oppelstrup, tomaso@nada.kth.se
 *   Updated by xx
 *   Thanks to yy
 *   Greetings to hello world!
 *   Dedicated to Fredrik Niemelä
 */

// solve(n,m) solves Ax = b, A nxm matrix
// Needs: number A[N][M], b[NN], x[MM], where NN,N>=n, MM,M>=m //
// I don't know your conventions for matrices:
//     number *, number ** or vector<number>
// A, b, x are destroyed on exit. solve() returns 0 if the system
// has a unique solution, -1 if no solution exists, otherwise
// the number of free variables (ideal for 10109)
// The comments prints the matrix after each elimination step.
template<class number> int solve(int n, int m) {
  int *r = new int[n], *c = new int[m];
  int t, ii, i, j, k, rankdef = 0;
  number pivot;
  /*
    for(i = 0; i<n; i++) {
      for(j = 0; j<m; j++) { A[i][j].print(); printf("  "); }
      b[i].print();
      printf("\n");
    }
    printf("\n");
  */
  for(i = 0; i<n; i++) r[i] = i;
  for(i = 0; i<m; i++) c[i] = i;
  for(ii = 0; ii<n; ii++) {
    i = ii - rankdef;
    j = i;
    while(j < m && A[r[i]][c[j]] == 0) j++;
    if(j < m) {
      t = c[i]; c[i] = c[j]; c[j] = t;
      for(j = i+1; j<n; j++) {
	pivot = A[r[j]][c[i]] / A[r[i]][c[i]];
	for(k = i; k<m; k++)
	  A[r[j]][c[k]] -= pivot * A[r[i]][c[k]];
	b[r[j]] -= pivot * b[r[i]];
      }
    } else if(b[r[i]] != 0) {
      rankdef = -1;
      break;
    } else {
      rankdef++;
      t = r[i]; r[i] = r[n-rankdef]; r[n-rankdef] = t;
    }
    /*
    printf("pivot = "); pivot.print(); printf("\n");
    for(i = 0; i<n; i++) {
      for(j = 0; j<m; j++) { A[i][j].print(); printf("  "); }
      b[i].print();
      printf("\n");
    }
    printf("\n");
    */
  }
  /*  printf("Rank deficiency %d (n=%d m=%d)\n", rankdef, n, m); */
  if(rankdef >=0 ) {
    if(m > n)
      rankdef += m-n;
    else if(rankdef == n-m) {
      rankdef = 0;
      for(i = m-1; i>=0; i--) {
	for(j = i+1; j<m; j++)
	  b[r[i]] -= A[r[i]][c[j]] * b[r[j]];
	b[r[i]] /= A[r[i]][c[i]];
      }
      for(i = 0; i<m; i++)
	x[c[i]] = b[r[i]];
    }
  }
  delete[] c;
  delete[] r;
  return rankdef;
}
