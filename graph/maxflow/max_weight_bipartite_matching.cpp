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

#include <vector>

template< class E, class M, class W >
inline bool augment( E &edges, int a, int n, int m,
		     vector<W> &pot, vector<bool> &free,
		     vector<int> &pred, vector<W> &dist, M &match_b,
		     bool perfect )
{
  typedef typename E::value_type L;
  typedef typename L::const_iterator L_iter;

  vector<bool> proc(m, false);
  dist[a] = 0;
  pred[a] = a; // Start of alternating path
  int best_a = a, a1 = a, v;
  W minA = pot[a], delta;

  while( true ) {
    // Relax all edges out of a1
    for( L_iter e = edges[a1].begin(); e != edges[a1].end(); ++e ) {
      int b = n+e->first;
      if( match_b[b-n] == a1 )
	continue;

      W db = dist[a1] + (pot[a1]+pot[b]-e->second);
      if( pred[b] < 0 || db < dist[b] ) {
	dist[b] = db; pred[b] = a1;
      }
    }

    // Select a node b with minimal distance db
    int b1 = -1;
    W db=0; // unused but makes compiler happy
    for( int b=n; b<n+m; b++ ) {
      if( !proc[b-n] && pred[b]>=0 && (b1<0 || dist[b]<db) ) {
	b1 = b;
	db = dist[b];
      }
    }

    if( b1>=0 )
      proc[b1-n] = true;

    // End conditions
    if( !perfect && (b1<0 || db >= minA) ) {
      // Augment by path to best node in A
      delta = minA;
      free[a] = false; free[best_a] = true; // NB! Order is important
      v = best_a;
      break;
    } else if( b1<0 ) {
      return false;
    } else if( free[b1] ) {
      // Augment by path to b
      delta = db;
      free[a] = free[b1] = false;
      v = b1;
      break;
    }

    // Continue shortest-path computation
    a1 = match_b[ b1-n ];
    pred[a1] = b1;
    dist[a1] = db;
    if( db+pot[a1] < minA ) {
      best_a = a1;
      minA = db+pot[a1];
    }
  }

  // Augment path
  while( true ) {
    int vn = pred[v];

    if( v==vn )
      break;

    if( v>=n ) match_b[v-n] = vn;
    v = vn;
  }

  for( int a=0; a<n; a++ ) {
    if( pred[a]>=0 ) {
      W dpot = delta - dist[a];
      pred[a] = -1;
      if( dpot > 0 ) pot[a] -= dpot;
    }
  }
  for( int b=n; b<n+m; b++ ) {
    if( pred[b]>=0 ) {
      W dpot = delta - dist[b];
      pred[b] = -1;
      if( dpot > 0 ) pot[b] += dpot;
    }
  }
  return true;
}

template< class E, class M, class W >
bool max_weight_bipartite_matching( E &edges, int n, int m, M &match_b,
				 W &max_weight, bool perfect )
{
  typedef typename E::value_type L;
  typedef typename L::const_iterator L_iter;

  vector<W> pot( n+m, 0 );
  vector<bool> free(n+m, true );
  vector<int> pred( n+m, -1 );
  vector<W> dist( n+m, 0 );

  for( int b=0; b<m; b++ )
    match_b[b] = -1;

  // Initialize pot and matching with simple heuristics
  for( int a=0; a<n; a++ ) {
    int b = -1;
    W Cmax = 0;

    for( L_iter e = edges[a].begin(); e != edges[a].end(); ++e ) {
      if( e->second > Cmax || e->second==Cmax && free[n+e->first] ) {
	b = n+e->first;
	Cmax = e->second;
      }
    }
    pot[a] = Cmax;
    if( b>=0 && free[b] ) {
      match_b[b-n] = a;
      free[a] = free[b] = false;
    }
  }

  // Augment matching
  for( int a=0; a<n; a++ )
    if( free[a] )
      if( !augment(edges, a, n, m, pot, free, pred, dist, match_b, perfect) )
	return false;

  max_weight = 0;
  for( int i=0; i<n+m; i++ )
    max_weight += pot[i];

  return true;
}
