/* KTH ACM Contest Template Library
 *
 * Pattern Matching/Automata/DFA, and NFA->DFA reduction
 *
 * Credit:
 *   By Per Austrin
 */


#include "nfa.cpp" // nfa.cpp includes vector, and other necessities.
#include <map>

struct DFA {
  vector<vi> states;
  vector<bool> accepting;

  DFA() {}
  DFA(const NFA& nfa) {
    map<StateSet, int> stateIdx;
    vector<StateSet> stateSets;
    unsigned int state = 0;
    
    /* Create initial state */
    StateSet start;
    start.insert(0);
    nfa.epsilonClosure(start);
    stateIdx[start] = 1;
    stateSets.push_back(start);
    states.push_back(vi(256, -1));
    accepting.push_back(false);

    /* Process states as they come */
    while (state < states.size()) {
      StateSet s = stateSets[state];
      /* Is this an accepting state? */
      if (s.count(nfa.accept))
	accepting[state] = true;
      /* Which chars trigger state transitions from this state? */
      for (int i = 1; i < 256; ++i) {
	StateSet nS = nfa.nextStates(s, i);
	if (!nS.empty()) {
	  nfa.epsilonClosure(nS);
	  int& idx = stateIdx[nS];
	  /* Is this a new state? */
	  if (idx == 0) {
	    states.push_back(vi(256, -1));
	    accepting.push_back(false);
	    stateSets.push_back(nS);
	    idx = states.size();
	  }
	  /* Add state transition */
	  states[state][i] = idx-1;
	}
      }
      ++state;
    }
  }

  size_t match(string::const_iterator s) {
    int state = 0;
    string::const_iterator begin = s;
    size_t lastAccept = string::npos;
    while (state != -1) {
      if (accepting[state])
	lastAccept = distance(begin, s);
      if (!*s)
	break;
      state = states[state][*s++];
    }
    return lastAccept;
  }
};
