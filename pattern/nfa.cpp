/* KTH ACM Contest Template Library
 *
 * Pattern Matching/Automata/NFA
 *
 * Credit:
 *   By Per Austrin
 */

#include <queue> /* Used in the epsilon closure */
#include <vector>
#include <set>

typedef vector<int> vi;
typedef set<int> StateSet;

struct NFA {
  typedef vector<vi> NFAState;
  vector<NFAState> states;
  vector<bool> accepting;
  
  NFA() { }

  size_t match(char* s) {
    size_t *lastAccept = string::npos;
    char *i = s;
    StateSet states;
    states.insert(0);
    while (!states.empty()) {
      epsClosure(S);
      for (StateSet::iterator si = states.begin(); si != states.end(); ++si)
	if (accepting[*si])
	  lastAccept = i - s;
      if (!*i)
	break;
      states = nextStates(states, *i++);
    }
    return lastAccept;
  }

  int newState() {
    states.push_back(NFAState(256, vi()));
    accepting.push_back(false);
    return states.size() - 1;
  }

  void newTransition(int from, int to, char c) { 
    states[from][c].push_back(to);
  }
  
  void epsClosure(StateSet& S) {
    queue<int> q;
    for (StateSet::iterator i = S.begin(); i != S.end(); ++i)
      q.push(*i);
    while (!q.empty()) {
      vi &epsStates = states[q.front()][0];
      q.pop();
      for (vi::iterator i = epsStates.begin(); i != epsStates.end(); ++i)
	if (S.insert(*i).second)
	  q.push(*i);
    }
  }

  StateSet nextStates(StateSet& S, char c) {
    StateSet res;
    for (StateSet::iterator i = S.begin(); i != S.end(); ++i) {
      vi &nStates = states[*i][(unsigned char)c];
      for (vi::iterator j = nStates.begin(); j != nStates.end(); ++j)
	res.insert(*j);
    }
    return res;
  }
};
