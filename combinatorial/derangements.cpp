#include <cstring> /* for mem... */

template <class T, int N>
struct derangements {
  T dgen[N][N], choose[N][N], fac[N];
  derangements() {
    fac[0] = choose[0][0] = 1;
    memset(dgen, 0, sizeof(dgen)); 
    for (int m = 1; m < N; ++m) {
      fac[m] = fac[m-1] * m;
      choose[m][0] = choose[m][m] = 1;
      for (int k = 1; k < m; ++k) {
	choose[m][k] = choose[m-1][k-1] + choose[m-1][k];
      }
    }
  }
  T DGen(int n, int k) {
    T ans = 0;
    if (dgen[n][k]) return dgen[n][k];
    for (int i = 0; i <= k; ++i) {
      T t = choose[k][i] * fac[n-i];
      if (i & 1) ans -= t;
      else ans += t;
    }
    return dgen[n][k] = ans;
  }
  void generate(int n, T idx, int *res) {
    int vals[N];
    for (int i = 0; i < n; ++i) vals[i] = i;
    for (int i = 0; i < n; ++i) {
      int j, k = 0, m = n - i;
      for (j = 0; j < m; ++j)
	if (vals[j] > i) ++k;
      for (j = 0; j < m; ++j) {
	T l = 0;
	if (vals[j] > i)      l = DGen(m-1, k-1);
	else if (vals[j] < i) l = DGen(m-1, k);
	if (idx <= l) break;
	idx -= l;
      }
      res[i] = vals[j];
      memmove(vals + j, vals + j + 1, sizeof(int)*(m-j-1));
    }
  }
};
