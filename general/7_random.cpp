/*****************************************************************************
 * 
 * 7_random: (pseudo-random)
 * =====================
 *
 * pseudo gives a pseudo-random integer in [0,1<<31-1]
 * fpseudo gives a pseudo-random number in [0.0,1.0)
 *
 * COMPLEXITY  O(1)
 * ------------------------------------------------------------------------- *
 *
 * NADA acmlib (10 March 2002)
 * Templates for KTH-NADA, Ballons'R'Us, ACM 2001-2002
 *   Swedish competition, Link?ping 6 Oct 2001
 *   Revised for SWERC, Portu, Portugal 17 Nov 2001
 *   Revised for World Finals, Honolulu, 23 Mar 2002
 *   David Rydh, Mattias de Zalenski, Fredrik Niemelä
 *
 *****************************************************************************/

const int pseudo_mod = 1<<31;
const int pseudo_mul = 247590621;
int pseudo_seed = 0x12345678;

int pseudo() {
  return pseudo_seed=(pseudo_seed*pseudo_mul+1)&(pseudo_mod-1);
}

double fpseudo() {
  return ((double)pseudo()/pseudo_mod+(double)pseudo())/pseudo_mod;
}
