/* KTH ACM Contest Template Library
 *
 * Utility/Code Library Document/Code stripper
 *
 * Credit:
 *   Requested by David Rydh, Fredrik Niemelä, Mattias de Zalenski
 *   By Mattias de Zalenski
 */
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

struct strip_parser {
  istream &in;
  ostream &out;
  bool strip_header, strip_comments, strip_preproc, strip_code;
  strip_parser(istream &_in, ostream &_out) : in(_in), out(_out) {
    strip_header = strip_comments = strip_preproc = strip_code = false;
  }
  // the strip function
  bool strip() {
    try {
      p = false; // skip initial empty lines
      h = true;
      lex();
      do rdX();
      while (in);
    } catch (bool f) { return f; }
    return true;
  }
  // recursive descent parser
  bool p; // print flag
  bool h; // header flag
  char c; // lex token
  void lex() { if (p) put(c); if (!in.get(c)) throw false; }
  void put(char d) { if (!(out << d)) throw false; }
  void rdEsc(char t) { // backslash-escaped sequence,
    bool esc = false; //  terminated by unescaped t
    while (esc || c != t) {
      esc = !esc && c == '\\'; // double \\'s cancel
      lex();
    }
    lex();
  }
  void rdX() { if (c == '#') rdP(); else rdC(); } // a c++ "line"
  void rdP() { p = !strip_preproc; rdEsc('\n'); } // a preproc "line"
  void rdC() { // a code "line"
    bool e = true; // empty code line flag, see //line comment
    bool s = true; // space flag, see /*range*/ comment
    while (c != '\n') {
      p = !strip_code; // newlines are skipped after somthing is skipped
      switch (c) {
      case '\'': lex(); rdQ(); e &= s = false; break; // quote
      case '"': lex(); rdS(); e &= s = false; break; // string
      case '/': // check for comments
	p = false;
	lex();
	if (c == '/') { //line comment
	  p = !strip_comments;
	  if (p) put('/');
	  rdL();
	  p |= !(strip_code || e); // newline if the comment was not alone
	  return; // a line was read, so return!
	}
	else if (c == '*') { // /*range*/ comment, or header
	  p = h ? !strip_header : !strip_comments;
	  if (p) put('/');
	  rdR();
	  // important!! if there are no spaces around a /*comment*/,
	  // one has to be inserted!!
	  if (!p && !s && !isspace(c) && !strip_code) put(' ');
	  p |= !(strip_code || e); // newline if the comment was not alone
	}
	else { // just a slash
	  p = !strip_code;
	  e &= s = false;
	  if (p) put('/');
	}
	break;
      default:
	e &= s = isspace(c);
	if (!s) h = false;
	lex();
	break;
      }
      e = false; // leading spaces problem!
    }
    lex();
  }
  void rdQ() { rdEsc('\''); } // quote
  void rdS() { rdEsc('"'); } // string
  void rdL() { while (c != '\n') lex(); } //line comment
  void rdR() { // /*range*/ comment
    h = false;
    for (;;) {
      lex();
      if (c == '*') {
	lex();
	if (c == '/') {
	  lex();
	  rdW(); // rdW to beatify "x /*comment*/ y;",
	  return;
	}
      }
    }
  }
  // whitespace
  void rdW() { while (isspace(c) && c != '\n') lex(); }
};

int main(int argc, char *argv[]) {
  strip_parser stripper(cin, cout);
  bool f = true;
  for (int i = 1; i < argc; i++) {
    string s = argv[i];
    if (s == "-") ; // do nothing
    else if (s == "header") stripper.strip_header = true;
    else if (s == "comments") stripper.strip_comments = true;
    else if (s == "preproc") stripper.strip_preproc = true;
    else if (s == "code") stripper.strip_code = true;
    else {
      cerr << "stripcode: unrecognized option '" << s << "'" << endl;
      f = false;
    }
  }
  if (argc <= 1 || !f) {
    cerr << "usage: stripcode {-|header|comments|preproc|code}+" << endl;
    cerr << "  header is the first /*comment*/ not preceded by code" << endl;
    return 1;
  }
  stripper.strip();
  return 0;
}
