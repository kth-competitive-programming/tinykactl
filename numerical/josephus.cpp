/* KTH ACM Contest Template Library
 *
 * Numerical/Josephus/Josephus
 *
 * Credit:
 *   Josephus, i suppose.
 *   From [Graham, Knuth, Patachnik "Concrete Mathematics"]
 *   Lectured by Mikael Goldman
 *   By Mattias de Zalenski
 */

int josephus(int n, int k) {
  int d = 1;
  while (d <= (k - 1) * n)
    d = (k * d + k - 2) / (k - 1);
  return k * n + 1 - d;
}
