int lowest_bit(int x) { return x & -x; }

bool ispow2(int x) { return (x & x - 1) == 0; }

int nlpow2(int x) { // power of two round up
  for (int i = 0; i < 5; ++i)
    x |= x >> (1 << i);
  return ++x;
}

// next higher number with the same number of bits set
unsigned nexthi_same_count_ones(unsigned a) {
  unsigned c = (a & -a), r = a+c;
  return (((r ^ a) >> 2) / c) | r;
}
