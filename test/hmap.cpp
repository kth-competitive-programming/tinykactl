#include "../tinystl/hmap.cpp"
#include<iostream.h>




int main()
{
  hmap<float, int> hm(1);
  float s;
  int n;
  hm.clear();
  while (cin >> s >> n) {
    if (hm.member(s))
      if (n == -1) 
	cout << "removing " << s  << endl, hm.remove(s);
      else
	cout << "changing " << hm[s] << " to " << n << endl;
    else 
      cout << "new entry " << s << " has value " << n << endl;
    if (n != -1) hm[s] = n;
    
  }  
  return 0;
}






