/*****************************************************************************
 * 
 * General2: io functions input, output, line, input_n
 * ===========================================================
 *
 * input_n(n, p)
 *
 *
 * ------------------------------------------------------------------------- *
 *
 * NADA acmlib (10 March 2002)
 * Templates for KTH-NADA, Ballons'R'Us, ACM 2001-2002
 *   Swedish competition, Link?ping 6 Oct 2001
 *   Revised for SWERC, Portu, Portugal 17 Nov 2001
 *   Revised for World Finals, Honolulu, 23 Mar 2002
 *   David Rydh, Mattias de Zalenski, Fredrik Niemel?
 *
 *****************************************************************************/

#include <iostream>

using namespace std;

template <class T>
void input_n(int n, T p) { for (int i = 0; i < n; i++) cin >> p[i]; }

template <class T>
void input(int &n, T p) { cin >> n; input_n(n, p); }

template <class T>
void input(int &m, int &n, T p) {
  cin >> m >> n;
  for (int i = 0; i < m; i++) input_n(n, p[i]);
}

template <class T>
void output(int n, T p) {
  while (n > 1) { cout << *p++ << ' '; n--; }
  if (n > 0) { cout << *p++; n--; }
}

void line() { cout << endl; }
template <class T> void line(T x) { cout << x << endl; }
template <class T> void line(int n, T p) { output(n, p); cout << endl; }
