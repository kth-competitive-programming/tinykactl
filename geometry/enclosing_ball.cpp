/* KTH ACM Contest Template Library
 *
 * Geometry/Enclosing ball/Minimal enclosing d-ball
 *
 * Credit:
 *   Based on algorithm by Emo Welzl -- 
 *            "Smallest enclosing disks (balls and ellipsoids)"
 *            (Lecture Notes in Computer Science 555 (1991) 359-370)
 *   Based on implementation by Bernd Gärtner --
 *            "Smallest Enclosing Balls - A Fast and Robust C++ Implementation"
 *            (www.inf.ethz.ch/personal/gaertner/miniball.html)
 *   By Per Austrin
 *   Bugfixed for World Finals 2006 by Joel
 */

#include <algorithm>

/* P is D-dimensional point type.
 * P needs: operator+, operator- (componentwise)
 *          operator* (by scalar), dot(), dist2()
 */
template <typename P, int D=3>
struct enclosing_ball {
  int support;
  P ortho[D+1], center[D+1];
  double radsqr[D+1], z[D+1];

  const P& Center() { return center[support]; }
  double RadSqr() { return radsqr[support]; }

  // find the minimal enclosing ball of range [begin, end)
  template <typename It> 
  void compute(It begin, It end) { 
    radsqr[0] = support = 0;    // reset ball
    random_shuffle(begin, end); // to ensure expected linear time
    find_sub(begin, end, 0);
  }

  bool add_support(const P& p, int b) {
    if ((p-Center()).dist2() - RadSqr() < 1e-10) 
      return false; // p already inside sphere
    if (!b) center[0] = p;
    else {
      P q = p - center[0], proj = P();
      for (int i = 1; i < b; ++i)
	proj = proj + ortho[i] * (ortho[i].dot(q) / z[i]);
      ortho[b] = q - proj;
      z[b] = ortho[b].dist2();
      if (z[b] < 1e-25 * RadSqr()) return false;
      double e = ((p-center[b-1]).dist2() - radsqr[b-1]) / 2;
      center[b] = center[b-1] + ortho[b]*(e/z[b]);
      radsqr[b] = radsqr[b-1] + e*e/z[b];
    }
    support = b;
    return true;
  }
  
  template <typename It>
  void find_sub(It begin, It end, int b) {
    if (begin != end && b != D+1) {
      find_sub(begin, --end, b);
      if (add_support(*end, b))
	find_sub(begin, end, b+1);
	// TODO: Welzl's move-to-front heuristic
    }
  }
};
