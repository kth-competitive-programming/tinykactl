/* KTH ACM Contest Template Library
 *
 * Graph/Euler Cycle/de Bruijn (fast)
 *
 * Credit:
 *   N. G. de Bruijn
 *   by David Rydh
 */

template<class V>
void euler_walk_dB( V &edges, int start, list< int > &path, int nSymb,
		    int nNodes )
{
  int node = start;

  while( true ) {
    int &s = edges[node];

    path.push_back( node );

    if( s == 0 )
      break;

    for( int i=0; i<nSymb; i++ ) {
      if( s & (1<<i) ) {
	node = (node*nSymb)%nNodes + i;
	s ^= (1<<i);
	break;
      }
    }
  }

  //for( list<int>::iterator iter = path.begin(); iter != path.end(); iter++ )

  for( list<int>::iterator iter = --path.end(); iter != path.begin(); ) {
    list<int>::iterator iter2 = iter; iter2--;
    node = *iter;

    int &s = edges[node];
    while( s != 0 ) {
      list<int>  extra_list;
      euler_walk_dB( edges, node, extra_list, nSymb, nNodes );
      path.splice( iter, extra_list, extra_list.begin(), --extra_list.end() );
    }
    iter = iter2;
  }
}


void deBruijn_fast( int nSymb, int L, char symbols[]) {
  int                nNodes;
  vector< int >      edges;
  list<int>          path;

  nNodes = 1;
  for( int i=0; i<L-1; i++ )
    nNodes *= nSymb;

  edges.reserve( nNodes );
  for( int i=0; i<nNodes; i++ )
    edges.push_back( (1<<nSymb)-1 );

  euler_walk_dB( edges, 0, path, nSymb, nNodes );


  // Non-cyclic deBruijn sequences
  cout << "Non-cyclic:" << endl;

  string answer;
  for( list<int>::iterator iter = path.begin(); iter != path.end(); iter++ ) {
    int node = *iter;

    if( iter==path.begin() ) {
      int d = nNodes;

      for( int j=0; j<L-1; j++ ) {
	d/= nSymb;
	answer += symbols[ node % nSymb ];
      }
    } else
      answer += symbols[ node % nSymb ];
  }
  cout << answer << endl;

  // Cyclic deBruijn sequences
  cout << "Cyclic:" << endl;
  cout << answer.substr(0, answer.length()-(L-1)) << endl << endl;
}

