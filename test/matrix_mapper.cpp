#include <iostream>
using namespace std;

#include "../datastructures/matrix_mapper.cpp"

int main() {
  typedef vector<int> Vi;
  Vi v(144 * 2);
  //matrix_mapper< vector<int>::iterator > m(v.begin(), 12);
  vector_matrix_mapper<int> m(v, 12); // convenience at high price
  for (int i = 0; i < 12; ++i)
    for (int j = 0; j < 12; ++j)
      m[i][j] = i + j; // use as a matrix
  for (int i = 0; i < 12; ++i) {
    for (int j = 0; j < 12; ++j) {
      if (j > 0) cout << " ";
      cout << v[m(i, j)]; // use as a function
    }
    cout << endl;
  }
}
