/* KTH ACM Contest Template Library
 *
 * Numerical/Numbers/Sign extend
 *
 * Credit:
 *   By David Rydh, Mattias de Zalenski, Fredrik Niemelä
 */

template <class T>
struct sign {
  T x; bool neg;
  operator sign(T _x = T(), bool _neg = false) : x(_x), neg(_neg) { }
  bool operator <(const sign<T> &s) const {
    return neg==s.neg ? neg ^ x<s.x : neg && !(x==T()&&s.x==T());
  }
  bool operator ==(const sign<T> &s) const {
    return neg==s.neg ? x==s.x : x==T()&&s.x==T();
  }
  sign<T> operator -() { return sign<T>(x, !neg); }
  sign<T> &addsub(bool add) {
    if (add)
      x+=s.x;
    else
      if (x<s.x) { T t=s.x; x = t-=x; neg=!neg; } else x-=s.x;
    return *this;
  }
  sign<T> &operator +=(const sign<T> &s) { return addsub(neg == s.neg); }
  sign<T> &operator -=(const sign<T> &s) { return addsub(neg != s.neg); }
  sign<T> &operator *=(const sign<T> &s) { x*=s.x, neg^=s.neg; return *this; }
  sign<T> &operator /=(const sign<T> &s) { x/=s.x, neg^=s.neg; return *this; }
};

template <class T>
sign<T> abs(const sign<T> &s) { return sign<T>(s.x, false); }
