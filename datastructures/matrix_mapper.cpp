/* KTH ACM Contest Template Library
 *
 * Datastructures/Two-index matrices in one-index arrays/Matrix mapper
 *
 * Credit:
 *   By Mattias de Zalenski
 *   Dedicated to Morpheus
 */

template <class R> // random access iterator
struct matrix_mapper {
  R array; int c; matrix_mapper(R _array, int _c) : array(_array), c(_c) { }
  R operator [](int row) { return array + row * c; }
  int operator ()(int row, int col) { return row * c + col; }
};


// Normally, the matrix_mapper will be used with a vector.
// It is then convenient to just specify the stored type,
// and construct the mapper with a vector reference.
// This convenience comes at a moderate price:
#include <vector>

template <class T>
struct vector_matrix_mapper :
  public matrix_mapper< vector<T>::iterator > {
  vector_matrix_mapper(vector<T> &v, int c) :
    matrix_mapper< vector<T>::iterator >(v.begin(), c) { }
};
