/*****************************************************************************
 * 
 * BigInt1: simple
 * ===============
 *
 * Simple dynamic BigInt class with only positive integers and +,-,*,/.
 * (can easily be reduced not to support * and /)
 *
 * ------------------------------------------------------------------------- *
 *
 * NADA acmlib (10 March 2002)
 * Templates for KTH-NADA, Ballons'R'Us, ACM 2001-2002
 *   Swedish competition, Linköping 6 Oct 2001
 *   Revised for SWERC, Portu, Portugal 17 Nov 2001
 *   Revised for World Finals, Honolulu, 23 Mar 2002
 *   David Rydh, Mattias de Zalenski, Fredrik Niemelä
 *
 *****************************************************************************/

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


  BigInt & operator/=( const BigInt &x ) {
    BigInt rem;

    div( x, *this, rem );
    return *this;
  }

  BigInt & operator%=( const BigInt &x ) {
    BigInt quot;

    div( x, quot, *this );
    return *this;
  }

  void div( const BigInt &d, BigInt &quot, BigInt &rem ) const {
    BigInt divisor = d;
    int scaling = 0;

    // Remainder = dividend
    rem.set( *this, l+1 );

    // Quotient = 0
    quot.set( 0, (l-d.l+1) );

    // Make sure a[l-1] is >=MAX/10 (for better guesses)
    if( divisor.l > 1 ) {
      int a = divisor.a[ divisor.l-1 ];

      while( (a*=10) < MAX ) {
	rem *= 10;
	divisor *= 10;
	scaling++;
      }
    }

    while( divisor <= rem ) {
      // Guess a quotient and subtract from remainder. We always
      // underestimate the quotient so we won't get any underflow.
      int dh = divisor.a[ divisor.l-1 ]+1;
      BigInt qadd;

      if( rem.l > 1 ) {
	int guess = (rem.a[ rem.l-1 ]*MAX + rem.a[ rem.l-2 ])/dh;

	// Scale guess to right position
	qadd.set( 0, rem.l-divisor.l+1 );
	qadd.a[ rem.l-divisor.l ] = guess/MAX;
	if( rem.l > divisor.l )
	  qadd.a[ rem.l-divisor.l-1 ] = guess%MAX;
	qadd.l = rem.l-divisor.l+1;
	if( guess < MAX ) {
	  if( qadd.l > 1 )
	    qadd.l--;
	  else           // (This implies that guess == 0)
	    qadd.a[0]++; // Fix case where x/x = 0 due to round-down.
	}
      } else {
	int guess = rem.a[0]/dh;
	if( guess == 0 ) guess++;

	qadd.set( guess, 1 );
      }

      // Add guess to quotient
      quot += qadd;

      // Subtract div*guess from remainder
      BigInt remsub( qadd );
      remsub *= divisor;
      rem -= remsub;
    }

    while( scaling > 0 ) {
      rem /= 10;
      scaling--;
    }
  }

  /*  
  void div( const BigInt &d, BigInt &quot, BigInt &rem ) const {
    BigInt rec;
    int    shift = l+1; // If shift=l we will get an almost correct answer.
                        // The problem is that the last digit isn't always
			// rounded down.

    d.reciprocal( rec, shift );
    quot = *this;
    quot *= rec;
    // Shift down
    for( int i=0; i<quot.l; i++ )
      quot.a[i] = (i+shift<quot.l) ? quot.a[i+shift] : 0;
    quot.l -= shift;

    rem = 0;  // UNIMPLEMENTED
  }

  void reciprocal( BigInt &r, int shift ) const {
    // r = MAX^shift / (*this) = w / (*this)  (not necessarit corr. rounded)
    // Newton-Raphson's method. Recursion: y' = y-(w/y-x)/(-w/y^2)=2y-xy^2/w
    if( shift < l-1 ) {
      r = 0;
      return;
    }

    int guess = MAX/a[l-1];
    r.set( 0, shift-l+2 );

    //    cout << guess << endl;
    r.a[shift-l+1] = guess/MAX;
    if( shift >= l )
      r.a[shift-l] = guess%MAX;
    r.l = shift-l+2;
    while( true ) {
      //      cout << r << endl;
      BigInt d = r;
      d *= r;
      d *= (*this);
      for( int i=0; i<d.l; i++ )
	d.a[i] = (i+shift<d.l) ? d.a[i+shift] : 0;
      d.l = d.l>shift ? d.l-shift : 1;
      if( d == r )
	break;
      r += r;
      r -= d;
    }
  }
  */
  void sqrt( BigInt &res ) const {
    // Newton-Raphson's method. Recursion: y' = y-(y^2-x)/(2y) = (y+x/y)/2
    res = *this;
    res /= 2;

    while( true ) {
      BigInt d = *this;
      d /= res;
      d += res;
      d /= 2;
      if( d==res )
	break;
      res = d;
    }
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

  /*
  void print() const {
    bool flag = false;

    for( int i=l-1; i>=0; i-- ) {
      int b = a[i];

      if( b<0 ) {
	cout << "ERROR!" << endl;
	throw(-1);
      }

      for( int j=0; j<NUMDIGITS; j++ ) {
	int d = b/(MAX/10);

	if( d!=0 || flag ) {
	  flag = true;
	  cout << d;
	}
	b %= MAX/10;
	b*=10;
      }
    }
    if( !flag )
      cout << '0';
  }
  */

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

ostream & operator<<(ostream &lhs,const BigInt &rhs) {
  rhs.print( lhs );
  return lhs;
}

istream & operator>>(istream &lhs,BigInt &rhs) {
  rhs.input( lhs );
  return lhs;
}
