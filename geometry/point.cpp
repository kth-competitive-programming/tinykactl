/* KTH ACM Contest Template Library
 *
 * Geometry/Primitives/Point structure
 *
 * Credit:
 *   By Mattias de Zalenski
 */

template <class T>
struct point {
  typedef T coord_type;
  typedef point S;
  typedef const S &R;
  T x, y;
  point(T _x=T(), T _y=T()) : x(_x), y(_y) { }
  bool operator< (R p) const {
    return x < p.x || x <= p.x && y < p.y;
  }
  S operator-(R p) const { return S(x - p.x, y - p.y); }
  S operator+(R p) const { return S(x + p.x, y + p.y); }
  S operator/(T d) const { return S(x / d, y / d); }
  T dot(R p)  const  { return x*p.x + y*p.y; }
  T cross(R p) const { return x*p.y - y*p.x; }
  T dist2() const { return dot(*this); }

  T dx(R p) const { return p.x - x; }
  T dy(R p) const { return p.y - y; }

  double dist() const { return sqrt(dist2()); }
  double angle() const { return atan2(y, x); }

  P unit() const { return *this / dist(); }
  P perp() const { return P(-y, x); }
  P normal() const { return perp().unit(); }

  double theta() {
    if (x==0 && y==0) return 0;
    double t = y / (x<0 ^ y<0 ? x-y : x+y);
    return x<0 ? y<0 ? t-2 : t+2 : t;
  }
};
