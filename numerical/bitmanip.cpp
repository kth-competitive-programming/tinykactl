// lowest bit
int lowest(int x) { return x & -x; }

// sign
int sign(int x) { return x >> 31; }

// is power of two
bool ispow2(int x) { return (x & x - 1) == 0; }

// power of two round up
int nlpow2(int x) {
  for (int i = 0; i < 5; ++i)
    x |= x >> (1 << i);
  return ++x;
}

// next higher number with the same number of bits set
unsigned nexthi_same_count_ones(unsigned a) { /* Gosper */
  /* works for any word length */
  unsigned c = (a & -a);
  unsigned r = a+c;
  return (((r ^ a) >> 2) / c) | r);
}


template <class T> // bit count, use with bitop
void bitcount(T &x, int s, T m) { x = (x >> s & m) + (x & m); }

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


// bit length, use with extended bitop
void bitlength(T &x, int s, T m, int c) { if (x & m << s) x >>= s, c |= s; }
