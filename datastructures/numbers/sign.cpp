/* KTH ACM Contest Template Library
 *
 * Numerical/Numbers/Sign extend
 *
 * Credit:
 *   By Mattias de Zalenski, Per Austrin, Fredrik Niemelä
 */

template <class T>
struct sign {
  static const T zero; // Requires declaration: const T sign<T>::zero = T();
  T x; bool neg;
  operator sign(T _x = zero, bool _neg = false) : x(_x), neg(_neg) { }
  bool operator <(const sign<T> &s) const {
    return neg==s.neg ? neg ? x>s.x : x<s.x : neg && !(x==zero&&s.x==zero);
  }
  bool operator ==(const sign<T> &s) const {
    return neg==s.neg ? x==s.x : x==zero&&s.x==zero;
  }
  sign<T> operator -() { return sign<T>(x, !neg); }
  sign<T> &addsub(bool add) {
    if (add) x+=s.x;
    else if (x<s.x) { T t=s.x; x = t-=x; neg=!neg; }
    else x-=s.x;
    return *this;
  }
  sign<T> &operator +=(const sign<T> &s) { return addsub(neg == s.neg); }
  sign<T> &operator -=(const sign<T> &s) { return addsub(neg != s.neg); }
  sign<T> &operator *=(const sign<T> &s) { x*=s.x, neg^=s.neg; return *this; }
  sign<T> &operator /=(const sign<T> &s) { x/=s.x, neg^=s.neg; return *this; }
};

template <class T>
sign<T> abs(const sign<T> &s) { return sign<T>(s.x, false); }

template <class T>
istream &operator >>(istream &in, sign<T> &s) {
  char c; in >> c; s.neg = c == '-'; if (!s.neg) in.unget(); in >> s.x;
}

template <class T>
ostream &operator <<(ostream &out, const sign<T> &s) {
  if (s.neg && s.x != s.zero) out << '-'; out << s.x;
}
