/*****************************************************************************
 * 
 * geometric_mst: Geometric minimal spanning tree
 * ==============================================
 *
 * Find a minimal spanning tree for a set of geometric points.
 *
 * INPUT
 * -----
 * V:      point
 * n:      number of points
 * E:      output tree
 *
 * OUTPUT
 * ------
 * tree:   The minimal spanning tree. tree may be the same vector as edges.
 *         It must already have the correct nr of edge-lists allocated.
 *
 *
 * COMPLEXITY  O(E log E)
 *
 * REQUIRES: mst/1_sets.cpp
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

#include <algorithm>
#include <vector>
#include <functional>

#include "geometry.h"
#include "../graph/mst/3_partial.cpp"


template <class V, class L>
L dist_edge_list(const V &p, int n, L edges) {
  return vertex_fun_edge_list(p, n, fun_ptr(dist2), edges);
}

template <class V>
double geometric_mst(const V &p, int n) {
  typedef typename iterator_traits< V >::value_type::coord_type C;
  typedef typename edge_traits< C >::edge_type E;
  typedef typename vector< E > L;
  typedef vector<int> I;
  L edges;
  dist_edge_list(p, n, back_insert_iterator(edges));
  sort(edges.begin(), edges.end());
  I idx;
  vector<int> v_flags;
  v_flags.resize(n);
  for (int i = 0; i < n; i++) v_flags[i] = true;
  partial_mst_index(v_flags, edges, n, back_insert_iterator(idx));
  int mst_size = idx.size();
  double d = 0;
  for (int i = 0; i < mst_size; i++) {
    d += sqrt(edges[idx[i]].first);
  }
  return d;
}

template <class V, class L, class F, class I>
double geometric_tsp_sub(const V &p, const L &edges,
			 F &v_flags, I &idx, I &best_idx,
			 int i, int n, double lim, int level) {
  v_flags[i] = false;
  v_flags[i] = true;
}

template <class V, class I>
double geometric_tsp(const V &p, I &idx, int n) {
  typedef typename iterator_traits< V >::value_type::coord_type C;
  typedef typename edge_traits< C >::edge_type E;
  typedef typename vector< E > L;
  L edges;
  dist_edge_list(p, n, back_insert_iterator(edges));
  sort(edges.begin(), edges.end());
  I idx;
  vector<int> v_flags;
  v_flags.resize(n);
  for (int i = 0; i < n; i++) v_flags[i] = true;
  partial_mst_index(v_flags, edges, n, back_insert_iterator(idx));
  int mst_size = idx.size();

  double d = 0;
  for (int i = 0; i < mst_size; i++) {
    d += sqrt(edges[idx[i]].first);
  }
  return d;

}
