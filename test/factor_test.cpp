#include "../numerical/factor.cpp"
#include <iostream>

void printFactors(int n) {
  vpii facs = Factor(n);
  cout << n << " = ";
  for (vector<pii>::iterator i = facs.begin(); i != facs.end(); ++i) {
    if (i != facs.begin())
      cout << " * ";
    cout << i->first << "^" << i->second;
  }
  cout << endl;
}

int main(void) {
  int i;
  while (cin >> i)
    printFactors(i);
}

