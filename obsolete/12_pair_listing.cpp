/*****************************************************************************
 * 
 * General11: misc container pair_listing::vector, pair_listing::list
 * ===========================================================
 *
 * A container that lists pairs of index,value in operator[].
 * Could be used for generating edge-lists..
 *
 * ------------------------------------------------------------------------- *
 *
 * NADA acmlib (10 March 2002)
 * Templates for KTH-NADA, Ballons'R'Us, ACM 2001-2002
 *   Swedish competition, Link?ping 6 Oct 2001
 *   Revised for SWERC, Portu, Portugal 17 Nov 2001
 *   Revised for World Finals, Honolulu, 23 Mar 2002
 *   David Rydh, Mattias de Zalenski, Fredrik Niemel?
 *
 *****************************************************************************/

#include <vector>
#include <list>

template <class S, class T>
struct pair_listing {
  typedef pair<S, T> pair;
  template <class V>
  struct lister : public V {
    T &operator [](S index) {
      push_back(make_pair(index, T()));
      return back().second;
    }
  };
  typedef lister< vector<pair> > vector;
  typedef lister< list<pair> > list;
};
