/*****************************************************************************
 * 
 * Graph5: get_shortest_path
 * =========================
 *
 *
 * INPUT
 * -----
 *
 * OUTPUT
 * ------
 *
 * COMPLEXITY  O(V)
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


// T is a random access iterator into a container containing
// node-indices of size V.

template<class T>
bool get_shortest_path( const T &from, T &path, int start, int end ) {
  int    n=0;

  if( from[end]<0 )
    return false;

  for( int node=end; node!=start; node = from[node] )
    path[n++] = node;
  path[n++] = start;

  reverse( path, path+n );

  return true;
}
