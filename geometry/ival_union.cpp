/* KTH ACM Contest Template Library
 *
 * Geometry/Primitives/Union of Intervals
 *
 * Credit:
 *   By David Rydh
 */

template <class F, class O>
O ival_union( F begin, F end, O dest ) {
  sort( begin, end );
  while( begin != end ) {
    *dest = *begin++;
    while( begin != end && begin->first <= dest->second ) {
      dest->second = max(dest->second,begin->second);
      ++begin;
    }
    ++dest;
  }
  return dest;
}   

