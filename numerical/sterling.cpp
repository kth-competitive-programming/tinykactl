/* KTH ACM Contest Template Library
 *
 * Numerical/Combinatorics/Sterling numbers
 *
 * beräknar sterlingtalet för n,k
 * dvs hur många sätt kan man placera n olika objekt i k lådor
 * utan att lämna någon låda tom
 *
 * Credit:
 *   Sterling
 *   By Max Bennedich
 *   Update by David Rydh
 */

int sterling( int n, int k ) {
  if( n <= 1 )
    return k==n ? 1:0;
  else
    return sterling( n-1, k-1 ) + k*sterling( n-1, k );
}
