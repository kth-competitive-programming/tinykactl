/******************************************
 *
 * @JUDGE_ID: 25719RJ 300 C++
 *
 * Problem 300 "Maya Calendar"
 *
 * David Rydh, <f99-dry@nada.kth.se>
 * December 2001
 *****************************************/

#include <cstdlib>
#include <iostream>

//#include <string>
//#include <algorithm>
//#include <map>

#include "../../tinystl/string.cpp"
//#include "../../tinystl/simplemap.cpp"
#include "../../tinystl/map.cpp"

// Haab
string month_names[19] = { "pop", "no", "zip", "zotz", "tzec", "xul",
			   "yoxkin", "mol", "chen", "yax", "zac", "ceh",
			   "mac", "kankin", "muan", "pax", "koyab", "cumhu",
			   "uayet" };

// Tzolkin
string day_names[20] = { "imix", "ik", "akbal", "kan", "chicchan",
			 "cimi", "manik", "lamat", "muluk", "ok",
			 "chuen", "eb", "ben", "ix", "mem",
			 "cib", "caban", "eznab", "canac", "ahau" };

map< string, int>  month_names_s;

int main() {
  int n;

  for( int i=0; i<19; i++ )
    month_names_s.insert( make_pair(month_names[i], i) );

  cin >> n;
  cout << n << endl;

  while( n-- > 0 ) {
    int  haab_nr, haab_month, haab_year;
    int  day;
    int  tzolkin_nr, tzolkin_day, tzolkin_year;
    char month_str[256];

    cin >> haab_nr;
    cin.ignore();
    cin >> month_str >> haab_year;
    haab_month = month_names_s[month_str];

    day = haab_year*365 + haab_month*20 + haab_nr;

    tzolkin_year = day/260;
    day %= 260;
    tzolkin_nr = day%13;
    tzolkin_day = day%20;

    cout << tzolkin_nr+1 << " " << day_names[tzolkin_day]
	 << " " << tzolkin_year << endl;
  }

  return 0;
}
