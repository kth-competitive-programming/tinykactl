/* KTH ACM Contest Template Library
 *
 * Numerical/BigInt/bigint_simple
 *
 * Credit:
 *   By David Rydh
 */

class BigInt {
  // If no multiplication
  /*  static const int NUMDIGITS = 9;
      static const int MAX = 1000000000; // 10^NUMDIGITS = 1e9
  */
  // If multiplication should be used
  static const int NUMDIGITS = 4;
  static const int MAX = 10000; // 10^NUMDIGITS = 1e4

  int *a;
  int l, res;

  void fix() { // Fix carry (when carry is -1, 0, +1)
    l = 1;
    for( int i=0; i<res; i++ ) {
      if( a[i] >= MAX ) {
	a[i] -= MAX;
	a[i+1]++;
      } else if( a[i] < 0 ) {
	a[i] += MAX;
	a[i+1]--;
      }
      if( a[i] != 0 )
	l = i+1;
    }
  }

  void set( const BigInt &x, int _res ) {
    int *newA = new int[res=_res];
    int i;

    for( i=0; i<x.l; i++ )
      newA[i] = x.a[i];
    for( ; i<res; i++ )
      newA[i] = 0;

    delete[] a;
    a = newA;
    l = x.l;
  }

public:
  static const BigInt zero;
  static const BigInt one;

  BigInt( unsigned int x=0 ) {
    a = new int[res=2];

    a[0] = x%MAX;
    a[1] = x/MAX;
    l = (x>=(unsigned)MAX ? 2:1);
  }
  BigInt( const BigInt &x ) {
    a = (int *)0;
    set( x, x.l );
  }
  ~BigInt() {
    delete[] a;
  }

  BigInt &operator=( const BigInt &x ) {
    set( x, x.l );
    return *this;
  }

  BigInt & operator+=( const BigInt &x ) {
    // Alloc larger array if there could be an overflow
    if( x.l > res || (l==res && x.l==res) )
      set( *this, x.l*2 );

    for( int i=0; i<x.l; i++ )
      a[i] += x.a[i];
    fix();

    return *this;
  }

  BigInt & operator-=( const BigInt &x ) {
    for( int i=0; i<x.l; i++ )
      a[i] -= x.a[i];
    fix();

    return *this;
  }

  BigInt & operator*=( const BigInt &x ) {
    BigInt prod;

    prod.set( 0, (l+x.l+1) );

    for( int i=0; i<x.l; i++ ) {
      for( int j=0; j<l; j++ ) {
	int s = prod.a[i+j]+x.a[i]*a[j];

	prod.a[i+j] = s%MAX;
	prod.a[i+j+1] += s/MAX;
      }
    }
    prod.fix();
    *this = prod;

    return *this;
  }

  int comp( const BigInt &x ) const {
    int d = l-x.l;

    if( d != 0 )
      return d;

    for( int i=l-1; i>=0; i-- ) {
      d = a[i]-x.a[i];

      if( d != 0 )
	return d;
    }
    return 0;
  }

  bool operator<( const BigInt &x ) const { return comp(x)<0; }
  bool operator<=( const BigInt &x ) const { return comp(x)<=0; }
  bool operator==( const BigInt &x ) const { return comp(x)==0; }
  bool operator!=( const BigInt &x ) const { return comp(x)!=0; }


  void print( ostream &out=cout ) const {
    bool flag = false;

    for( int i=l-1; i>=0; i-- ) {
      int b = a[i];

      if( flag ) {
	for( int j=MAX/10; j>b; j/=10 )
	  out << '0';
	if( b>0 )
	  out << b;
      } else if( i==0 || b>0 ) {
	out << b;
	flag = b>0;
      }
    }
  }

  void input( istream &in=cin ) {
    *this = 0;

    // Skip leading whitespace
    char c=' ';
    while(c==' ' || c=='\t' || c==10 || c==13) {
      in.get(c);
      if( !in.good() )
	return;
    }

    // Read word-wise
    int k=1, n=0;
    while(c>='0' && c<='9' && in.good() ) {
      n=n*10+(c-'0');
      k*=10;

      // Store word
      if( k>=MAX ) {
	*this *= MAX;
	a[0] = n;
	n = 0;
	k = 1;
      }

      in.get(c);
    }
    *this *= k;
    a[0] += n;

    if( in.good() )
      in.putback(c);
  }

  friend ostream &operator<<(ostream &lhs,const BigInt &rhs);
  friend istream &operator>>(istream &lhs,BigInt &rhs);
};

const BigInt BigInt::zero = BigInt(0);
const BigInt BigInt::one = BigInt(1);


ostream & operator<<(ostream &lhs,const BigInt &rhs) {
  rhs.print( lhs );
  return lhs;
}

istream & operator>>(istream &lhs,BigInt &rhs) {
  rhs.input( lhs );
  return lhs;
}
