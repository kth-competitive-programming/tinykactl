/*
 * Filter a LaTeX file into an lgrind file.  Convert
 * \begin{verbatim}-\end{verbatim} pairs into %[ - %] pairs.  Tabify
 * the former verbatim environments. Convert \verb|stuff| into @stuff@.
 */

#ifndef lint
static char sccsid[] = "@(#)v2lg.c       1.1 20/3/85";
static char rcsid[] =
   "$Id: v2lg.c,v 1.2 1999/05/25 17:01:36 mike Exp $";
#endif


#include <stdio.h>
#include <string.h>

#define FALSE	0
#define TRUE	1

#define STREQ(s,t)  ((*(s) == *(t)) && (!*(s) || !strcmp((s),(t))))


int main(int argc, char **argv)
{
   int in_verbatim = FALSE, col, start_col;
   char in[256], out[256], *ic, *oc, *verb, delim;

   while (fgets(in, sizeof(in), stdin) != NULL) {
      if (in_verbatim) {
	 if (STREQ(in, "\\end{verbatim}\n")) {
	    fputs("%]\n", stdout);
	    in_verbatim = FALSE;
	    continue;
	 }
	 for (col = 0, ic = in, oc = out; *ic != '\n'; ) {
	    if (*ic != ' ' && *ic != '\t') {
	       *oc++ = *ic++; col++;
	    } else {	/* \t == ' ' in a verbatim environment */
	       start_col = col;
	       while (*ic == ' ' || *ic == '\t') {
		  if (((++col) & 7) == 0) {
		     *oc++ = '\t'; start_col = col;
		  }
		  ic++;
	       }
	       if ((col & 7) != 0)
		  for ( ; start_col < col; start_col++)
		     *oc++ = ' ';
	    }
	 }
	 *oc++ = '\n'; *oc++ = '\0';
	 fputs(out, stdout);
	 continue;
      }
      if (STREQ(in, "\\begin{verbatim}\n")) {
	 fputs("%[\n", stdout);
	 in_verbatim = TRUE;
	 continue;
      }
      for (ic = in; (verb = strstr(ic, "\\verb")) != NULL; ) {
	 for ( ; ic < verb; ic++)
	    putchar(*ic);
	 ic += 5;		/* Skip over \verb */
	 if (*ic == '*')	/* \verb* => funny-looking spaces */
	    ic++;
	 delim = *ic++;		/* the delimiter char */
	 putchar('@');
	 while (*ic != delim) {
	    putchar(*ic); ic++;
	 }
	 ic++;			/* Skip the other delimiter */
	 putchar('@');
      }
      fputs(ic, stdout);
   }
   return 0;
}

