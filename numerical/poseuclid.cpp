template <class T>
T poseuclid( T a, T b, T &x, T &y ) {
  if( b==T(0) )
    return x = T(1), y = T(0), a;
  else {
    T d = poseuclid( b, a%b, y, x );
    y += a/b*x;
    return d;
  }
}
