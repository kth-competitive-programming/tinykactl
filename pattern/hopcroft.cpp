#include <set>

template <class T>
int count(T s, int Q) { // Count the number of bits in s
  int c(0); T zero(0), one(1);
  for (int x = 0; x < Q; ++x)
    if ((s & one << x) != zero)
      c++;
  return c;
}

template <class T, class F> // Hopcroft state minimization.
set<T> hopcroft(T q, T f, // all states q, finishing states f
		int S, int Q, // number of symbols S and states Q
		F &d) {  // function d(state, symbol) -> next states
  set<T> w, p;
  w.insert(f); w.insert(q & ~f); // work list
  p.insert(f); p.insert(q & ~f); // initial partition
  while (!w.empty()) {
    T s = *w.begin(); w.erase(w.begin()); // pick a set of states s
    for (int a = 0; a < S; ++a) {
      T i(0), zero(0), one(1); // find the set of states i,
      for (int x = 0; x < Q; ++x) // that can reach a state in s,
	if ((s & d[x][a]) != zero) // given the symbol a
	  i |= one << x;
      typename set<T>::iterator it = p.begin();
      while (it != p.end()) { // refine the partition around i
	T r = *it; T r1 = r & i, r2 = r & ~i;
	if (r1 != zero && r2 != zero) {
	  if (w.count(r) == 0) // put either min{r1, r2}
	    w.insert(count(r1, Q) < count(r2, Q) ? r1 : r2);
	  else // or both{r1, r2} in worklist
	    w.erase(r), w.insert(r1), w.insert(r2);
	  p.erase(it++), p.insert(r1), p.insert(r2);
	}
	else
	  ++it;
      }
    }
  }
  return p; // returns a state partition
}

/*Pseudo-code:
W,P <- {F,Q-F}
while W not empty
  take S from W
  for a in Symb
    I_a=deltainv_a(S)
    for R in P
      R1=R&I_a;R2=R&~I_a;
      R->{R1,R2} in P
      if R in W
        R->{R1,R2} in W
      else
        min{R1,R2} to W
*/

// if used with bitset<N>:
namespace std { // operator < required by set, must be _in_ namespace std
  template <size_t N> bool operator<(const bitset<N> &x, const bitset<N> &y) {
    for (int i = 0; i < N; ++i)
      if (x[i] != y[i]) return x[i] < y[i];
    return false;
  }
}


/*Alternative count:
int count(int x) {
  x = (x & 0x55555555) + (x >> 1 & 0x55555555);
  x = (x & 0x33333333) + (x >> 2 & 0x33333333);
  x = (x & 0x0f0f0f0f) + (x >> 4 & 0x0f0f0f0f);
  x = (x & 0x00ff00ff) + (x >> 8 & 0x00ff00ff);
  x = (x & 0x0000ffff) + (x >>16 & 0x0000ffff);
  return x;
}
template <size_t N> int count(const bitset<N> &b) { return b.count(); }
*/
