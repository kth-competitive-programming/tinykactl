/******************************************
 *
 * @JUDGE_ID: 25719RJ 10117 C++ ""
 *
 * Problem 10117 "Milk"
 *
 * David Rydh, <f99-dry@nada.kth.se>
 * October 2002
 *
 * Popup 02, Karmosin, 2002-10-07
 *
 * By Mattias de Zalenski and David Rydh
 *****************************************/

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

template <class T>
struct point {
  typedef T coord_type;
  T x, y;
  point(T _x = 0, T _y = 0) : x(_x), y(_y) { }
  point<T> operator-(const point<T> &p) const {
    return point<T>(x - p.x, y - p.y);
  }
  point<T> operator+(const point<T> &p) const {
    return point<T>(x + p.x, y + p.y);
  }
  point<T> operator*(const double &d) const {
    return point<T>(x*d, y*d);
  }
};

template <class V>
double poly_area(V p, int n) {
  int j = n - 1;
  typename V::value_type::coord_type a = 0;
  for (int i = 0; i < n; ++i) {
    a += (p[j].x - p[i].x) * (p[j].y + p[i].y);
    j = i;
  }
  return (double) a / 2;
}

template <class P> typename P::coord_type dx(P p, P q) { return p.x - q.x; }
template <class P> typename P::coord_type dy(P p, P q) { return p.y - q.y; }

template <class T> T sqr(T x) { return x * x; }

template <class T> T dot(point<T> p, point<T> q) {
  return p.x*q.x + p.y*q.y;
}
template <class T> T cross(point<T> p, point<T> q) {
  return p.x*q.y - p.y*q.x;
}
template <class P> P unit(P p) { return p * (1/dist(p)); }
template <class P> P perp(P p) { return P(-p.y, p.x); }
template <class P> P normal(P p) { return unit(perp(p)); }

template <class P>
double dist(P p, P q = P()) { return sqrt(sqr(dx(p, q)) + sqr(dy(p, q))); }


template <class P, class R>
bool line_isect(P p0, P p1, P q0, P q1, R &x) {
  typedef typename R::coord_type T;

  P p = p1-p0, q = q1-q0;
  T det = cross(p, q);
  if (det == 0)
    return false;

  T a = dot(perp(p), p0), b = dot(perp(q), q0);
  x.x = (a*q.x - b*p.x) / det;
  x.y = (a*q.y - b*p.y) / det;
  return true;
}

template <class CI, class OI, class P>
OI poly_cut(CI first, CI last, P p0, P p1, OI result) {
  if (first == last) return result;
  P p = p1-p0;
  CI j = last; --j;
  bool pside = cross(p, *j-p0) > 0;
  for (CI i = first; i != last; ++i) {
    bool side = cross(p, *i-p0) > 0;
    if (pside ^ side)
      line_isect(p0, p1, *i, *j, *result++);
    if (side)
      *result++ = *i;
    j = i; pside = side;
  }
  return result;
}


const int N = 0;
const bool debug = true;

void init();
bool solve(int P);

int main() {
  init();

  int n = 0;
  while (solve(n))
    ++n;

  return 0;
}

void init() {
}

typedef point<double> Pt;
typedef vector< Pt > V;

V pts; int n;
double h, a, maxarea;

void cut_it( int c, int k, const V &c_pts ) {
  if( k==0 ) {
    double b = poly_area( c_pts, c_pts.size() );
    maxarea = max( a-b, maxarea );
    return;
  }

  if( n-(c+1) >= k )
    cut_it( c+1, k, c_pts );

  if( k>0 ) {
    // Cut
    Pt o = pts[c], oo = pts[(c + 1) % n];
    Pt n = normal(oo-o)*h;
    o = o+n; oo = oo+n;
    V pts2( c_pts.size()*2 );
    pts2.resize( poly_cut( c_pts.begin(), c_pts.end(), o, oo, pts2.begin() )
		 - pts2.begin() );

    cut_it( c+1, k-1, pts2 );
  }
}

bool solve(int P) {
  int k;
  cin >> n >> k >> h;
  if (n == 0 && k == 0 && h == 0) return false;
  pts.clear();
  for (int i = 0; i < n; ++i) {
    double x, y;
    cin >> x >> y;
    pts.push_back(point<double>(x, y));
  }

  if( k > n ) k = n;

  a = poly_area(pts, n);
  maxarea = 0;
  V pts2 = pts;
  cut_it( 0, k, pts2 );

  printf("%.2f\n", maxarea);
  return true;
}
