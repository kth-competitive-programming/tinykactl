/* KTH ACM Contest Template Library
 *
 * Computational Geometry/Intervals/Combining Intervals
 *
 * Method for adding an interval I to a disjoint set of intervals S,
 * such that the result is the least disjoint set of intervals S'
 * covering the union of S and {I}.
 *
 * Complexity: O(|S|)  [1]
 *
 * Example: see Valladolid Problem 313.
 *
 * Credit:
 *   By Per Austrin, 2002-10-01
 *   Cleaned up for KACTL by Per Austrin, 2002-10-03
 *
 * [1] - It is possible to reduce to complexity to O(log |S|) using
 *       search trees (sets/maps) instead of lists. However, for most
 *       practical purposes, O(|S|) should be enough.
 */

#include <list>

#define MIN(a,b) ((a)>(b) ? (b) : (a))
#define MAX(a,b) ((a)<(b) ? (b) : (a))

/* EPSILON defines the distance quanta, i.e. if the distance between
 * two intervals is less then EPSILON, they are considered to
 * intersect each other.
 */
#define EPSILON 1E-4


template <class T>
struct I_Traits {
  typedef pair<T,T> Interval;
  typedef list<Interval> Intervals;
};


/* Add the interval I to the set of intervals S.  T is the type used
 * for the interval (usually double).
 *
 * PRE: [The intervals in S are all pairwise disjoint.]
 *
 * POST: The intervals in S cover all the previous intervals in S, and
 *       the interval I. [The intervals in S are all pairwise disjoint.]
 */
template <class T>
void IntervalAdd(I_Traits<T>::Intervals &S,
		 const I_Traits<T>::Interval &I) {
  typedef I_Traits<T>::Intervals::iterator IntsIt;
  const T eps = EPSILON;

  IntsIt l = S.end();
  for (IntsIt j = S.begin(); j != S.end(); ++j)
    if (j->second + eps >= I.first) {
      l = j;
      break;
    }

  IntsIt ni = S.insert(l, I);
  if (l != S.end())
    ni->first = MIN(ni->first, l->first);
  
  IntsIt r = S.end();
  for (IntsIt j = l; j != S.end(); ++j)
    if (j->first + eps >= ni->second) {
      r = j;
      break;
    }
  
  ni->second = MAX(ni->second, (--r)->second);
  S.erase(l, ++r);
}

/* Convenience definitions. Replace double by the datatype of your
 * choice.
 */
typedef I_Traits<double>::Interval Interval;
typedef I_Traits<double>::Intervals Intervals;
