/* KTH ACM Contest Template Library
 *
 * Pattern Matching/Regular Expressions/RegExp -> NFA
 *
 * Credit:
 *   By Per Austrin, 2002-10-2?
 */


#include "nfa.cpp"

int parseRegExp(NFA& nfa, char* s, int entry);

NFA parseRegexp(const char* s) {
  NFA res;
  res.newState();
  res.accepting[parseRegExp(res, s, 0)] = true;
  return res;
}


int parseRegExp(NFA& nfa, const char* s, int entry) {
  int res = entry;
  char literal = 0;
  while (*i && *i != ')') {
    int oldRes = res;
    switch (*i | (*i == '"' ? 0 : literal)) {
    case '"':
      literal = ~literal;
      break;
    case '(':
      res = parseRegExp(++i, res);
      break;
    case '|': {
      int altEnd = parseRegExp(++i, entry);
      res = nfa.newState();
      nfa.newTransition(oldRes, res, 0);
      nfa.newTransition(altEnd, res, 0);
      --i;
      break;
    }
    case '*':
      nfa.newTransition(res, entry, 0);
      res = entry;
      break;
    case '[':
      res = nfa.newState();
      while (*++i != ']' && *i)
	nfa.newTransition(oldRes, res, *i);
      break;
    default:
      res = nfa.newState();
      nfa.newTransition(oldRes, res, (unsigned char)*i);
    }
    if (*i)  ++i;
  }
  return res;
}
