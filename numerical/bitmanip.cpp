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
