/* KTH ACM Contest Template Library
 *
 * Geometry/Primitives/Union of Intervals
 *
 * Credit:
 *   By David Rydh
 */

#include <algorithm>

template <class It, class OIt>
It ival_union( It begin, It end, OIt dest ) {
  sort( begin, end );
  while( begin != end ) {
    *dest = *begin++;
    while( begin != end && begin->first <= dest->second )
      dest->second >?= begin++->second;
    ++dest;
  }
  return dest;
}   

