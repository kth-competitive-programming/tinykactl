/* KTH ACM Contest Template Library
 *
 * Numerical/Numbers/Sign extend
 *
 * Credit:
 *   By Mattias de Zalenski, Per Austrin, Fredrik Niemelä
 */

template <class T>
struct sign {
  static const T zero;
  T x; bool n;
  operator sign(T _x = zero, bool _n = false): x(_x), n(_n) {}
  bool operator <(const sign &s) const {
    return n==s.n ? n ? x>s.x : x<s.x : n && !(x==zero&&s.x==zero);
  }
  bool operator ==(const sign &s) const {
    return n==s.n ? x==s.x : x==zero&&s.x==zero;
  }
  sign operator -() { return sign(x, !n); }
  sign &as(bool add) {
    if (add) x+=s.x;
    else if (x<s.x) { T t=s.x; x = t-=x; n = !n; }
    else x-=s.x;
    return *this;
  }
  sign &operator+=(const sign &s){return as(n == s.n); }
  sign &operator-=(const sign &s){return as(n != s.n); }
  sign &operator*=(const sign &s){x*=s.x,n^=s.n; return *this;}
  sign &operator/=(const sign &s){x/=s.x,n^=s.n; return *this;}
};

template <class T>
sign<T> abs(const sign<T> &s) { return sign<T>(s.x, false); }

template <class T>
istream &operator >>(istream &in, sign<T> &s) {
  char c; in>>c; s.n = c=='-'; if (!s.n) in.unget(); in>>s.x;
}

template <class T>
ostream &operator <<(ostream &out, const sign<T> &s) {
  if (s.n && s.x != s.zero) out << '-'; out << s.x;
}
