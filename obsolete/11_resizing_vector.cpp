/*****************************************************************************
 * 
 * General11: misc container resize_vector
 * ===========================================================
 *
 * A vector that resizes in operator[].
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

#include <vector>

template <class T>
struct resizing_vector : public vector<T> {
  T &operator [](int index) {
    if (size() <= index) resize(index + 1);
    return vector<T>::operator[](index);
  }
};
