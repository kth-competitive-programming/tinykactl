/* @JUDGE_ID: 16129WM 314 C++ "" */
// Problem: Robot
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
#include "../graph/prijm.cpp"
#include "../numerical/coords.cpp"
#include "../datastructures/null_vector.cpp"

int rows, cols;
struct robofun {
  vector<bool> &open; robofun(vector<bool> &_open) : open(_open) { }
  template <class F> void operator ()(int node, F &f) {
    cubeX X(rows, cols);
    int dir, r, c; X(node, dir, r, c);
    f(make_pair(X(dir + 1 & 3, r, c), 1)); // turn right
    f(make_pair(X(dir + 3 & 3, r, c), 1)); // turn left
    int dr, dc; drc(dir, dr, dc);
    for (int i = 0; i < 3 && open[X(0, r += dr, c += dc)]; ++i)
      f(make_pair(X(dir, r, c), 1)); // walk up to three steps
  }
};

bool solve() {
  cin >> rows >> cols;
  if (!cin || rows == 0 && cols == 0) return false;

  sqrX X(cols);
  vector<int> v(X(rows, 0));
  int p = 0;
  for (int i = 0; i < rows; ++i)
    for (int j = 0; j < cols; ++j)
      cin >> v[p++];

  // mark positions that are open to the robot (no adjacent obstacles)
  // shift to keep a frame of false values, to avoid edge coordinate checks
  sqrX Y(cols + 1);
  vector<bool> open(Y(rows + 1, 0), false);
  for (int i = 1; i < rows; ++i)
    for (int j = 1; j < cols; ++j)
      open[Y(i, j)] =
	v[X(i - 1, j - 1)] + v[X(i - 1, j)] +
	v[X(i, j - 1)] + v[X(i, j)] == 0;
  ++rows, ++cols; // more grid-line positions than squares

  // position and direction
  string s;
  int b1, b2, e1, e2, dir = 0; // north
  cin >> b1 >> b2 >> e1 >> e2 >> s;
  if (s == "east") dir = 1;
  else if (s == "south") dir = 2;
  else if (s == "west") dir = 3;

  // set up dijkstra
  const int inf = 1 << 29;
  robofun robo(open);
  cubeX Z(rows, cols);
  vector<int> dist(Z(4, 0, 0), inf);
  null_vector<int> path;
  int start = Z(dir, b1, b2);

  dijkstra(robo, dist, path, start);

  // accept the robot facing any direction at the destination point
  int d = inf;
  for (int i = 0; i < 4; ++i)
    d = min(d, dist[Z(i, e1, e2)]);

  cout << (d == inf ? -1 : d) << endl;

  return true;
}

int main() {
  while (solve());
  return 0;
}
