/* KTH ACM Contest Template Library
 *
 * Utility/Code Library Document/Line code, safe version
 *
 * Credit:
 *   Resolution for sstream problem by David Rydh
 *   By Mattias de Zalenski
 */

#include <strstream>
#include <string>
struct istringstream : istrstream {
  istringstream( const string &s ) : istrstream( s.c_str(), s.length() ) {}
};
