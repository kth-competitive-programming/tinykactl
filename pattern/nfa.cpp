/* KTH ACM Contest Template Library
 *
 * Automata Theory/Finite State Automata/NFA:s
 *
 * Credit:
 *   By Per Austrin
 */

#include <queue> /* Used in the epsilon closure */
#include <vector>
#include <set>
#include <string>

/* Note: some general cleaning up between this file and regexp.cc is to
 *       be expected in the near future. I hope.
 */

typedef vector<int> vi;
typedef set<int> StateSet;

class NFA {
protected:
  typedef vector<vi> NFAState;
  typedef vector<NFAState> NFAStates;
  NFAStates states;
  
  int parseRegExp(string::const_iterator& i, int entry) {
    int res = entry;
    char literal = 0;
    while (*i && *i != ')') {
      switch (*i) {
      case '"':
	literal = ~literal;
	break;
      case '(':
	res = parseRegExp(++i, res);
	break;
      case '|': {
	int end = parseRegExp(++i, entry);
	states[end][0].push_back(states.size());
	states[res][0].push_back(states.size());
	res = states.size();
	states.push_back(NFAState(256, vi()));
	--i;
	break;
      }
      case '*':
	states[res][0].push_back(entry);
	res = entry;
	break;
      case '[':
	while (*++i != ']' && *i) {
	  states[res][*i].push_back(states.size());
	}
	res = states.size();
	states.push_back(NFAState(256, vi()));
	break;
      default:
	states[res][(unsigned char)*i].push_back(states.size());
	res = states.size();
	states.push_back(NFAState(256, vi()));
      }
      if (*i)  ++i;
    }
    return res;
  }

public:
  int accept;
  
  NFA(string& regexp) {
    // Necessary due to the mean and evil way in which string works.
    *(regexp.begin() + regexp.length()) = 0;
    states.push_back(NFAState(256, vi()));
    string::const_iterator i = regexp.begin();
    accept = parseRegExp(i, 0);
  }

  
  /* Runs in O(n*m*log(n*m)) \subset O(N^2log(N)), where n is the size
   * of S _after_ the epsilon closure is complete, m is the average
   * number of epsilon-transitions from these states, and N is the
   * total number of states in the NFA.
   */
  void epsilonClosure(StateSet& S) {
    queue<int> q;
    for (StateSet::iterator i = S.begin(); i != S.end(); ++i)
      q.push(*i);
    while (!q.empty()) {
      vi epsStates = states[q.front()][0];
      q.pop();
      for (vi::iterator i = epsStates.begin(); i != epsStates.end(); ++i)
	if (S.insert(*i).second)
	  q.push(*i);
    }
  }


  /* Runs in O(n*m*log(n*m)) \subset O(N^2log(N)), where n is the size
   * of S, m is the average number of c-transitions in the states in
   * S, and N is the total number of states in the NFA.
   */
  StateSet nextStates(StateSet& S, char c) {
    StateSet res;
    for (StateSet::iterator i = S.begin(); i != S.end(); ++i) {
      vi nStates = states[*i][(unsigned char)c];
      for (vi::iterator j = nStates.begin(); j != nStates.end(); ++j)
	res.insert(*j);
    }
    return res;
  }
};
