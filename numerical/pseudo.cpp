/* KTH ACM Contest Template Library
 *
 * Numerical/Number Theory/pseudo
 *
 * Credit:
 *   Donald Knuth?
 *   Based on ?
 *   By David and Mattias
 */

const int pseudo_mod = 1<<31;
const int pseudo_mul = 247590621; // Largest prime < psuedo_mod (?)
int pseudo_seed = 0x12345678;

int pseudo() { // [0,1<<31)
  return pseudo_seed=(pseudo_seed*pseudo_mul+1)&(pseudo_mod-1);
}

double fpseudo() { // [0.0,1.0)
  return ((double)pseudo()/pseudo_mod+(double)pseudo())/pseudo_mod;
}

unsigned long long ulpseudo() { // [0,1<<62)
  return ((unsigned long long)pseudo())*pseudo_mod+pseudo();
}
