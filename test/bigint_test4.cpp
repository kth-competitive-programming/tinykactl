#include <iostream>
#include <strstream>
#include <time.h>

#include "../bigint/1_simple.cpp"
#include "../bigint/2_bignum_jimmy.cpp"
#include "../general/7_random.cpp"

void bipseudo( int size, BigInt &bi, Bignum &bn ) {
  bi = 0;
  bn = 0;

  for( int j=0; j<size/4; j++ ) {
    int a = pseudo() % 10000;
    bi *= 10000;
    bi += a;
    //    bn = bn*10000+a;
    /*    bn *= 10000;
	  bn += a;*/
  }

  // Copy random number from bi -> bn since bignum mult is so slow...
  const int L = 10000;
  char s[L];
  ostrstream sout(s, L);
  istrstream sin(s, L);

  sout << bi << endl;
  sin >> bn;
}

void convert( const Bignum &bn, BigInt &bi ) {
  const int L = 10000;
  char s[L];
  ostrstream sout(s, L);
  istrstream sin(s, L);

  sout << bn << endl;
  sin >> bi;
}

int main( void ) {
  int t1 = 0, t2 = 0, t;
  const int N = 50;
 
  // ******** MULTIPLICATION ********
  /*
  cout << "Multiplication (800*400)" << endl;
  int tot = clock();
  for( int i=0; i<N; i++ ) {
    BigInt bi, bi2;    Bignum bn, bn2;

    bipseudo( 800, bi, bn );
    bipseudo( 400, bi2, bn2 );

    t = clock();    bi *= bi2;    t1 += clock()-t;
    t = clock();    bn *= bn2;    t2 += clock()-t;

    //    convert( bn, bi2 );
    //    if( bi != bi2 )      cout << "ERROR! Mismatch!!!" << endl;
  }
  cout << "Tot: " << double(clock()-tot)/_CLOCKS_PER_SEC_/N << " s" << endl;
  cout << "BigInt: " << (double)t1/_CLOCKS_PER_SEC_/N << " s" << endl;
  cout << "Bignum: " << (double)t2/_CLOCKS_PER_SEC_/N << " s" << endl;
  */

  // ******** DIVISION ********
  
  cout << endl << "Division (800*400)" << endl;
  for( int i=0; i<N; i++ ) {
    BigInt bi, bi2;    Bignum bn, bn2;

    bipseudo( 800, bi, bn );
    bipseudo( 400, bi2, bn2 );

    t = clock();    bi %= bi2;    t1 += clock()-t;
    t = clock();    bn %= bn2;    t2 += clock()-t;

    convert( bn, bi2 );
    if( bi != bi2 ) {
      cout << "ERROR! Mismatch!!!" << endl;
      cout << bi << endl << bi2 << endl;
    }
  }
  cout << "BigInt: " << (double)t1/_CLOCKS_PER_SEC_/N << " s" << endl;
  cout << "Bignum: " << (double)t2/_CLOCKS_PER_SEC_/N << " s" << endl;
  
  /*
  cout << endl << "sqrt (400)" << endl;
  for( int i=0; i<N; i++ ) {
    BigInt bi, bi2;    Bignum bn, bn2;

    bipseudo( 200, bi, bn );

    t = clock();    bi.sqrt(bi2);    t1 += clock()-t;
        cout << bi2 << endl;
    t = clock();    bn2 = sqrt(bn);   t2 += clock()-t;
        cout << bn2 << endl;

    convert( bn2, bi );
    if( bi != bi2 )      cout << "ERROR! Mismatch!!!" << endl;
  }
  cout << "BigInt: " << (double)t1/_CLOCKS_PER_SEC_/N << " s" << endl;
  cout << "Bignum: " << (double)t2/_CLOCKS_PER_SEC_/N << " s" << endl;
  */
}
