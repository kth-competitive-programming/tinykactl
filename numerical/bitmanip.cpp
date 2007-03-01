typedef unsigned int uint;

int lowest_bit(int x) { return x & -x; }

bool ispow2(uint x) { return (x & x - 1) == 0; }

uint nlpow2(uint x) { // power of two round up
  if (!x--) return 1;
  for (int i = 0; i < 5; ++i)
    x |= x >> (1 << i);
  return ++x;
}

// next higher number with the same number of bits set
uint nexthi_same_count_ones(uint a) {
  uint c = (a & -a), r = a+c;
  return (((r ^ a) >> 2) / c) | r;
}

const unsigned int b[] = {0x2, 0xC, 0xF0, 0xFF00, 0xFFFF0000};

uint log2(uint v) {
  uint c = 0;
  for (int i = 4; i >= 0; i--)
    if (v & b[i])
      v >>= (1 << i), c |= (1 << i);
  return c;
}

template <class T> // bit count, use with bitop
void bitcount(T &x, int s, T m) { x = (x >> s & m) + (x & m); }
// Use __builtin_popcount or __builtin_popcountll if available.

template <class T> // bit reversal, use with bitop
void revbits(int &x, int s, int m) { x = x >> s & m | (x & m) << s; }

template <class F> int bitop(int x, F _fun) {
  _fun(x, 1, 0x55555555);
  _fun(x, 2, 0x33333333);
  _fun(x, 4, 0x0f0f0f0f);
  _fun(x, 8, 0x00ff00ff);
  _fun(x,16, 0x0000ffff);
  return x;
}

template <class F> long long bitop(long long x, F _fun) {
  _fun(x, 1, 0x5555555555555555ll);
  _fun(x, 2, 0x3333333333333333ll);
  _fun(x, 4, 0x0f0f0f0f0f0f0f0fll);
  _fun(x, 8, 0x00ff00ff00ff00ffll);
  _fun(x,16, 0x0000ffff0000ffffll);
  _fun(x,32, 0x00000000ffffffffll);
  return x;
}
