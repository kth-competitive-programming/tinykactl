/* KTH ACM Contest Template Library
 *
 * Combinatorial/Permute
 *
 * Credit:
 *   By David Rydh
 */

template <class R>
void permute( R f, R c, R l ) {
  if( c==l ) {
    // Process whole perm
    while( f<l )
      cout << *f++;
    cout << endl;
    return;
  }

  for( R i=c; i!=l; ++i ) {
    if( i != c ) {
      if( *i == *c ) // for repetitions
	continue;
      swap( *i, *c );
    }
    // Process pos c
    // ...

    // Continue permutation seq
    permute( f, c+1, l );
  }
  while( l>c )
    swap( *--l, *c );
}

