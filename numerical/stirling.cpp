/* KTH ACM Contest Template Library
 *
 * Numerical/Combinatorics/Stirling numbers
 *
 * beräknar stirlingtalet för n,k
 * dvs hur många sätt kan man placera n olika objekt i k lådor
 * utan att lämna någon låda tom
 *
 * Credit:
 *   Stirling
 *   By Max Bennedich
 *   Update by David Rydh
 */

template <class T>
T stirling( T n, T k ) {
  if( n <= T(1) )
    return T(k==n ? 1:0);
  else
    return stirling( n-1, k-1 ) + k*stirling( n-1, k );
}
