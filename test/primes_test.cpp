#include <iostream>

#include "../numerical/prime_sieve.cpp"
#include "../numerical/primes.cpp"

int main( void ) {
  prime_sieve p(100);
  primes<int> p2;

  p2.generate(100);

  for( int i=2; i<100; i++ )
    cout << p.isprime(i);

  cout << endl;

  for( int i=2; i<100; i++ )
    cout << (p2.factor(i)==i);

  cout << endl;

  return 0;
}
