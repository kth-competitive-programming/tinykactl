/* KTH ACM Contest Template Library
 *
 * Geometry/Convex hull/Graham Scan
 *
 * Credit:
 *   Graham
 *   Based on [Intro to algorithms] and previous KACTL implementation.
 *   By Mattias de Zalenski
 *   Bugfixed for World Finals 2004 by Per
 */

template <class P>
struct cross_dist_comparator {
  P o; cross_dist_comparator(P _o) : o(_o) { }
  bool operator ()(const P &p, const P &q) const {
    typename P::coord_type c = (p-o).cross(q-o);
    return c != 0 ? c > 0 : (p-o).dist2() > (q-o).dist2();
  }
};

template <class It>
It convex_hull(It begin, It end) {
  typedef typename iterator_traits<It>::value_type P;
  // zero, one or two points always form a hull
  if (end - begin < 3) return end;
  // find a guaranteed hull point, sort in scan order around it
  swap(*begin, *min_element(begin, end));
  cross_dist_comparator<P> comp(*begin);
  sort(begin + 1, end, comp);
  // colinear points on first line of the hull must be reversed
  It i = begin + 1;
  for (It j = i++; i != end; j = i++)
    if ((*i-*begin).cross(*j-*begin) != 0)
      break;
  reverse(begin + 1, i);
  // place hull points first by doing a Graham scan
  It r = begin + 1;
  for (It i = begin + 2; i != end; ++i) {
    // change < 0 to <= 0 if colinear points are not desired
    while (r > begin && (*r - *(r-1)).cross(*i-*(r-1)) < 0)
      --r;
    swap(*++r, *i);
  }
  // removing colinear points at the end of the hull
  while (r-1 > begin && cross(*begin - *(r-1), *r - *(r-1)) == 0)
    --r;
  // return the iterator past the last hull point
  return ++r;
}
