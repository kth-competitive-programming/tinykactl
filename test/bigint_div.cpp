#include <utility>
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>

using namespace std;
using namespace std::rel_ops;

#include "../datastructures/numbers/bigint_full.cpp"
#include "../datastructures/numbers/bigint.cpp"
#include "../numerical/pseudo.cpp"

typedef unsigned long ul;
typedef unsigned long long ull;
typedef bigint<ul, ull> big;
const ul big::P = ul(1e6); // or 1e18, not using multiplication
const unsigned big::N = 6; // or 18

typedef big Bignum;

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
  string s;
  ostringstream sout;//(s);
  sout << bi << endl;
  istringstream sin(sout.str());
  sin >> bn;
}

void convert( const Bignum &bn, BigInt &bi ) {
  string s;
  ostringstream sout;//(s);
  sout << bn << endl;
  istringstream sin(sout.str());
  sin >> bi;
}

int main( void ) {
  int t1 = 0, t2 = 0, t;
  const int N = 200;

  // ******** MULTIPLICATION ********
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
  cout << "Tot: " << double(clock()-tot)/CLOCKS_PER_SEC/N << " s" << endl;
  cout << "BigInt: " << (double)t1/CLOCKS_PER_SEC/N << " s" << endl;
  cout << "Bignum: " << (double)t2/CLOCKS_PER_SEC/N << " s" << endl;

  // ******** DIVISION ********
  t1 = t2 = 0;
  
  cout << endl << "Division (1200/800)" << endl;
  for( int i=0; i<N; i++ ) {
    BigInt bi, bi2;    Bignum bn, bn2;
    

    bipseudo( 1200, bi, bn );
    bipseudo( 800, bi2, bn2 );

    //cout << bi << endl << bi2 << endl;

    t = clock();    bi %= bi2;    t1 += clock()-t;
    //cout << "x" << endl;
    t = clock();    bn %= bn2;    t2 += clock()-t;

    convert( bn, bi2 );
    if( bi != bi2 ) {
      cout << "ERROR! Mismatch!!!" << endl;
      cout << bi << endl << bi2 << endl;
    }
  }
  cout << "BigInt: " << (double)t1/CLOCKS_PER_SEC/N << " s" << endl;
  cout << "Bignum: " << (double)t2/CLOCKS_PER_SEC/N << " s" << endl;

  /*
  cout << endl << "sqrt (100)" << endl;
  for( int i=0; i<N; i++ ) {
    BigInt bi, bi2;    Bignum bn, bn2;

    bipseudo( 100, bi, bn );

    t = clock();    bi.sqrt(bi2);    t1 += clock()-t;
        cout << bi2 << endl;
    t = clock();    bn2 = sqrt(bn);   t2 += clock()-t;
        cout << bn2 << endl;

    convert( bn2, bi );
    if( bi != bi2 )      cout << "ERROR! Mismatch!!!" << endl;
  }
  cout << "BigInt: " << (double)t1/CLOCKS_PER_SEC/N << " s" << endl;
  cout << "Bignum: " << (double)t2/CLOCKS_PER_SEC/N << " s" << endl;
  */
}
