// Programmerings-SM, KTH Stockholm, 20020928
//
// Template for KTH-Nada, Team Niemelae
//  Fredrik Niemelae, David Rydh, Mattias de Zalenski
//
// Problem: _

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <cmath>

using namespace std;

const int N = 1000;
const bool debug = true;

void init();
bool solve(int P);

int main() {
  init();

  // while-solve
  int n = 0;
  while (solve(n))
    ++n;

  return 0;
}

void init() {
}

string s;
int apps;

int parmatch(int pos) {
  int level = 1;
  while (pos < s.size() && level > 0) {
    switch (s[pos]) {
    case '(': level++; break;
    case ')': level--; break;
    }
    pos++;
  }
  return pos;
}

void eval(int pos) {
  while (pos < s.size()) {
    //if (debug) cerr << pos << ':' << s << endl;
    char var;
    int s1, s2;
    string subst, t;
    if (apps > N) return;
    switch (s[pos]) {
    case '(': pos++; break;
    case 'L':
      var = s[pos + 1];
      s1 = parmatch(pos + 3);
      if (s1 < s.size()) {
	s2 = parmatch(s1);
	if (s2 < s.size()) s2--;
	subst = s.substr(s1, s2 - s1);
	//if (debug) cerr << var << '/' << subst << endl;
	t = "";
	for (int i = pos + 3; i < s1 - 1; i++)
	  if (s[i] == 'L' && s[i + 1] == var) { // var becomes bound
	    int j = parmatch(i + 3) - 1;
	    t += s.substr(i, j - i);
	    i = j;
	  }
	  else if (s[i] == var) // subst application
	    t += subst, apps++;
	  else
	    t += s[i];
	s = s.substr(0, pos - 1) + t + s.substr(s2);
	pos--;
      }
      else
	pos += 3;
      break;
    default:
      apps++;
      pos += 2;
      break;
    }
  }
}

bool solve(int P) {
  cin >> s;
  // remember: if (debug) ...
  apps = 0;
  eval(0);
  if (apps > N)
    cout << "unterminated" << endl;
  else
    cout << s << endl;
  return s != "z";
}
