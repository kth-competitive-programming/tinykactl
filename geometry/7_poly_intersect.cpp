/*****************************************************************************
 * 
 * 7_poly_intersect: Intersection of polygons
 * ==========================================
 *
 * <explanation>
 *
 * INPUT
 * -----
 *
 * OUTPUT
 * ------
 *
 * COMPLEXITY  -
 *
 * REQUIRES  -
 * ------------------------------------------------------------------------- *
 *
 * NADA acmlib (10 March 2002)
 * Templates for KTH-NADA, Ballons'R'Us, ACM 2001-2002
 *   Swedish competition, Linköping 6 Oct 2001
 *   Revised for SWERC, Portu, Portugal 17 Nov 2001
 *   Revised for World Finals, Honolulu, 23 Mar 2002
 *   David Rydh, Mattias de Zalenski, Fredrik Niemelä
 *
 *****************************************************************************/

template<class T>
struct line_sort {
  double lx, ly;

  line_sort( double _lx=0, double _ly=0 ) : lx(_lx), ly(_ly) {}

  bool operator()(const point<T> &p1, const point<T> &p2) const
  { return dx(p1,p2)*lx+dy(p1,p2)*ly > 0; }
};


template<class V, class L>  // L is an output-iter with vector< point<T> >:s.
int poly_intersect( const V &p, int m, const V &q, int n, L &isectPolys ) {
  typedef typename iterator_traits<V>::value_type P;
  typedef typename P::coord_type T;
  typedef multimap<P, int, line_sort<T> > M;
  vector< M > pi, qi;

  for( int i=0; i<m; i++ )
    pi.push_back( M(line_sort(dx(p[i],p[(i+1)%m]), dy(p[i],p[(i+1)%m]))) );
  for( int i=0; i<n; i++ )
    qi.push_back( M(line_sort(dx(q[i],q[(i+1)%n]), dy(q[i],q[(i+1)%n]))) );

  for( i=0; 
}
