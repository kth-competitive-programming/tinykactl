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

int pseudo() {
  return pseudo_seed=(pseudo_seed*pseudo_mul+1)&(pseudo_mod-1);
}

double fpseudo() {
  return ((double)pseudo()/pseudo_mod+(double)pseudo())/pseudo_mod;
}
