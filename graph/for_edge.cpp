// example for_edge function objects:

typedef vector<int> Vi; vector<Vi> g;
struct onefun {
  template <class F> void operator()(int node, F &f) {
    const Vi &l = g[node];
    for (Vi::const_iterator i = l.begin(); i != l.end(); ++i)
      f(make_pair(*i, 1));
  }
}

typedef vector<pair<int, int> > Vp; vector<Vp> h;
struct lenfun {
  template <class F> void operator()(int node, F &f) {
    const Vp &l = h[node];
    for_each(l.begin(), l.end(), f);
  }
}

typedef vector<point<double> > VP; int n; VP pts(n);
struct distfun {
  template <class F> void operator()(int node, F &f) {
    for (int i = 0; i < pts.size(); ++i)
      f(i, dist(pts[node] - pts[i]));
  }
}
