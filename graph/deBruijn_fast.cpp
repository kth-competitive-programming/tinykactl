/* KTH ACM Contest Template Library
 *
 * Graph/Euler Cycle/de Bruijn (fast)
 *
 * Credit:
 *   N. G. de Bruijn
 *   by David Rydh
 */

template<class V>
void euler_walk_dB(V &edges, int start, list<int> &path, 
		   int nSymb, int nNodes) {
  int node = start;
  while( true ) {
    int &s = edges[node];
    path.push_back( node );
    if( s == 0 ) break;
    for( int i=0; i<nSymb; i++ )
      if( s & (1<<i) ) {
	node = (node*nSymb)%nNodes + i;
	s ^= (1<<i);
	break;
      }
  }

  for(list<int>::iterator it=--path.end(); it!=path.begin();) {
    list<int>::iterator iter2 = iter; iter2--;
    node = *iter;
    int &s = edges[node];
    while( s != 0 ) {
      list<int> add;
      euler_walk_dB(edges, node, add, nSymb, nNodes);
      path.splice(iter, add, add.begin(), --add.end());
    }
    iter = iter2;
  }
}


void deBruijn(int nSymb, int L, char *symbols, char *sol) {
  int           nNodes = 1;
  vector<int>   edges;
  list<int>     p;
  for(int i = 0; i < L-1; ++i) nNodes *= nSymb;
  edges.reserve(nNodes);
  for(int i = 0; i < nNodes; ++i)
    edges.push_back((1<<nSymb) - 1);

  euler_walk_dB(edges, 0, p, nSymb, nNodes);
  for(list<int>::iterator it = p.begin(); it != p.end(); ++it)
    if(iter == p.begin())
      for(int j=0; j<L-1; j++)
	*sol++ = symbols[*iter % nSymb];
    else
      *sol++ = symbols[*iter % nSymb];
  *sol = 0;
}
