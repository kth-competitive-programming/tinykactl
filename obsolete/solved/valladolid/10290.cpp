/******************************************
 *
 * @JUDGE_ID: 16100CR 10290 C++ ""
 *
 * Problem 10290 "{sum+=i++} to Reach N"
 *
 * David Rydh, <f99-dry@nada.kth.se>
 * October 2002
 *****************************************/

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

#include "../../numerical/ndivisors_prob.cpp"
#include "../../numerical/primes_many_fast.cpp"


const int N = 100000; // max^(1/3)
primes_many_fast pr(N);

int main() {
  string s;

  while( getline( cin, s ) ) {
    unsigned long long n=0;

    for( unsigned int i=0; i<s.length(); i++ ) {
      n*=10;
      n+=s[i]-'0';
    }

    while( n % 2 == 0 )
      n /= 2;
    cout << ndivisors( n, pr.primes ) << endl;
  }

  return 0;
}
