/* KTH ACM Contest Template Library
 *
 * Pattern Matching/Regular Expressions/RegExp -> NFA -> DFA
 *
 * Credit:
 *   By Per Austrin, 2002-10-2?
 */


#include "nfa.cc" // nfa.cc includes vector, and other necessities.
#include <map>

/* Note: some general cleaning up between this file and nfa.cc is to
 *       be expected in the near future. I hope.
 */

class RegExp {
protected:
  vector<vi> states;
  vector<bool> accepting;

public:
  RegExp(string& regexp) {
    map<StateSet, int> stateIdx;
    vector<StateSet> stateSets;
    unsigned int state = 0;
    NFA nfa(regexp); // Create the NFA for the regexp
    
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
  

  /* Returns the length of the longest string beginning in s which
   * _completely matches_ the regular expression. If no prefix matches
   * the regexp, the return value is string::npos.
   *
   * Time complexity: O(n), where n is the length of the string.
   */
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
