/* KTH ACM Contest Template Library
 *
 * Geometry/Primitives/Line intersection
 *
 * Credit:
 *   By Per Austrin
 */

const double NO_ISECT = -1.0/0.0;

template <class P> inline 
double line_isect(const P& A0, const P& A1, 
		  const P& B0, const P& B1) {
  typedef P::value_type T;
  P dP1 = A1-A0, dP2 = B1-B0, dL = B0-A0;
  T det = dP1.cross(dP2), s = dL.cross(dP1), t = dL.cross(dP2);

  /* intersection between infinitely extending lines: */
  if (det == 0) return NO_ISECT;

  /* intersection between finite line segments: */
  if (det == 0) {
    T s1 = dP1.dot(dL), s2 = dP1.dot(B1)-dP1.dot(A0);
    if (t != 0 || min(s1, s2) > dP1.dist2() || max(s1, s2) < 0)
      return NO_ISECT;
    return sqrt((double) max(0, min(s1, s2)));
  } 

  /* both: */
  if (det < 0) det = -det, t = -t, s = -s;
  if (!(t >= 0 && t <= det && s >= 0 && s <= det))
    return NO_ISECT;
  return (double)t / det;
}

template <class P> inline 
bool line_isect(const P& A0, const P& A1, 
		const P& B0, const P& B1, P &R) {
  double t = line_isect(A0, A1, B0, B1);
  if (t != NO_ISECT) R = (1-t)*A0 + t*A1;
  return t != NO_ISECT;
}
