#ifndef lint
static char sccsid[] = "@(#)lgrindef.c   4.3 (Berkeley) 11/12/84";
static char rcsid[] =
   "$Id: lgrindef.c,v 1.3 1999/05/28 11:00:16 mike Exp $";
#endif

/* Copyright %%\copyright%% 1979 Regents of the University of California 
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#define MAXHOP	32	/* max number of %|tc=|% indirections */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lgrindef.h"

/*
 * grindcap --- routines for dealing with the language definitions data base
 *	(code stolen almost totally from termcap)
 *
 * BUG:		Should use a "last" pointer in @tbuf@, so that searching
 *		for capabilities alphabetically would not be a %$n^2/2$%
 *		process when large numbers of capabilities are given.
 * Note:	If we add a last pointer now we will screw up the
 *		%|tc|% capability. We really should compile termcap.
 *
 * Essentially all the work here is scanning and decoding escapes
 * in string capabilities.  We don't use stdio because the editor
 * doesn't, and because living w/o it is not hard.
 */

static	char *tbuf;
static	char *filename;
static	int hopcount = 0; /* detect infinite loops in termcap */

static char	*tskip(char *);
static char	*tdecode(char *, char **);

/*
 * @tnchktc@: check the last entry, see if it's %|tc=xxx|%. If so,
 * recursively find %|xxx|% and append that entry (minus the names)
 * to take the place of the %|tc=xxx|% entry. This allows termcap
 * entries to say "like an HP2621 but doesn't turn on the labels".
 * Note that this works because of the left to right scan.
 */
static int tnchktc(void)
{
   register char *p, *q;
   char tcname[16];	/* name of similar terminal */
   char tcbuf[BUFFERSIZE];
   char *holdtbuf = tbuf;
   int l;
   
   p = tbuf + strlen(tbuf) - 2;	/* before the last colon */
   while (*--p != ':')
      if (p < tbuf) {
     /* Not very informative. Wrong BTW (for the configs). Shut up. */ 
     /* write(2, "Bad lgrind entry\n", 18); */
	 return 0;
      }
   p++;
   /* @p@ now points to beginning of last field */
   if (p[0] != 't' || p[1] != 'c')
      return 1;
   strcpy(tcname,p+3);
   q = tcname;
   while (q && *q != ':')
      q++;
   *q = '\0';
   if (++hopcount > MAXHOP) {
      fprintf(stderr, "Infinite tc= loop\n");
      return 0;
   }
   if (tgetent(tcbuf, tcname, filename) != 1)
      return 0;
   for (q = tcbuf; *q != ':'; q++)
      ;
   l = (int)(p - holdtbuf + strlen(q));
   if (l > BUFFERSIZE) {
      fprintf(stderr, "LGrind entry too long\n");
      q[(int)(BUFFERSIZE - (p-tbuf))] = '\0';
   }
   strcpy(p, q+1);
   tbuf = holdtbuf;
   return 1;
}


/*
 * @tnamatch@ deals with name matching.  The first field of the termcap
 * entry is a sequence of names separated by %|||%'s, so we compare
 * against each such name.  The normal %|:|% terminator after the last
 * name (before the first field) stops us.
 */
static int tnamatch(char *np)
{
   register char *Np, *Bp;
   
   Bp = tbuf;
   if (*Bp == '#')
      return 0;
   for (;;) {
      for (Np = np; *Np && toupper(*Bp) == toupper(*Np); Bp++, Np++)
		 continue;
      if (*Np == '\0' && (*Bp == '|' || *Bp == ':' || *Bp == '\0'))
		 return 1;
      while (*Bp != '\0' && *Bp != ':' && *Bp != '|')
		 Bp++;
      if (*Bp == '\0' || *Bp == ':')
		 return 0;
      Bp++;
   }
}


/*
 * Skip to the next field.  Notice that this is very dumb, not
 * knowing about %|\:|% escapes or any such.  If necessary, %|:|%'s can
 * be put into the termcap file in octal.
 */
static char *tskip(register char *bp)
{
   while (*bp && *bp != ':')
      bp++;
   if (*bp == ':')
      bp++;
   return bp;
}


/*
 * Return the (numeric) option id.
 * Numeric options look like
 *	%|li#80|%
 * i.e. the option string is separated from the numeric value by
 * a %|#|% character.  If the option is not found we return %$-1$%.
 * Note that we handle octal numbers beginning with %$0$%.
 */
int tgetnum(char *id)
{
   register int i, base;
   register char *bp = tbuf;
   
   for (;;) {
      bp = tskip(bp);
      if (*bp == '\0')
	 return -1;
      if (*bp++ != id[0] || *bp == '\0' || *bp++ != id[1])
	 continue;
      if (*bp == '@')
	 return -1;
      if (*bp != '#')
	 continue;
      bp++;
      base = 10;
      if (*bp == '0')
	 base = 8;
      i = 0;
      while (isdigit(*bp))
	 i *= base, i += *bp++ - '0';
      return i;
   }
}



/*
 * Handle a flag option.
 * Flag options are given "naked", i.e. followed by a %|:|% or the end
 * of the buffer.  Return 1 if we find the option, or 0 if it is
 * not given.
 */
int tgetflag(char *id)
{
   register char *bp = tbuf;
   
   for (;;) {
      bp = tskip(bp);
      if (!*bp)
	 return 0;
      if (*bp++ == id[0] && *bp != 0 && *bp++ == id[1]) {
	 if (!*bp || *bp == ':')
	    return 1;
	 else if (*bp == '@')
	    return 0;
      }
   }
}


/*
 * Get a string valued option.
 * These are given as
 *	%|cl=^Z|%
 * Much decoding is done on the strings, and the strings are
 * placed in area, which is a ref parameter which is updated.
 * No checking on area overflow.
 */
char *tgetstr(char *id, char **area)
{
	register char *bp = tbuf, *i;
	register int eq;

	for (;;) {
		bp = tskip(bp);
		if (!*bp)
			return 0;
		eq=1;
		for (i=id; *i;)
			if (*i++!=*bp++) { eq=0; break; }
		if (!eq)
			continue;
		if (*bp == '@')
			return 0;
		if (*bp != '=')
			continue;
		bp++;
		return tdecode(bp, area);
	}
}


/*
 * @tdecode@ does the grunge work to decode the
 * string capability escapes.
 */
static char *tdecode(register char *str, char **area)
{
   char *cp = *area, c;
   
   while ((c = *str++) != 0) {
      if (c == ':') {
         if (*(cp-1) == '\\')
            cp--;
         else           
            break;
      }
      *cp++ = c;
   }
   *cp++ = '\0';
   str = *area;
   *area = cp;
   return str;
}

/*
 * Get an entry for terminal name in buffer @bp@,
 * from the termcap file.  Parse is very rudimentary;
 * we just notice escaped newlines.
 */
int tgetent(char *bp, char *name, char *file)
{
   register char *cp;
   register char c;        /* 30.7.96 -- tryal [sic] */
   register int i = 0, cnt = 0;
   char ibuf[BUFFERSIZE];
   FILE *tf;
   
   tbuf = bp;
   tf = 0;
   filename = file;
   tf = fopen(filename, "rt");
   if (tf == NULL)
      return -1;
   for (;;) {
      cp = bp;
      for (;;) {
	 if (i == cnt) {
	    cnt = fread(ibuf, 1, BUFFERSIZE, tf);
	    if (cnt <= 0) {
	       fclose(tf);
	       return 0;
		}
		i = 0;
	 }
	 c = ibuf[i++];
	 if (c == '\n') {
		if (cp > bp && cp[-1] == '\\'){
		   cp--;
		   continue;
		}
		break;
	 }
	 if (cp >= bp+BUFFERSIZE) {
		fprintf(stderr, "LGrind entry too long\n");
		break;
	 } else
		*cp++ = c;
	  }
	  *cp = '\0';

	  /*
	   * The real work for the match.
	   */
	  if (tnamatch(name)) {
	 fclose(tf);
	 return tnchktc();
	  }
   }
}
