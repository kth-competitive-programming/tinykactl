#include <cstdlib>
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main(int argc, char *argv[]) {
  int n = 72;
  if (argc > 1)
    n = atoi(argv[1]);
  string s;
  while (getline(cin, s)) {
    while (s.size() > n) {
      int i = n - 1;
      while (i > 0 && isalnum(s[i]))
	--i;
      if (i == 0)
	i = n;
      else
	++i;
      cout << s.substr(0, i) << " \\" << endl;
      s = s.substr(i);
    }
    cout << s << endl;
  }
  return 0;
}
