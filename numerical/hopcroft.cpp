#include <set>

template <class T>
int count(T s, int Q) { // Count the number of bits in s
  int c(0); T zero(0), one(1); // Alternatively:
  for (int x = 0; x < Q; ++x) // use int bit manipulation
    if ((s & one << x) != zero) // or bitset<N>::count()!
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
  while (!w.empty()) { // pick a set of states,
    T s = *w.begin(); w.erase(w.begin()); // s
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
      R->{R1,R2} in W  OR  min{R1,R2} to W, if R is not in W
*/
// if used with bitset<N>:
// operator < required by set, must be _in_ namespace std
