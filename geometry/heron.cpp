/* KTH ACM Contest Template Library
 *
 * Geometry/Triangle area/Heron's formula
 *
 * Credit:
 *   Heron
 *   By Mattias de Zalenski
 */
#include <cmath>

double heron(double a, double b, double c) {
  double s=(a+b+c)/2;
  return sqrt(s*(s-a)*(s-b)*(s-c));
}

template <class P> double heron(P A, P B, P C) {
  return heron(dist(B-C), dist(C-A), dist(A-B));
}
