/* KTH ACM Contest Template Library
 *
 * Graph/Network Flow/Max Weight Bipartite Matching
 *
 * Complexity: O( V(E+V^2) )
 *
 * Credit:
 *   After Kurt Mehlhorn (LEDA)
 *   By David Rydh
 */

#include "max_weight_bipartite_matching.cpp"

template< class E, class M, class W >
void max_weight_b_m_of_max_card(E &edges, int n, int m, 
				M &match_b, W &max_weight) {
  typedef typename E::value_type L;
  typedef typename L::iterator L_iter;

  W Cmax = 0;
  for( int a=0; a<n; a++ )
    for(L_iter e = edges[a].begin(); e != edges[a].end(); ++e)
      Cmax = max( Cmax, max(e->second, -e->second) );
  Cmax = 1 + 2*max(n,m)*Cmax;

  for( int a=0; a<n; a++ )
    for( L_iter e = edges[a].begin(); e != edges[a].end(); ++e )
      e->second += Cmax;

  max_weight_bipartite_matching(edges, n, m, 
				match_b, max_weight, false);

  for(int b=0; b<m; b++)
    if( match_b[b] >= 0 )
      max_weight -= Cmax;

  for( int a=0; a<n; a++ )
    for( L_iter e = edges[a].begin(); e != edges[a].end(); ++e )
      e->second -= Cmax;
}
