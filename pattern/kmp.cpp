/*****************************************************************************
 * 
 * Pattern1: kmp (Knuth-Morris-Pratt)
 * ==================================
 *
 * Match substring with KMP algorithm. (for any alphabet)
 * If integers/characters aren't used, the class should have
 * a bool() function. (for the 0-termination)
 *
 * INPUT
 * -----
 * str:  the text to search for the pattern. (0-terminated)
 * p:    the pattern to search for. (0-terminated)
 *
 * OUTPUT
 * ------
 * result:  offset to first match.
 *
 * COMPLEXITY  O(n+m)
 *
 * ------------------------------------------------------------------------- *
 *
 * NADA acmlib (10 March 2002)
 * Templates for KTH-NADA, Ballons'R'Us, ACM 2001-2002
 *   Swedish competition, Link?ping 6 Oct 2001
 *   Revised for SWERC, Portu, Portugal 17 Nov 2001
 *   Revised for World Finals, Honolulu, 23 Mar 2002
 *   David Rydh, Mattias de Zalenski, Fredrik Niemel?
 *
 *****************************************************************************/

template<class S, class T>
int kmp( S str, T p ) {
  vector<int> prefix;
  int         m;

  for( m = 0; p[m]; m++ )
    ;

  // Compute prefix-function
  prefix.resize(m);
  prefix[0] = -1;
  for( int i=1, k=-1; i<m; i++ ) {
    while( k>=0 && p[k+1] != p[i] )
      k = prefix[k];
    if( p[k+1] == p[i] )
      k++;
    prefix[i] = k;
  }

  // Match string
  for( int i=0, k=-1; str[i]; i++ ) {
    while( k>=0 && p[k+1] != str[i] )
      k = prefix[k];
    if( p[k+1] == str[i] )
      k++;
    if( k==m-1 )
      return i-(m-1);
  }

  return -1;
}
