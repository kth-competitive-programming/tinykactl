#include "Testplate.cpp"

#include <cstdio>
#include "../numerical/simplex.cpp"

void init() { }

// In: m n
//          a00  a01  ...  a0n
//     var1 a10  a11  ...  a1n
//     .    .    .    .      .
//     .    .    .     .     .
//     .    .    .      .    .
//     varm am0  am1  ...  amn

// Out:
//          a00 a01 ... a0n
//     var1 a10 a11 ... a1n
//     .    .       .     .
//     .    .        .    .
//     .    .         .   .
//     varm am0 am1 ... amn

template <class M, class V>
void print(M &a, V &var, int m, int n) {
  for (int i = 0; i <= m; ++i) {
    if (i > 0)
      printf("%1i", var[i]);
    else
      printf(" ");
    for (int j = 0; j <= n; ++j)
      printf(" %5.2f", a[i][j]);
    printf("\n");
  }
  printf("\n");
}

typedef vector<double> V;
typedef vector<V> M;
typedef vector<int> I;

bool solve(int P) {
  int m, n, artificial; cin >> m >> n >> artificial;
  int twophase = artificial > 0 ? 1 : 0;
  V v(n + artificial + 1);
  M a(m + 1 + twophase, v);
  I var(m + 1);
  for (int i = 0; i <= m; ++i) {
    if (i > 0)
      cin >> var[i];
    for (int j = 0; j <= n + artificial; ++j)
      cin >> a[i][j];
  }
  simplex_result r;
  if (twophase)
    r = twophase_simplex(a, var, m, n, artificial);
  else
    r = simplex(a, var, m, n);
  if (r == UNBOUNDED) printf("Unbounded!\n");
  if (r == NO_SOLUTION) printf("No solution!\n");
  print(a, var, m, n);
  return true;
};
