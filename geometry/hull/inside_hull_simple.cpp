/* KTH ACM Contest Template Library
 *
 * Geometry/Convex hull/Inside Hull Simple
 *
 * Credit:
 *   By David Rydh
 */

// If the hull only consist of non-colinear points the degenerated-hull-check
// can be replaced with a onsegment-call if end-begin==2.

template <class It, class T>
int inside_hull_simple(It begin, It end, const point<T> &t) {
  bool on_edge = false;

  point<T> p, q;   // degenerated hulls
  p = q = *begin;  //

  for( It i=begin, j=end-1; i!=end; j=i++ ) {
    T d = cross(*i-*j,t-*j);
    if( d<0 )
      return -1;
    if( d==0 ) on_edge = true;

    p.x = min(p.x,i->x); // degenerated hulls
    p.y = min(p.y,i->y); //
    q.x = max(q.x,i->x); //
    q.y = max(q.y,i->y); //
  }

  // Extra check for degenerated hulls
  if( on_edge ) {
    if( t.x<p.x || t.x>q.x || t.y<p.y || t.y>q.y )
      return -1;
  }

  return on_edge ? 0:1;
}
