/* KTH ACM Contest Template Library
 *
 * Utility/Code Library Document/Line code, safe version
 *
 * Credit:
 *   Resolution for sstream problem by David Rydh
 *   By Mattias de Zalenski
 */

/* Enter linecode (with a commented-out //#include <sstream>),
 * checksum it. Then either remove the //, or enter the fix below:
 */
#if __GNUC__ >= 3
#include <sstream>
#else
// START FIX
#include <strstream>
#include <string>
struct istringstream : istrstream {
  istringstream( const string &s ) : istrstream( s.c_str(), s.length() ) {}
};
// END FIX
#endif

#include "linecode.cpp"
