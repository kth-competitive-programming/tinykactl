/* KTH ACM Contest Template Library
 *
 * Geometry/Polygons/Inside
 *
 * Credit:
 *   By David Rydh
 */

template<class P, class V>     // V is vector/array of point<T>s
bool inside(const V &p, int n, P t) {
  bool c = false;

  for (int i=0, j=n-1; i<n; j=i++) {
    if ( ((p[i].y<=t.y && t.y<p[j].y) || (p[j].y<=t.y && t.y<p[i].y)) &&
         (dx(p[i],t) < dx(p[i],p[j])*dy(p[i],t)/dy(p[i],p[j])) )
      c = !c;
  }
  return c;
}
