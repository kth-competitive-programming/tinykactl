/* KTH ACM Contest Template Library
 *
 * Geometry/Convex hull/Graham Scan
 *
 * Credit:
 *   Graham
 *   Based on [Intro to algorithms] and previous KACTL implementation.
 *   By Mattias de Zalenski
 */

template <class P>
struct cross_dist_comparator {
  P o; cross_dist_comparator(P _o) : o(_o) { }
  bool operator ()(const P &p, const P &q) const {
    typename P::coord_type c = cross(p-o, q-o);
    return c != 0 ? c > 0 : dist2(p-o) > dist2(q-o);
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
  // colinear points on the first line of the hull must be reversed
  It i = begin + 1;
  for (It j = i++; i != end; j = i++)
    if (cross(*i-*begin, *j-*begin) != 0)
      break;
  reverse(begin + 1, i);
  // place hull points first by doing a Graham scan
  It r = begin + 2;
  for (It i = begin + 3; i != end; ++i) {
    // change < 0 to <= 0 if colinear points on the hull are not desired
    while (cross(*r-*(r-1), *i-*(r-1)) < 0)
      --r;
    swap(*++r, *i);
  }
  // return the iterator past the last hull point
  return ++r;
}
