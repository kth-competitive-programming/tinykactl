/* KTH ACM Contest Template Library
 *
 * Geometry/Polygons/Inside
 *
 * Credit:
 *   By Per Austrin
 */

#include "point_line_relations.cc"

template <class It, class P>
bool poly_inside(It begin, It end, const P &p, bool strict = true) {
  bool inside = false;
  for (It i = begin, j = end - 1; i != end; j = i++) {
    if (on_segment(*j, *i, p)) return !strict;
    if (min(j->x, i->x) < p.x && max(j->x, i->x) >= p.x &&
	abs(j->x - i->x)*(p.y - i->y) > abs(p.x - i->x)*(j->y - i->y))
      inside ^= 1;
  }
  return inside;
}
