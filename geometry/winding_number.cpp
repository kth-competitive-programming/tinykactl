/* KTH ACM Contest Template Library
 *
 * Geometry/Polygons/Winding Number
 *
 * Credit:
 *   By Matthias de Zalenski and David Rydh
 */

#include "pointline.cpp"

template<class V, class P>
double winding_nr(const V &p, int n, const P &t, bool &onEdge) {
  double wind = 0;

  onEdge = false;

  for (int i=0, j=n-1; i<n; j=i++) {
    if( onsegment(p[i], p[j], t) ) {
      onEdge = true;
      continue;
    }
    double t1 = theta(t-p[i]), t2 = theta(t-p[j]);
    double dt = t1-t2;
    if( dt > 2 ) dt -= 4;
    if( dt < -2 ) dt += 4;
    wind += dt;
  }

  return wind;
}

template<class P, class V>     // V is vector/array of point<T>s
int inside_wn(const V &p, int n, P t) {
  bool edge;
  double wind = winding_nr(p,n,t, edge);

  if( edge ) return wind>4 ? 1:0;

  // Not on edge, i.e. wind is (approx) 4*nr of turns.
  return wind > 2 ? 1:-1;
}
