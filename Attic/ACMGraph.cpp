/*
 * ACMGraph.cpp
 *
 * NADA acmlib (10 March 2002)
 *
 * Templates for KTH-NADA, Ballons'R'Us, ACM 2001-2002
 *   Swedish competition, Link?ping 6 Oct 2001
 *   Revised for SWERC, Portu, Portugal 17 Nov 2001
 *   Revised for World Finals, Honolulu, 23 Mar 2002
 *   David Rydh, Mattias de Zalenski, Fredrik Niemel?
 *
 */


/********************************************************************
 *  1) shortest_path_all_pairs (adj matrix)
 *******************************************************************/

template<class T, int N>    // T may be int, double etc
void shortest_path_all_pairs( T adj[N][N], T from_paths[N][N], int V ) {
  if( from_paths ) {
    for( int x=0; x<V; x++ )
      for( int y=0; y<V; y++ )
	from_paths[x][y] = -1;      // **
  }

  for( int m=0; m<V; m++ ) {
    for( int x=0; x<V; x++ ) {
      for( int y=0; y<V; y++ ) {
        if( adj[x][m] >=0 && adj[m][y] >= 0 ) {
          if( adj[x][y]<0 || adj[x][m] + adj[m][y] < adj[x][y] ) {
            adj[x][y] = adj[x][m] + adj[m][y];
            if( from_paths )                           // **
              from_paths[x][y] = from_paths[m][y];     // **
          }
        }
      }
    }
  }
}


/********************************************************************
 *  2) shortest_path
 *******************************************************************/

template<class R, class S, class T>
void shortest_path( const S edges, R min, T from, int start, int n ) {
  typedef S::value_type      E;
  typedef E::const_iterator  Eiter;
  typedef R::value_type      DIST;
  const DIST                 inf = (DIST)0x20000000;
  vector<bool>               processed;

  // Initialize min
  for( int i=0; i<n; i++ )
    min[i] = inf;
  min[start] = 0;


  processed.resize( n, false );

  // Find shortest path
  while( true ) {
    int  node;
    DIST least = inf;

    for( int i=0; i<n; i++ ) {
      if( !processsed[i] && min[i] < least ) {
        node = i;
        least = min[i];
      }
    }

    if( least == inf )    // the rest of the nodes are unreachable
      break;


    // Process node
    for( Eiter e=S[node].begin(); e!=S[node].end(); e++ ) {
      int destNode = (*e).first;

      if( !processed[destNode] && min[node]+(*e).second < min[destNode] )
        min[destNode] = min[node]+(*e).second;
    }
  }

  for( int i=0; i<n; i++ ) {
    if( min[i] == inf )
      min[i] = -1;
  }
}

/********************************************************************
 *  3) shortest_path_1
 *******************************************************************/

template<class R, class S, class T>
void shortest_path_1( const S edges, R min, T from, int start, int n ) {
  typedef S::value_type      E;
  typedef E::const_iterator  Eiter;
  const int                  inf = 0x20000000;
  int                        length;
  stack<int>                 proc, proc2;

  // Initialize min
  for( int i=0; i<n; i++ )
    min[i] = inf;
  min[start] = length = 0;

  proc.push( start );

  do {
    proc2.clear();
    length++;

    while( !proc.empty() ) {
      int node = proc.top();

      proc.pop();
 
      // Process node
      for( Eiter e=S[node].begin(); e!=S[node].end(); e++ ) {
        int destNode = *e;

        if( length < min[destNode] ) {
          // Process this node the next run
          min[destNode] = length;
          proc2.push( destNode );
        }
      }
    }
    swap( proc, proc2 );
  } while( !proc.empty() );

  for( i=0; i<n; i++ ) {
    if( min[i] == inf )
      min[i] = -1;
  }
}

/********************************************************************
 *  4) shortest_path_heap
 *******************************************************************/

template<class R, class S, class T>
void shortest_path_heap( const S edges, R min, T from, int start, int V ) {
  typedef S::value_type      E;
  typedef E::const_iterator  E_iter;

  struct dijkstra_vertix {
    int  nr;

    bool operator<( const dijkstra_vertix &x ) {
      return min[nr] > min[x.nr];  // We want the LEAST value
    }

    void set_position( int pos ) {
      inverse[nr] = pos;
    }
  };

  typedef R::value_type      DIST;
  upd_heap<DijkstraVertix>   heap();
  vector<int>                inverse;
  const DIST                 inf = (DIST)0x20000000;

  // Initialize min/from
  for( int i=0; i<V; i++ ) {
    min[i] = inf;
    if( from )       // **
      from[i] = -1;  // **
  }
  min[start] = 0;


  // Initialize heap
  inverse.resize( V );
  for( int i=0; i<V; i++ )
    heap.push( i );


  // Find shortest path
  while( !heap.empty() ) {
    int   node = heap.top();
    heap.pop();
    if( min[node] == inf )    // the rest of the nodes are unreachable
      break;

    // Process node
    for( E_iter e=S[node].begin(); e!=S[node].end(); e++ ) {
      int destNode = (*e).first;

      if( inverse[destNode] >= 0 &&
	  min[node]+(*e).second < min[destNode] )
	{
	  min[destNode] = min[node]+(*e).second;
	  heap.key_increased( inverse[destNode] );

	  if( from )                // ** for path-tracking
	    from[destNode] = node;  // **
	}
    }
  }

  for( int i=0; i<V; i++ ) {
    if( min[i] == inf )
      min[i] = -1;
  }
}

/********************************************************************
 *  5) get_shortest_path
 *******************************************************************/

template<class T>
bool get_shortest_path( const T from, T path, int start, int end ) {
  int    n=0;

  if( from[end]<0 )
    return false;

  for( int node=end; node!=start; node = from[node] )
    path[n++] = node;
  path[n++] = start;

  reverse( path, path+n );

  return true;
}

/********************************************************************
 *  6) euler_walk
 *******************************************************************/

void euler_walk( vector< set<int> > edges, int s_node, list< int > path ) {
  int node = s_node, next_node;

  // Find a maximal path
  while( true ) {
    set<int> &s = edges[node];

    path.push_back( node );

    if( s.size() == 0 )
      break;

    // Follow the first edge and remove it
    next_node = *s.begin();
    s.erase( s.begin() );

    node = next_node;
  } while( true ); //while( node != s_node );


  // Extend path with cycles
  list<int>::iterator iter = path.begin();

  while( iter != path.end() ) {
    node = *iter;

    set<int> &s = edges[node];

    while( s.size() > 0 ) {
      list<int>  extra_list;

      find_path( edges, node, extra_list );

      path.splice( iter, extra_list, extra_list.begin(), --extra_list.end() );
    }
    ++iter;
  }
}
