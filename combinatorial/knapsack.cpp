/* KTH ACM Contest Template Library
 *
 * Combinatorial/Hard Optimisation Problems/Knapsack Heuristic
 *
 * Credit:
 *   By Per Austrin
 */

#include <vector>

/* Templates:
 * R is the value type (needs to be constructable from "-1").
 * T is the cost type (needs to be multipliable with doubles).
 * W is a random access container of costs.
 * V is a random access container of values.
 */
template <class R, class T, class W, class V>
R knapsack(int n, const T& C, const W& costs, const V& values,
	   int bound=500000) {
  double scale = bound / ((double) n * C);
  // This line should be removed if the costs are all 
  // small-valued doubles.
  if (scale > 1) scale = 1;

  int C_max = (int) (scale * C) + 1;
  R max = R();
  vector<R> val_max(C_max, R(-1));
  val_max[0] = R();

  for (int i = 0; i < n; ++i) {
    int scaled_cost = (int) (scale * costs[i]);
    for (int j = C_max - 1; j >= scaled_cost; --j) {
      R v = val_max[j - scaled_cost];
      if (v != -1 && v + values[i] > val_max[j]) {
	val_max[j] = v + values[i];
	if (val_max[j] > max)
	  max = val_max[j];
      }
    }
  }

  return max;
}
