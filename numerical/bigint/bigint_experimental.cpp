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

/************ OLD **********
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

