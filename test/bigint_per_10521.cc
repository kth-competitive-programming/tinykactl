/* @JUDGE_ID:    ..  10521   C++ */

#include "../datastructures/numbers/bigint_per.cpp"

const enum {SIMPLE, FOR, WHILE} mode = WHILE;
const bool debug = false;

void init() {}

const bigint zero;
const bigint one = BigInt(1);

void gen_frac(bigint& n, bigint& m, bool neg) {
  bigint q;
  divmod(n, m, &q);
  if (neg && n != zero) {
    bigint tmp = n;
    q += one;
    (n = m) -= tmp;
  }
  if (neg && q != zero) cout << '-';
  cout << q;
  if (n != zero) {
    cout << "+1/{";
    gen_frac(m, n, false);
    cout << "}";
  }
}

bool solve(int P) {
  bool neg = false;
  bigint n, m;

  while (cin && isspace(cin.peek())) cin.get();
  if (cin && cin.peek() == '-') cout << '-', neg = !neg, cin.get();
  if (!(cin >> n)) return false;
  cout << n << "/";

  while (cin && isspace(cin.peek())) cin.get();
  if (cin && cin.peek() == '-') cout << '-', neg = !neg, cin.get();
  if (!(cin >> m)) return false;
  cout << m << " = ";

  gen_frac(n, m, neg);
  cout << endl;
  return true;
}

int main() {
  init();
  int n = mode == SIMPLE ? 1 : 1<<30;
  if (mode == FOR) cin >> n;
  for (int i = 0; i < n && solve(i); ++i);
  return 0;
}
