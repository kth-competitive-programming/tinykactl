/* KTH ACM Contest Template Library
 *
 * Geometry/Hull/Hull diameter
 *
 * Credit:
 *   By David Rydh, Mattias de Zalenski
 */

template <class V>
double hull_diameter2(V p, int n, int &i1, int &i2) {
  typedef typename V::value_type::coord_type T;
  if (n < 2) { i1 = i2 = 0; return 0; }
  T m = 0;
  int i, j = 1, k = 0;
  // wander around
  for (i = 0; i <= k; i++) { 
    // find opposite
    T d2 = dist2(p[j]-p[i]);
    while (j + 1 < n) {
      T t = dist2(p[j+1]-p[i]);
      if (t > d2) d2 = t; else break;
      j++;
    }
    if (i == 0) k = j; // remember first opposite index
    if (d2 > m) m = d2, i1 = i, i2 = j;
  }
  //  cout << "first opposite: " << k << endl;
  return m;
}
