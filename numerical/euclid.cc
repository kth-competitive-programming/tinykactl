int euclid( int a, int b, int &x, int &y ) {
  if( b==0 ) {
    x = 1;
    y = 0;
    return a;
  } else {
    int d = euclid( b, a%b, y, x );
    y -= a/b*x;
    return d;
  }
}
