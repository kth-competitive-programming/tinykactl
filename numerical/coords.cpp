/* KTH ACM Contest Template Library
 *
 * Numerical/Coordinate indices/Simple utility structs
 *
 * Credit:
 *   By Mattias de Zalenski
 */

struct sqrX { // square [rows*]columns
  int c; sqrX(int cols) : c(cols) { }
  int operator()(int row, int col) { return row*c + col; }
  void operator()(int idx, int &row, int &col) { row = idx/c, col = idx%c; }
};

struct cubeX { // cube [levels*]square
  int r, c; cubeX(int rows, int cols) : r(rows), c(cols) { }
  int operator()(int lev, int row, int col) { return (lev*r + row)*c + col; }
  void operator()(int idx, int &lev, int &row, int &col) {
    col = idx%c, idx /= c, row = idx%r, lev = idx/r;
  }
};

struct quadX { // quad [hyper*]cube
  int l, r, c;
  quadX(int levs, int rows, int cols) : l(levs), r(rows), c(cols) { }
  int operator()(int hyp, int lev, int row, int col) {
    return ((hyp*l + lev)*r + row)*c + col;
  }
  void operator()(int idx, int &hyp, int &lev, int &row, int &col) {
    col = idx%c, idx /= c, row = idx%r, idx /= r, lev = idx%l, hyp = idx/l;
  }
};

struct triX { // triangle [row >= col]
  int operator()(int row, int col) { return row * (row + 1) / 2 + col; }
  void operator()(int idx, int &row, int &col) {
    for (row = 0, col = idx; col > row; col -= row) ++row;
  }
};

void dxy(int dir, int &dx, int &dy) { // direction is dir*90 degrees for x, y
  dx = dir & 1 ? 0 : 1 - (dir & 2);
  dy = dir & 1 ? 1 - (dir & 2) : 0;
}
void drc(int dir, int &dr, int &dc) { // direction is NESW for row, column
  dr = dir & 1 ? 0 : (dir & 2) - 1;
  dc = dir & 1 ? 1 - (dir & 2) : 0;
}

void dknight(int dir, int &dr, int &dc) { // chess knight jump
  int DR[] = { -2, -2, -1, 1, 2, 2, 1, -1 };
  int DC[] = { -1, 1, 2, 2, 1, -1, -2, -2 };
  dr = DR[dir], dc = DC[dir];
}
