#include <iostream>
#include "../tinystl/skip_list.cpp"
#include <stdlib.h>

typedef skip_list<int> sli;

int main(void) {
  sli hej;

  hej.insert(4);
  hej.insert(8);
  hej.insert(122);
  hej.insert(8);
  hej.insert(53);
  hej.insert(23);
  hej.insert(999);
  hej.insert(2);
  hej.insert(5);
  hej.insert(-38723);
  hej.insert(-367);
  hej.insert(0);
  hej.insert(8);
  hej.insert(1 << 20);
  hej.insert(1 << 10);
  hej.insert(1 << 9);
  hej.insert(-77);
  for (sli::const_iterator i = hej.begin(); i != hej.end(); ++i)
    cout << "  " << *i;
  cout << endl;
  hej.erase(hej.find(53));
  hej.erase(hej.find(8));
  hej.erase(hej.find(-38723));
  hej.erase(hej.find(1 << 20));
  hej.erase(hej.find(-77));
  for (sli::const_iterator i = hej.begin(); i != hej.end(); ++i)
    cout << "  " << *i;
  cout << endl;
  return 0;
}
