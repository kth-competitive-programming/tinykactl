// example for_edge function objects:

// one fun
typedef vector<int> Vi; vector<Vi> g;
struct onefun {
  template <class F> void operator()(int node, F &f) {
    const Vi &l = g[node];
    for (Vi::const_iterator i = l.begin(); i != l.end(); ++i)
      f(*i, 1);
  }
};

// weighted edge fun
typedef vector<pair<int, int> > Vp; vector<Vp> h;
struct wefun {
  template <class F> void operator()(int node, F &f) {
    const Vp &l = h[node];
    for (Vp::const_iterator i = l.begin(); i != l.end(); ++i)
      f(i->first, i->second);
  }
};

// geometrical dist fun
typedef vector<point<double> > VP; int n; VP pts(n);
struct distfun {
  template <class F> void operator()(int node, F &f) {
    for (int i = 0; i < pts.size(); ++i)
      f(i, dist(pts[node] - pts[i]));
  }
};

// the following funs fetches min[node] from inside f, which is a bit ugly:

// for time-table searches without mod
typedef vector<pair<int, pair<int, int> > > Vpp; vector<Vpp> g;
struct stepfun {
  template <class F> void operator()(int node, F &f) {
    const Vi &l = g[node]; int t = f.min[node];
    for (Vpp::const_iterator i = l.begin(); i != l.end(); ++i)
      if (i->second.first >= t)
	f(i->first, i->second.first - t + i->second.second);
  }
};

// for time-table searches
typedef vector<pair<int, pair<int, int> > > Vpp; vector<Vpp> g;
template <int MOD> struct modfun {
  template <class F> void operator()(int node, F &f) {
    const Vi &l = g[node]; int t = f.min[node];
    for (Vpp::const_iterator i = l.begin(); i != l.end(); ++i)
      f(i->first, (i->second.first - t % MOD + MOD) % MOD + i->second.second);
  }
};
