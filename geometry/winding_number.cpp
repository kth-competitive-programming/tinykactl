/* KTH ACM Contest Template Library
 *
 * Geometry/Polygons/Winding Number
 *
 * Credit:
 *   By Matthias de Zalenski and David Rydh
 */

#include "point_line_relations.cpp"

template <class It, class P>
double winding_nr(It begin, It end, const P &t, bool &onEdge) {
  double wind = 0;
  onEdge = false;
  for (It i = begin, j = end-1; i != end; j = i++) {
    if(onsegment(*i, *j, t)) {
      onEdge = true;
      continue;
    }
    double t1 = (t-*i).theta(), t2 = (t-*j).theta();
    double dt = t1-t2;
    if (dt > 2) dt -= 4;
    if (dt < -2) dt += 4;
    wind += dt;
  }
  return wind;
}

template<class It, class P>     // V is vector/array of point<T>s
int inside_wn(It begin, It end, P t) {
  bool edge;
  double wind = winding_nr(begin,end,t, edge);
  if(edge) return wind>4 ? 1:0;
  // Not on edge, i.e. wind is (approx) 4*nr of turns.
  return wind > 2 ? 1:-1;
}
