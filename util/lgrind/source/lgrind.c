#ifndef lint
static char sccsid[] = "@(#)lgrind.c     3.66 (MPi) 5/10/99";
static char rcsid[] =
   "$Id: lgrind.c,v 1.14 2000/12/27 21:42:42 mike Exp $";
#endif

/*
 * Copyright %%\copyright%% 1980 The Regents of the University of California.
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


/* lgrind --- general purpose "pretty printer" for use with %%\LaTeX%%.
 * A %%\LaTeX%% version of tgrind, which is a %%\TeX%% version
 * of vgrind.  Used to "grind nice program listings."
 *
 * Copyright %%\copyright%% 1985 by Van Jacobson, Lawrence Berkeley Laboratory
 * This program may be freely used and copied but %%{\bf may not be sold}%%
 * without the author's %%{\bf written permission}%%. This notice must remain
 * in any copy or derivative.
 *
 * This program is an adaptation of "vfontedpr" v4.2 (12/11/84) from
 * the 4.2bsd Unix distribution.  Vfontedpr was written by Dave
 * Presotto (based on an earlier program of the same name written by
 * Bill Joy).
 *
 * I would welcome comments, enhancements, bug fixes, etc.  Please
 * mail them to:
 *	van@@lbl-rtsg.arpa	(from arpanet, milnet, csnet, etc.)
 *	..!ucbvax!lbl-csam!van	(from Usenet/UUCP)
 */

/*%%\par{\bf Thank you very much, Van. Due to the ``may not be sold'' clause%%*/
/*%%this program has become non-free. And since the author of this licence%%*/
/*%%cannot be contacted (address too old, apparently newer ones exist, but%%*/
/*%%no answers from them), this cannot be changed.}\par%%*/

/* Copyright %%\copyright%% 1995-99 by Michael Piefel
 *
 * Modifications.
 * --------------
 * 10 Feb 85	Van		Written.
 * 29 Mar 85	Chris Torek	(chris@@maryland):  Bug fixes for %|~|% and
 *				%|^L|% output.	Most cpu-time eaters recoded
 *				to improve efficiency.
 * 30 Mar 85	Chris & Van Fixed %|\C|% & %|\S|% (comment & string start
 *				indicators to really appear at the start of
 *				comments & strings.  Changes for speeded-up
 *				@expmatch()@.
 *  8 Oct 87	JSL		Modified so as to compile on VMS. %|-i|% option
 *    Jan 88	JSL		%|-e|% option for embedded code.
 *    Sep 91	George V Reilly Reformated and cleaned up code, including
 *				naughtiness with @NULL@.  Added %|@|%,
 *				%|%%|%, %|%$|%, and %%\tt \%|%% features.
 *				Also the %|%<|%, %|%!|%, and %|%#|% features.
 *    Oct 94	Matthias Eckermann (%|ud311aa@@sunmail.lrz-muenchen.de|%)
 *				fixed a little bug, added: Internal_Help,
 *    Sep 95	Michael Piefel	Modified for %%\LaTeXe%%
 *    Feb 96	Michael Piefel	Restructured into ANSI C
 *    May 99	Michael Piefel	Made it Y2K compliant
 *    Oct 99	Michael Piefel	Space runs make tabstops
 *    Dec 99	Michael Piefel  Version option, space allowed after '-l'
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
/* One of the following two (depending on your system) */
#include <unistd.h>
/* #include <io.h> */
#include "lgrindef.h"
#include "regexp.h"

#ifndef vms
#  include <sys/types.h>
#  include <sys/stat.h>
#else
#  include <types.h>
#  include <stat.h>
#endif

#define STANDARD 0
#define ALTERNATE 1

#define NOTCODE 0		/* the three states of @incode@ */
#define INITCODE 1
#define OTHERCODE 2

#define PNAMELEN 80		/* length of a function/procedure name */
#define PSMAX 20		/* size of procedure name stacking */

#ifndef vms
#  define OKEXIT	0
#  define BADEXIT	1
#  ifndef DEFSFILE
#    define DEFSFILE	"/usr/lib/texmf/tex/latex/lgrind/lgrindef"
#  endif
#else
#  define OKEXIT	1
#  define BADEXIT	0
#  define DEFSFILE	"TEX$INPUTS:lgrindef.src"
#endif

#ifndef unix
#  define HELPOPTION	"-?"
#else
#  define HELPOPTION	"--help"
#endif

typedef struct varsubst {
	char *var;
	char *subst;
	struct varsubst *next;
} varsubst;

varsubst *varsubstlist;

/* forward declarations */

int	getredirection(int argc, char **argv);
void	setlang();
void	Internal_Help();
void	Internal_Help_Language_List();
void	readfile(FILE *);
void	putScp(char *);
boolean	putKcp(char *, char *, boolean);
void	putVcp(char *, char *);
void	putstr(char *);
boolean	(*isproc)(char *);
boolean	isprocNorm(char *);
boolean	isprocC(char *);
void	outchar(int);
void	parsechartab(void);
varsubst *parsevartab(char *);
void	parsepreamble(char *);
void	setpreambles(void);
void	printpreamble(char *);
void	writeDefsfileInExe(char *, char *);
int	substvarname(char **, int);

/*
 *	The state variables
 */

boolean incomm;			/* in a comment of the primary type */
boolean instr;			/* in a string constant */
boolean inchr;			/* in a character constant */
int	incode;			/* in program text within a comment */
int	latexcode;		/* in program text within %%\LaTeX%% */
int	latex_tt;		/* in %|\texttt|% text within %%\LaTeX%% */
boolean use_tt;			/* use %|\texttt|% everywhere */
boolean do_at;			/* pay attention to %|@|%s in %%\LaTeX%% */
boolean do_tt;			/* pay attention to %|||%s in %%\LaTeX%% */
boolean nokeyw = FALSE;		/* no keywords being flagged */
boolean prccont;		/* continue last procedure */
boolean code_cmnts = TRUE;	/* Treat %|@|%, etc specially in comments */
boolean code_latex = TRUE;	/* Treat %|@|%, etc specially in %%\LaTeX%% */
int	lastout;		/* (extended) last character to outchar */
int	comtype;		/* type of comment */
int	psptr;			/* the stack index of the current procedure */
char	pstack[PSMAX][PNAMELEN+1]; /* the procedure name stack */
int	plstack[PSMAX];		/* the procedure nesting level stack */
int	blklevel;		/* current nesting level */
int	reclevel;		/* current @record@ nesting level */
int	procedures_pending;	/* proc starts w/o block starts */
char	fname[200]="";		/* File being read */
int	lineno;			/* Line number in that file */
int	linenocode;		/* Line number of the source code worked on */
char	pname[BUFFERSIZE+1];	/* Current procedure name */

/*
 *	The language specific globals
 */
char	defsbuf[200]="DeFsBuF"DEFSFILE;
char	*defsfile=&defsbuf[7];	    /* name of language definitions file */
char	language[PNAMELEN]="mPi";   /* the language indicator */
char	the_buf[BUFFERSIZE+1];	    /* general purpose buffer */
char	*buf = the_buf + 1;	    /* @buf-1@ must be valid */
char	*strings;		    /* store the keywords */
char	*defs;			    /* language definitions from lgrindef */
char	preamble[BUFFERSIZE/4];	    /* first preamble */
char	postamble[BUFFERSIZE/4];    /* first preamble */
char	preamble2[BUFFERSIZE/4];    /* file preamble */
char	config[BUFFERSIZE/4];	    /* redefinitions within lgrind-environment */
char	chartab[BUFFERSIZE/4];	    /* buffer for chartab modifications */
char	*l_keywds[BUFFERSIZE/2];    /* keyword table address */
char	*l_prcbeg;		    /* regular expr for procedure begin */
char	*l_noproc;		    /* regexp for lines with NO procedure begin */
char	*l_combeg;		    /* regexp introducing a comment */
char	*l_comend;		    /* regexp ending a comment */
char	*l_acmbeg;		    /* regexp introducing a comment */
char	*l_acmend;		    /* regexp ending a comment */
char	*l_blkbeg;		    /* regexp beginning of a block */
char	*l_blkend;		    /* regexp ending a block */
char	*l_strbeg;		    /* regexp starting string constant */
char	*l_strend;		    /* regexp ending string constant */
char	*l_chrbeg;		    /* regexp starting character constant */
char	*l_chrend;		    /* regexp ending character constant */
char	*l_cdebeg;		    /* regexp starting prog text within comment */
char	 s_cdebeg[BUFFERSIZE/8];    /* actual string corresponding to @l_cdebeg@ */
char	*l_cdeend;		    /* regexp ending prog text within comment */
char	*l_texbeg;		    /* regexp starting %%\TeX%% text in comment */
char	*l_texend;		    /* regexp ending %%\TeX%% text in comment */
char	*l_txmbeg;		    /* regexp starting %%\TeX%% math in comment */
char	*l_txmend;		    /* regexp ending %%\TeX%% math in comment */
char	*l_tt_beg;		    /* regexp starting verbatim text in comment */
char	*l_tt_end;		    /* regexp ending typewriter text in comment */
char	*l_at;			    /* regexp for %|@|% in %%\LaTeX%% text */
char	*l_tt;			    /* regexp for %|||% in %%\LaTeX%% text */
char	*l_pc;			    /* regexp for %|%|% in %%\LaTeX%% text */
char	*l_id;			    /* string containing valid identifier chars */
char	*l_record;		    /* start of lexical block outside functions */
char	l_escape;		    /* character used to escape characters */
boolean l_toplex;		    /* procedures only defined at top lex level */
boolean l_onecase;		    /* upper & lower case equivalent */
boolean	l_cfunctions;		    /* special for C function search */
boolean embed = FALSE;		    /* -e seen --- do embedded code */
boolean code = TRUE;		    /* Looking at code */
int	TabWidth = 8;		    /* Default width of a tab */

/*
 *  global variables also used by expmatch
 */

extern  boolean _escaped;	    /* if last character was an escape */
extern	char *_sstart;		    /* start of the current string */

extern	int (*re_strncmp)(const char*, const char*, size_t);
				    /* function to do string compares */

int main(int argc, char **argv)
{
   struct stat  stbuf;
   boolean	hseen = FALSE;	    /* -h seen		*/
   char		*hstring="";	    /* header string to use */
   char		*programname;	    /* the zeroeth argument */
   boolean	iseen = FALSE;	    /* -i seen		*/
   int		files_done = 0;

   defs=(char*)malloc(2*BUFFERSIZE);
   strings=(char*)malloc(2*BUFFERSIZE);
   argc = getredirection(argc, argv);

   /* abuse of programname */
   programname=getenv("LGRINDEF");
   if (programname) strcpy(defsfile, programname);

   programname=argv[0];
   argc--, argv++;

   if (argc==0) {
       Internal_Help();
	   return OKEXIT;
   }

   do {
      struct tm modtime = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

      if (argc > 0) {
	 /* Help-facility */
	 if (!strcmp(argv[0], HELPOPTION)) {
	    Internal_Help();
	    return OKEXIT;
	 }

	 if (!strcmp(argv[0], "-s")) {
	    Internal_Help_Language_List();
	    return OKEXIT;
	 }

	 if (!strcmp(argv[0], "--version")) {
	    printf("LGrind %s\n", VERSION);
	    return OKEXIT;
	 }


	 /* Header */
	 if (!strcmp(argv[0], "-h")) {
		hseen = TRUE;
		if (argc == 1) {
		   argc--;
		   goto rest;
		}
		hstring = argv[1];
		argc--, argv++;
		argc--, argv++;
		if (argc > 0)
		   continue;
		goto rest;
	 }

	 /* take input from the standard place */
	 if (!strcmp(argv[0], "-")) {
		argc = 0;
		goto rest;
	 }

	 /* put output to non-standard place */
	 if (!strcmp(argv[0], "-o")) {
	    if (freopen(argv[1], "w", stdout) == NULL) {
		   perror(argv[1]);
		   return BADEXIT;
	    }
		argc--, argv++;
		argc--, argv++;
		continue;
	 }

	 /* Process embedded text */
	 if (!strcmp(argv[0], "-e")) {
		embed = TRUE;
		argc--, argv++;
		continue;
	 }

	 /* format for inclusion */
	 if (!strcmp(argv[0], "-i")) {
		iseen = TRUE;
		argc--, argv++;
		continue;
	 }

	 /* indicate no keywords */
	 if (!strcmp(argv[0], "-n")) {
		nokeyw++;
		argc--, argv++;
		continue;
	 }

	 /* Don't treat %|@|%, etc. specially in comments */
	 if (!strcmp(argv[0], "-c")) {
		code_cmnts = FALSE;
		argc--, argv++;
		continue;
	 }

	 /* Do treat %|@|%, etc. specially in comments */
	 if (!strcmp(argv[0], "+c")) {
		code_cmnts = TRUE;
		argc--, argv++;
		continue;
	 }

	 /* Don't treat %|@|%, etc. specially in
	  * %%\LaTeX%% text (@embed@ only) */
	 if (!strcmp(argv[0], "-a")) {
		code_latex = FALSE;
		argc--, argv++;
		continue;
	 }

	 /* Do treat %|@|%, etc. specially in
	  * %%\LaTeX%% text (@embed@ only) */
	 if (!strcmp(argv[0], "+a")) {
		code_latex = TRUE;
		argc--, argv++;
		continue;
	 }

	 /* Use %|\texttt|% for all fonts */
	 if (!strcmp(argv[0], "-t")) {
		sscanf(argv[1], "%d", &TabWidth);
		argc--, argv++;
		argc--, argv++;
		continue;
	 }

	 /* specify the language */
	 if (!strncmp(argv[0], "-l", 2)) {
	     if (strlen(argv[0])==2) {
		 strcpy(language, argv[1]);
		 argc--, argv++;
		 argc--, argv++;
	     } else {
		 strcpy(language, argv[0]+2);
		 argc--, argv++;
		 continue;
	     }
	 }

	 /* specify the language description file for permanent use */
	 if (!strcmp(argv[0], "-d!")) {
		 writeDefsfileInExe(programname, argv[1]);
		 return OKEXIT;
	 }

	 /* specify the language description file */
	 if (!strncmp(argv[0], "-d", 2)) { /* TODO strncmp? */
		strcpy(defsfile, argv[1]);
		argc--, argv++;
		argc--, argv++;
		continue;
	 }

	 /* specify the file containing variable substitutions */
	 if (!strcmp(argv[0], "-v")) {
		varsubstlist=parsevartab(argv[1]);
		argc--, argv++;
		argc--, argv++;
		continue;
	 }

	 /* open the file for input */
	 if (freopen(argv[0], "r", stdin) == NULL) {
		perror(argv[0]);
		return BADEXIT;
	 }

	 strcpy(fname, argv[0]);
	 argc--, argv++;
	  }
   rest:

	  lineno = 0;
	  setpreambles();

	  /* get config data from %|lgrindef|% */
	  if (tgetent(buf, "firstpreamble", defsfile)>0)
		 parsepreamble(preamble);

	  if (tgetent(buf, "postamble", defsfile)>0)
		 parsepreamble(postamble);

	  if (tgetent(buf, "filepreamble", defsfile)>0)
		 parsepreamble(preamble2);

	  if (tgetent(buf, "configuration", defsfile)>0)
		 parsepreamble(config);

	  if (tgetent(buf, "chartab", defsfile)>0)
		 parsechartab();

	  if (iseen && embed) {
		 fprintf(stderr, "-i makes no sense with -e; -e ignored\n");
		 embed = FALSE;
	  }

	  if (!iseen && !embed) {
		 if (files_done == 0) printpreamble(preamble);
		 printpreamble(preamble2);
		 printf("\\begin{lgrind}\n");
		 printpreamble(config);
		 /* In case \BGfont was modified in config */
		 printf("\\BGfont\n");
	  }


	  if (embed)
		 printf("%% This document was generated automagically by lgrind.  DO NOT EDIT.\n\n");
	  if (iseen)
	  {
		  printf("%% Remember to use the lgrind style\n\n");
		  printf("\\Head{");
		  if (hseen) putstr(hstring);
		  printf("}\n");
	  }

	  setlang();

	  /* initialize the program */

	  incomm = instr = inchr = _escaped = FALSE;
	  incode = latexcode = latex_tt = NOTCODE;
	  do_at = do_tt = code_latex;
	  blklevel = 0;
	  reclevel = 0;
	  for (psptr = 0; psptr < PSMAX; psptr++) {
		 pstack[psptr][0] = '\0';
		 plstack[psptr] = 0;
	  }
	  psptr = -1;
	  if (*fname=='\0') {
	      time_t tm;
	      strcpy(fname, "stdin");
	      stbuf.st_size=0;
	      tm=time(NULL);
	      modtime = *localtime(&tm);
	  }
	  else {
	      stat(fname, &stbuf);
	      modtime = *localtime(&stbuf.st_mtime);
	  }

	  if (!embed) {
		 printf("\\File{");
		 putstr(fname);
		 printf("}{%d}{%d}{%d}{%d:%02d}{%ld}\n", modtime.tm_year+1900, modtime.tm_mon+1,
				 modtime.tm_mday, modtime.tm_hour, modtime.tm_min, stbuf.st_size);
      }

      code = FALSE;
      readfile(stdin);
      files_done++;

      if (!iseen && !embed) {
		 printf("\\end{lgrind}\n");
      }

      if (code)
		 fprintf(stderr, "Reached EOF within code in file %s\n", fname);
   } while (argc > 0);

   if (!iseen && !embed) {
      printpreamble(postamble);
   }
   return OKEXIT;
}


/*
 * @readfile()@ --- read and process a file
 */
void readfile(FILE *fp)
{
   register char *cp;
   boolean	LGinline=FALSE;		/* Doing %( -- %)	*/
   char		term;			/* ']' or ')'           */
   char		*atptr;			/* start of %|@|% within %%\LaTeX%% text */
   char		*atendptr;		/* end of %|@|% within %%\LaTeX%% text */
   char		*pcptr;			/* start of %|%|% within %%\LaTeX%% text */
   char		*pcendptr;		/* end of %|%|% within %%\LaTeX%% text */
   char		temp[BUFFERSIZE];
   char		fnamebak[200];
   int		linenobak;

   while (fgets(buf, BUFFERSIZE, fp) != NULL) {
      cp = &buf[strlen(buf)-1];
      if (*cp != '\n') {*(++cp) = '\n'; *(++cp) = '\0'; }
	  lineno++;
      cp = buf;
      lastout = '\0';
      if (embed) {
	  if (!code) {
	      if (buf[0] == '%' &&
		      (buf[1] == '[' || buf[1] == '('
		       || buf[1] == '#' || buf[1] == '<' || buf[1] == '!'
		       || buf[1] == '@' || buf[1] == '|')) {

		  for (cp = buf + 2; *cp == ' ' || *cp == '\t'; cp++)
		      ;

		  /* Change the language */
		  if (buf[1] == '#') {
		      if (*cp == '\n')
			  fprintf(stderr, "no language seen after %%# in file\
			      %s at line %d\n", fname, lineno);
		      else {
			  cp[strlen(cp) - 1] = '\0'; /* nuke the @'\n'@ */
			  while ((*cp==' ') || (*cp=='\t')) cp++;
			  strcpy(language, cp);
			  printf("%% switching to %s\n", language);
			  setlang();
		      }
		      continue;
		  }

		  /* Turn %|@|% or %|||% processing within %%\LaTeX%%
		   * text on or off. */

		  if (buf[1] == '@' || buf[1] == '|') {
		      if (*cp == '\n')
			  fprintf(stderr, "no setting seen after %%%c in file\
			      %s at line %d\n", buf[1], fname, lineno);
		      else {
			  int flag = (*cp == '1' || *cp == '+');
			  if (buf[1] == '@')
			      do_at = flag;
			  else
			      do_tt = flag;
		      }
		      continue;
		  }

		  code = TRUE;

		  /* take input from another file or from a shell command */
		  if (buf[1] == '<' || buf[1] == '!') {
		      FILE *fp;
		      char source = buf[1];

		      cp[strlen(cp) - 1] = '\0';    /* nuke the @'\n'@ */
		      if (source == '<')
			  fp = fopen(cp, "r");
		      else /* @source == '!'@ */
			  fp = popen(cp, "r");

		      if (fp == NULL) {
			  sprintf(temp, "%%%c on `%s' failed", source, cp);
			  perror(temp);
		      } else {
			  strcpy(temp, cp);
			  printf("%% start of `%s'\n", temp);
			  /* printf("\\LGinlinefalse\\LGbegin\\lgrinde\n"); */
			  /* the above was not %%all%% incorrect ... */
			  printf("\\LGinlinefalse");
			  printf("\\begin{lgrind}\n");
			  printpreamble(config);
			  /* In case \BGfont was modified in config */
			  printf("\\BGfont\n");
			  embed = FALSE;
			  linenobak=lineno; strcpy(fnamebak, fname);
			  lineno=0; strcpy(fname, temp);
			  linenocode=0;
			  readfile(fp);
			  lineno=linenobak; strcpy(fname, fnamebak);
			  embed = TRUE;
			  printf("\\end{lgrind}\n");
			  printf("%% end of `%s'\n", temp);
			  if (source == '<')
			      fclose(fp);
			  else
			      pclose(fp);
		      }
		      code = FALSE;
		      continue;
		  }

		  /* embedded inline or displayed code */
		  linenocode=0;
		  if (buf[1] == '(') {
		      LGinline = TRUE;
		      term = ')';
		      printf("\\LGinlinetrue");
		  } else { /* @buf[1] == '['@ */
		      LGinline = FALSE;
		      term = ']';
		      printf("\\LGinlinefalse");
		  }
		  if (buf[2] == '\n') {
		      printf("\\LGbegin\\lgrinde\n");
		  } else {
		      buf[strlen(buf)-1] = '\0';
		      printf("%s\\lgrinde\n", &buf[2]);
		  }
		  continue;

	      } /* @if (buf[0] == '%'@%%\dots%% (special comment) */
	      else
	      {
		  while (do_at && (atendptr = expmatch(cp, l_at, &atptr, (char *) NULL)) != NULL
			  && ( (pcendptr = expmatch(cp, l_pc, &pcptr, (char *) NULL)) == NULL
			      || atptr < pcptr ) )
		  {
		      putVcp(cp, atptr-1);
		      printf("\\LGinlinetrue\\LGbegin\\lgrinde");
		      cp = atendptr;
		      atendptr = expmatch(cp, l_at, &atptr, (char *) NULL);
		      /* No %|@|%: implicit %|@|% just before NL */
		      if (atptr == NULL)
			  atptr = atendptr = cp + strlen(cp) - 1;
		      strncpy(temp, cp, (size_t)(atptr-cp));
		      temp[(int)(atptr-cp)] = '\0';
		      cp = atendptr;
		      linenocode++;
		      putScp(temp);
		      printf("}}\\egroup\\endlgrinde\\LGend{}");
		  }
		  fputs(cp, stdout);
		  continue;
	      }
	  } /* @if (!code)@ */

	  /*
	   * We're in embedded code.
	   */
	  if (buf[0] == '%') {
	      if (buf[1] == '*') {
		  if (term != ']')
		      fprintf(stderr, "%%* only makes sense in display mode\
			  in file %s at line %d\n", fname, lineno);
		  else {
		      printf("\\endlgrinde\\LGend\n");
		      printf("\\LGinlinefalse\\LGbegin\\lgrinde[%d]\n", linenocode+1);
		  }
		  continue;
	      } else if (buf[1] == term) {
		  if (term == ')') printf("\\egroup");
		  if (buf[2] == '\n')
		      printf("\\endlgrinde\\LGend\n");
		  else
		      printf("\\endlgrinde%s", &buf[2]);
		  code = FALSE;
		  continue;
	      } else if (buf[1] == '=') { /* Send literal */
		  fputs(&buf[2], stdout);
		  continue;
	      } else if (buf[1] == '[' || buf[1] == '('
		      || buf[1] == ']' || buf[1] == ')') {
		  fprintf(stderr,
			  "Possible nested embedded code in file %s at line %d\n",
			  fname, lineno);
	      }
	  }

	  /*
	   * Inline code --- suppress leading whitespace
	   */
	  if (LGinline) {
	      while (isspace(*cp))
		  cp++;
	  }
      } /* @if (embed)@ */

      if (*cp == '\f') {
	  printf("\\NewPage\n");
	  cp++;
	  if (*cp == '\n')  /* some people like ^Ls on their own line */
	      continue;
      }
      prccont = FALSE;
      linenocode++;
      putScp(cp);
      if (!embed && prccont && (psptr >= 0)) {
	  printf("\\ProcCont{");
	  putstr(pstack[psptr]);
	  printf("}");
      }
#ifdef DEBUG
      printf("com %o str %o chr %o ptr %d\n", incomm, instr, inchr, psptr);
#endif
   } /* @while fgets()@ */
}



/*
 * Set all of the language-dependent variables
 */
void setlang(void)
{
   char *p, *cp;
   int i;

   /*
	*  get the language definition from the defs file
	*/
   if (strcmp(language, "mPi") == 0)   /* none yet defined */
   {
	   i = tgetent(defs, "extensions", defsfile);
	   if (i == 0) strcpy(language, "c");
	   else
	   {
		   cp = strrchr(fname, '.');
		   if (cp !=NULL)
		   {
			   p=buf; cp = tgetstr(cp+1, &p);
		   }
		   if (cp != NULL) strcpy(language, cp);
		   else strcpy(language, "c");
	   }
   }
   i = tgetent(defs, language, defsfile);
   if (i == 0) {
	  fprintf(stderr, "no entry for language %s\n", language);
	  exit(BADEXIT);
   } else if (i < 0) {
	  fprintf(stderr,  "cannot find lgrindef file `%s'\n", defsfile);
	  exit(BADEXIT);
   }

   p = strings;
   if (tgetstr("kw", &p) == NULL)
      nokeyw = TRUE;
   else  {
      char **cpp;

      cpp = l_keywds;
      cp = strings;
      while (*cp) {
	 while (*cp == ' ' || *cp =='\t')
	    *cp++ = '\0';
	 if (*cp)
	    *cpp++ = cp;
	 while (*cp != ' ' && *cp != '\t' && *cp)
	    cp++;
      }
      *cpp = NULL;
   }

   p = buf;  l_prcbeg = convexp(tgetstr("pb", &p));
   p = buf;  l_noproc = convexp(tgetstr("np", &p));
   p = buf;  l_combeg = convexp(tgetstr("cb", &p));
   p = buf;  l_comend = convexp(tgetstr("ce", &p));
   p = buf;  l_acmbeg = convexp(tgetstr("ab", &p));
   p = buf;  l_acmend = convexp(tgetstr("ae", &p));
   p = buf;  l_strbeg = convexp(tgetstr("sb", &p));
   p = buf;  l_strend = convexp(tgetstr("se", &p));
   p = buf;  l_blkbeg = convexp(tgetstr("bb", &p));
   p = buf;  l_blkend = convexp(tgetstr("be", &p));
   p = buf;  l_chrbeg = convexp(tgetstr("lb", &p));
   p = buf;  l_chrend = convexp(tgetstr("le", &p));
   p = s_cdebeg;  l_cdebeg = convexp(tgetstr("zb", &p));
   p = buf;  l_cdeend = convexp(tgetstr("ze", &p));
   p = buf;  l_texbeg = convexp(tgetstr("tb", &p));
   p = buf;  l_texend = convexp(tgetstr("te", &p));
   p = buf;  l_txmbeg = convexp(tgetstr("mb", &p));
   p = buf;  l_txmend = convexp(tgetstr("me", &p));
   p = buf;  l_tt_beg = convexp(tgetstr("vb", &p));
   p = buf;  l_tt_end = convexp(tgetstr("ve", &p));
   p = buf;  l_record = convexp(tgetstr("rb", &p));
   p = buf;  cp       =         tgetstr("id", &p) ;
   if (cp)
   {
     l_id = (char*)malloc(strlen(cp));
     strcpy(l_id, cp);
   }
   else    l_id = "_";

   l_tt = convexp("\\|");
   l_at = convexp("@");
   l_pc = convexp("%");

   l_escape = '\\';
   l_cfunctions = tgetflag("cf");
   isproc = l_cfunctions ? isprocC : isprocNorm;

   l_onecase = tgetflag("oc");
   re_strncmp = l_onecase ? lc_strncmp : strncmp;
   l_toplex = tgetflag("tl");
}


/*
 * Write out a line of TeX in comment verbatim
 */
void putVtc(char *stringstart, char *comacmptr)
{
   char *texptr, *texendptr;
   char texline[BUFFERSIZE/8];
   texendptr = expmatch(stringstart, l_texend, &texptr, (char *) NULL);
   if (texendptr == comacmptr)
   {
       strncpy(texline, stringstart, texptr-stringstart);
       texline[texptr-stringstart]='\0';
       printf("%s\n", texline);
   }
}


/*
 * Write out a formatted line of program text
 */
void putScp(char *os)
{
   register char *s = os; /* pointer to unmatched string */
   register char *s1;	/* temp. string */
   char *comptr;	/* start of a comment delimiter */
   char *comendptr;	/* end of a comment delimiter */
   char *acmptr;	/* start of an alt. comment delimiter */
   char *acmendptr;	/* end of an alt. comment delimiter */
   char *strptr;	/* start of a string delimiter */
   char *strendptr;	/* end of a string delimiter */
   char *chrptr;	/* start of a char. const delimiter */
   char *chrendptr;	/* end of a char. const delimiter */
   char *cdeptr;	/* start of prog text delim within a comment */
   char *cdeendptr;	/* end of prog text delim within a comment */
   char *cdbptr;	/* start of prog text delim within a comment */
   char *cdbendptr;	/* end of prog text delim within a comment */
   char *texptr;	/* start of %%\TeX%% text delim within a comment */
   char *texendptr;	/* end of %%\TeX%% text delim within a comment */
   char *txmptr;	/* start of %%\TeX%% math delim within a comment */
   char *txmendptr;	/* end of %%\TeX%% math delim within a comment */
   char *tt_ptr;	/* start of typewriter delim within a comment */
   char *tt_endptr;	/* end of typewriter delim within a comment */
   char *blksptr;	/* start of a lexical block start */
   char *blksendptr;	/* end of a lexical block start */
   char *recsptr;	/* start of a lexical block outside functions start */
   char *recsendptr;	/* end of a lexical block outside functions start */
   char *blkeptr;	/* start of a lexical block end */
   char *blkeendptr;	/* end of a lexical block end */

   _sstart = os;	/* remember the start for @expmatch()@ */
   _escaped = FALSE;
   if (nokeyw || incomm || instr)
      goto skip;

   /* check for complete comment TeX line */
   comendptr = expmatch(s, l_combeg, &comptr,  (char *) NULL);
   acmendptr = expmatch(s, l_acmbeg, &acmptr,  (char *) NULL);
   texendptr = expmatch(s, l_texbeg, &texptr,  (char *) NULL);
   if (texptr && comptr == s)
       if (texptr == comendptr)
       {
	   comendptr = expmatch(comendptr, l_comend, &comptr,  (char *) NULL);
	   if (*comendptr=='\n')
	   {
	       putVtc(texendptr, comptr);
	       return;
	   }
       } else if (texptr == acmendptr)
       {
	   acmendptr = expmatch(acmendptr, l_acmend, &acmptr,  (char *) NULL);
	   if (*acmendptr=='\n')
	   {
	       putVtc(texendptr, acmptr);
	       return;
	   }
       }

   if ((*isproc)(s) && reclevel == 0) {
      printf("\\index{"); putstr(pname); printf("}");
      printf("\\Proc{");
      if (strlen(pname)>30)
      {
         s1=pname+strlen(pname)-1;
         while (s1>pname && (isalnum(*s1) || *s1=='_')) s1--;
         if (s1!=pname) strcpy(pname, s1+1);
      }
      if (strlen(pname)>32) { 
         strcpy(pname, pname+strlen(pname)-28);
         printf("\\dots "); }
      putstr(pname);
      printf("}");
      if (!embed && psptr < PSMAX-1) {
		 ++psptr;
		 strncpy(pstack[psptr], pname, PNAMELEN);
		 pstack[psptr][PNAMELEN] = '\0';
		 plstack[psptr] = blklevel-1;
      }
   }

 skip:
   printf("\\L{\\LB{");

   do {
      /* check for string, comment, blockstart, etc */
      if (!incomm && !instr && !inchr) {

	 blkeendptr = expmatch(s, l_blkend, &blkeptr, (char *) NULL);
	 blksendptr = expmatch(s, l_blkbeg, &blksptr, (char *) NULL);
	 recsendptr = expmatch(s, l_record, &recsptr, (char *) NULL);
	 comendptr =  expmatch(s, l_combeg, &comptr,  (char *) NULL);
	 acmendptr =  expmatch(s, l_acmbeg, &acmptr,  (char *) NULL);
	 strendptr =  expmatch(s, l_strbeg, &strptr,  (char *) NULL);
	 chrendptr =  expmatch(s, l_chrbeg, &chrptr,  (char *) NULL);

	 /* check for end of program text in comment */
	 if (incode != NOTCODE) {
	    cdeendptr = expmatch(s, l_cdeend, &cdeptr, (char *) NULL);

	    if ((cdeptr == NULL && (comptr != NULL || acmptr != NULL))
		|| (cdeptr != NULL
		    && ((comptr != NULL && comptr < cdeptr)
			|| ((acmptr != NULL && acmptr < cdeptr))))) {
	       fprintf(stderr, "Comments may not be nested within\
 program text within comments in file %s at\
 line %d\n", fname, lineno);
	       s = (comptr != NULL) ? comptr : acmptr;
	       incode = NOTCODE;
	       continue;
	    }

	    /* look to see if there's a \<zb> in the program text */
	    cdbendptr = expmatch(s, l_cdebeg, &cdbptr, (char *) NULL);
	    if (cdeptr != NULL
		&& (strptr  == NULL || cdbptr < strptr)
		&& (chrptr  == NULL || cdbptr < chrptr)
		&& (blksptr == NULL || cdbptr < blksptr)
		&& (recsptr == NULL || cdbptr < recsptr)
		&& (blkeptr == NULL || cdbptr < blkeptr)) {
	       if (cdbptr > s && cdbptr[-1] == l_escape) {
		  putKcp(s, cdbptr-2, FALSE);
		  printf("\\C{}");
		  putKcp(s_cdebeg, s_cdebeg + strlen(s_cdebeg) - 1, TRUE);
		  printf("\\CE{}");
		  s = cdbendptr;
		  incode = OTHERCODE;
		  continue;
	       }
	    }

	    comendptr =
	       expmatch(s, (comtype == STANDARD) ? l_comend : l_acmend,
			&comptr, (char *) NULL);

	    if ((cdeptr == NULL && comptr != NULL)
		|| (cdeptr != NULL && (comptr != NULL && comptr < cdeptr))) {
	       fprintf(stderr, "Unterminated program text within comment\
 in file %s at line %d\n", fname, lineno);
	       printf("\\C{}");
	       s = comptr;
	       incode = NOTCODE; incomm = TRUE;
	       continue;
	    }


	    if (cdeendptr != NULL) {
	       if ((strptr  == NULL || cdeptr < strptr)
		   && (chrptr  == NULL || cdeptr < chrptr)
		   && (blksptr == NULL || cdeptr < blksptr)
		   && (recsptr == NULL || cdeptr < recsptr)
		   && (blkeptr == NULL || cdeptr < blkeptr)) {
		  if (incode == INITCODE && cdeptr == s) {
		     printf("\\C{}");
		     putKcp(s_cdebeg, s_cdebeg + strlen(s_cdebeg) - 1, TRUE);
		  } else {
		     putKcp(s, cdeptr-1, FALSE);
		     printf("\\C{}");
		  }
		  s = cdeendptr;
		  incode = NOTCODE; incomm = TRUE;
		  continue;
	       }
	    } else if (strptr == NULL && chrptr == NULL
		       && blksptr == NULL && recsptr == NULL 
		       && blkeptr == NULL) {
	       cdeptr = s;
	       s += strlen(s);
	       putKcp(cdeptr, s-1, FALSE);
	       incode = OTHERCODE;
	       continue;
	    } /* else there is a string/char/block on this line */

	    incode = OTHERCODE;
	 } /* @if (incode)@ */


	 /* start of a comment? */
	 if (comptr != NULL
	     && (strptr  == NULL || comptr < strptr)
	     && (acmptr  == NULL || comptr < acmptr)
	     && (chrptr  == NULL || comptr < chrptr)
	     && (blksptr == NULL || comptr < blksptr)
	     && (recsptr == NULL || comptr < recsptr)
	     && (blkeptr == NULL || comptr < blkeptr)) {
	    putKcp(s, comptr-1, FALSE);
	    printf("\\C{}");
	    s = comendptr;
	    putKcp(comptr, comendptr-1, TRUE);
	    incomm = TRUE;
	    comtype = STANDARD;
	    continue;
	 }

	 /* start of an alternate-form comment? */
	 if (acmptr != NULL
	     && (strptr  == NULL || acmptr < strptr)
	     && (chrptr  == NULL || acmptr < chrptr)
	     && (blksptr == NULL || acmptr < blksptr)
	     && (recsptr == NULL || acmptr < recsptr)
	     && (blkeptr == NULL || acmptr < blkeptr)) {
	    putKcp(s, acmptr-1, FALSE);
	    printf("\\C{}");
	    s = acmendptr;
	    putKcp(acmptr, acmendptr-1, TRUE);
	    incomm = TRUE;
	    comtype = ALTERNATE;
	    continue;
	 }

	 /* start of a string? */
	 if (strptr != NULL
	     && (chrptr  == NULL || strptr < chrptr)
	     && (blksptr == NULL || strptr < blksptr)
	     && (recsptr == NULL || strptr < recsptr)
	     && (blkeptr == NULL || strptr < blkeptr)) {
	    putKcp(s, strptr-1, FALSE);
	    printf("\\S{}");
	    s = strendptr;
	    putKcp(strptr, strendptr-1, FALSE);
	    instr = TRUE;
	    continue;
	 }

	 /* start of a character string? */
	 if (chrptr != NULL
	     && (blksptr == NULL || chrptr < blksptr)
	     && (recsptr == NULL || chrptr < recsptr)
	     && (blkeptr == NULL || chrptr < blkeptr)) {
	    putKcp(s, chrptr-1, FALSE);
	    printf("\\S{}");
	    s = chrendptr;
	    putKcp(chrptr, chrendptr-1, FALSE);
	    inchr = TRUE;
	    continue;
	 }

	 /* end of a lexical block */
	 if (blkeptr != NULL) {
	    if ((blksptr == NULL || blkeptr < blksptr) &&
	        (recsptr == NULL || blkeptr < recsptr)) {
	       putKcp(s, blkeendptr - 1, FALSE);
	       s = blkeendptr;
	       if (blklevel) blklevel--;
	       if (reclevel) reclevel--;
	       else if (psptr >= 0 && plstack[psptr] >= blklevel) {

		  /* end of current procedure */
		  blklevel = plstack[psptr];

		  /* see if we should print the last proc name */
		  if (--psptr >= 0)
		     prccont = TRUE;
		  else
		     psptr = -1;
	       }
	       continue;
	    }
	 }

	 /* start of a lexical block */
	 if (blksptr != NULL) {
	    putKcp(s, blksendptr - 1, FALSE);
	    s = blksendptr;
	    if (procedures_pending)
		procedures_pending--;
	    else
		/* when C functions then not on top level */
		if (!l_cfunctions || blklevel)
		    blklevel++;
	    continue;
	 }

	 /* start of a lexical block outside functions */
	 if (recsptr != NULL) {
	    putKcp(s, recsendptr - 1, FALSE);
	    s = recsendptr;
	    if (procedures_pending)
		procedures_pending--;
	    else
		blklevel++;
	    reclevel++;
	    continue;
	 }

	 /* check for end of comment */
      } else if (incomm) {

	 cdeendptr = expmatch(s, l_cdebeg, &cdeptr, (char *) NULL);
	 texendptr = expmatch(s, l_texbeg, &texptr, (char *) NULL);
	 txmendptr = expmatch(s, l_txmbeg, &txmptr, (char *) NULL);
	 tt_endptr = expmatch(s, l_tt_beg, &tt_ptr, (char *) NULL);

	 if (code_cmnts) {

	    /* Check for program text within comment */
	    if (cdeptr != NULL
		&& (texptr == NULL || cdeptr < texptr)
		&& (tt_ptr == NULL || cdeptr < tt_ptr)
		&& (txmptr == NULL || cdeptr < txmptr)) {
	       putKcp(s, cdeptr-1, TRUE);
	       printf("\\CE{}");
	       s = cdeendptr;
	       incode = INITCODE; incomm = FALSE;
	       continue;
	    }

	    /* Check for %%\TeX%% text within comment */
	    if (texptr != NULL
		&& (tt_ptr == NULL || texptr < tt_ptr)
		&& (txmptr == NULL || texptr < txmptr)) {
	       putKcp(s, texptr-1, TRUE);
	       s = texendptr;
	       if ((texendptr =
		    expmatch(s, l_texend, &texptr, (char *) NULL)) != NULL) {
		  putchar('{'); putVcp(s, texptr-1); putchar('}');
		  s = texendptr;
	       } else {
		  fprintf(stderr, "LaTeX text within a comment must all be\
 on one line (file %s at line %d)\n", fname, lineno);
		  s += strlen(s);
	       }
	       continue;
	    }

	    /* Check for typewriter text within comment */
	    if (tt_ptr != NULL
		&& (txmptr == NULL || tt_ptr < txmptr)) {
	       putKcp(s, tt_ptr-1, TRUE);
	       s = tt_endptr;
	       if ((tt_endptr =
		    expmatch(s, l_tt_end, &tt_ptr, (char *) NULL)) != NULL) {
		  printf("{\\TTfont ");
		  latex_tt=TRUE;
		  putKcp(s, tt_ptr-1, TRUE);
		  latex_tt=FALSE;
		  printf("}");
		  s = tt_endptr;
	       } else {
		  fprintf(stderr, "typewriter text within a comment must all\
 be on one line (file %s at line %d)\n\t%s",
			    fname, lineno, s);
		  s += strlen(s);
	       }
	       continue;
	    }

	    /* Check for %%\TeX%% math within comment */
	    if (txmptr != NULL) {
	       putKcp(s, txmptr-1, TRUE);
	       s = txmendptr;
	       if ((txmendptr =
		    expmatch(s, l_txmend, &txmptr, (char *) NULL)) != NULL) {
		  putchar('$'); putVcp(s, txmptr-1); putchar('$');
		  s = txmendptr;
	       } else {
		  fprintf(stderr, "TeX math within a comment must all be\
 on one line (file %s at line %d)\n", fname, lineno);
		  s += strlen(s);
	       }
	       continue;
	    }
	 } /* @if (code_cmnts)@ */

	 if ((comendptr =
		expmatch(s, (comtype == STANDARD) ? l_comend : l_acmend,
			 (char **) NULL, (char *) NULL)) != NULL) {
	    putKcp(s, comendptr-1, TRUE);
	    s = comendptr;
	    incomm = FALSE;
	    printf("\\CE{}");
	 } else {
	    comptr = s;
	    s += strlen(s);
	    putKcp(comptr, s-1, TRUE);
	 }
	 continue;

	 /* check for end of string */
      } else if (instr) {
	 if ((strendptr =
	      expmatch(s, l_strend, (char **) NULL, (char *) NULL)) != NULL) {
	    putKcp(s, strendptr-1, TRUE);
	    s = strendptr;
	    instr = FALSE;
	    printf("\\SE{}");
	 } else {
	    strptr = s;
	    s += strlen(s);
	    putKcp(strptr, s-1, TRUE);
	 }
	 continue;

	 /* check for end of character string */
      } else if (inchr) {
	 if ((chrendptr =
	      expmatch(s, l_chrend, (char **) NULL, (char *) NULL)) != NULL) {
	    putKcp(s, chrendptr-1, TRUE);
	    s = chrendptr;
	    inchr = FALSE;
	    printf("\\SE{}");
	 } else {
	    chrptr = s;
	    s += strlen(s);
	    putKcp(chrptr, s-1, TRUE);
	 }
	 continue;
      }

      /* print out the line */
      chrptr = s;
      s += strlen(s);
      putKcp(chrptr, s-1, FALSE);

   } while (*s);
}


/*
 * Output a %%\LaTeX%% command to tab to column "col" (see the documentation
 * for a partial explanation of the bizarre brace arrangement).
 */
#define tabto(col) printf("}\\Tab{%d}{", col);


/*
 * @islidchr()@ is @TRUE@ for things that can begin identifiers;
 * @isidchr@ is @TRUE@ of identifier constituents.
 */
#define islidchr(c)(((isalpha(c) || (strchr(l_id, c))) && c!=0))
#define isidchr(c)(((isalnum(c) || (strchr(l_id, c))) && c!=0))


/*
 * Get the identifier starting at @s@.	It is assumed that @s@ may indeed
 * start an identifier.  Value is %$>0$% for a keyword --- the count of
 * characters in the keyword --- and %$<0$% if not a keyword, in which
 * case the value returned is the negative of the number of bytes in
 * the matched identifier.
 *
 * This function checks @nokeyw@ and won't check to see if the
 * identifier found is a keyword if it is @TRUE@.
 */
int getid(char *s)
{
   char **ss	= l_keywds;
   int	i	= 1;
   char *cp	= s;
   int	firstc	= *s;

   while (++cp, isidchr(*cp))
      i++;
   if (nokeyw)
      return -i;
   while ((cp = *ss++) != '\0') {
      if (!l_onecase && firstc != *cp)
	 continue;
      if ((*re_strncmp)(s, cp, i) == 0 && !isidchr(cp[i]))
	 return i;
   }
   return -i;
}


/*
 * Calculate the width of a string, including tabs
 */
int width(register char *s, register char *os)
{
   register int i = 0, c;

   while (s < os) {
      c = *s++;
      if (c == '\t') {
	 /* i = (i + 8) &~ 7; */
	 i = ((i + TabWidth) / TabWidth) * TabWidth;
	 continue;
      }
      if (c < ' ')
	 i += 2;
      else
	 i++;
   }
   return i;
}


/*
 * Write out a portion of the line
 */
boolean putKcp(char *start, char *end, boolean nix)
/* start	Start of string to write
   end		End of string to write
   nix		Don't look for identifiers, numbers
   returns  whether we ate only as much as we ought to */
{
   int i, c;

   while (start <= end) {
      c = *start++;
      /*
       * take care of nice tab stops ...
       * ... and of space runs
       */
      if (c == '\t' || (c == ' ' && *start == ' ')) {
	 while (start <= end && ( *start == '\t' || *start == ' ' ))
	    start++;
	 tabto(width(_sstart, start));
	 continue;
      }

      /*
       * First split off numbers.  We have a rather ad hoc
       * definition:  A number is a digit followed by any number
       * of digits or letters, and periods.
       * (Additionally a number can start with %|$|% (e.g. hex numbers).)
       * This produces meaningless parses --- %$.2$% is parsed as %|.|%
       * followed by the number %|2|% --- but should produce decent
       * results for most languages (outside of maybe FORTRAN and DCL).
       */
      if (!nix) {
		 if (c == '#' || islidchr(c)) {
		    i = getid(--start);
		    if (i > 0)
		       printf("\\K{");
		    else {
		       printf("\\V{");
		       i = substvarname(&start, -i);
		    }
		    while (--i >= 0) {
		       c = *start++;
		       outchar(c);
		    }
		putchar('}');
		    continue;
		 }
		 else if (isdigit(c) || c == '$') {
		    printf("\\N{");
		    do {
		       if (c == 'l')
				  printf("$\\ell$");
		       else
				  outchar(c);
		       c = *start++;
		    } while (isalnum(c) || (c == '.' && *start != '.'));
		    putchar('}');
		    start--;
		    continue;
		 }
      }
      outchar(c);
   }
   return (start-1)==end;
}



/*
 * Write out a portion of the line verbatim
 */
void putVcp(char *start, char *end)
/* start	Start of string to write
   end		End of string to write */
{
   for ( ; start <= end; start++) {
      putchar(*start);
   }
}


/*
 * Output a string, escaping special characters
 */
void putstr(register char *cp)
{
   register int c;

   if (cp == NULL)
      return;
   while ((c = *cp++) != '\0')
      outchar(c);
}


/*
 * The following table converts ASCII characters to a printed
 * representation, taking care of all the %%\LaTeX%% quoting.  N.B.: all
 * single-character strings are assumed to be equivalent to the
 * character for that index (i.e., @printtab['c']@ can't be @"f"@).
 * (This is purely for efficiency hacking.)
 *
 * Notes:
 *  Some pairs of characters are handled specially within @outchar()@;
 *  this table contains no indication when that happens.
 *  %|`|% is output as %|{`}|% to avoid various ligatures, such as %|!`|%.
 *  The %|''|% and %|--|% (and %|---|%) ligatures are not a problem
 *  because those characters are output as macros anyway.  Using %|{`}|%
 *  is sufficient since nothing we put out will ever be given to the
 *  hyphenation algorithms anyway.
 *
 * @ttprinttab@ is the same for the emulated verbatim mode
 */

char *printtab[256] = {
   "\0x",   "\\^A",  "\\^B",  "\\^C",  "\\^D",  "\\^E",  "\\^F",  "\\^G",
   "\\^H",  "\t",    "}}\n",  "\\^K",  "\0x",   "\\^M",  "\\^N",  "\\^O",
   "\\^P",  "\\^Q",  "\\^R",  "\\^S",  "\\^T",  "\\^U",  "\\^V",  "\\^W",
   "\\^X",  "\\^Y",  "\\^Z",  "\\^[",  "\\^\\!","\\^]",  "\\^\\^","\\^\\_",
   " ",     "!",     "\\3",   "\\#",   "\\$",   "\\%",   "\\&",   "{'}",
   "(",     ")",     "*",     "+",     ",",     "\\-",   ".",     "/",
   "0",     "1",     "2",     "3",     "4",     "5",     "6",     "7",
   "8",     "9",     ":",     ";",     "\\<",   "=",     "\\>",   "?",
   "@",     "A",     "B",     "C",     "D",     "E",     "F",     "G",
   "H",     "I",     "J",     "K",     "L",     "M",     "N",     "O",
   "P",     "Q",     "R",     "S",     "T",     "U",     "V",     "W",
   "X",     "Y",     "Z",     "[",     "\\2",   "]",     "\\5",   "\\_",
   "{`}",   "a",     "b",     "c",     "d",     "e",     "f",     "g",
   "h",     "i",     "j",     "k",     "l",     "m",     "n",     "o",
   "p",     "q",     "r",     "s",     "t",     "u",     "v",     "w",
   "x",     "y",     "z",     "\\{",   "\\|",   "\\}",   "\\~{}", "\\^?",
   "\200",  "\201",  "\202",  "\203",  "\204",  "\205",  "\206",  "\207",
   "\210",  "\211",  "\212",  "\213",  "\214",  "\215",  "\216",  "\217",
   "\220",  "\221",  "\222",  "\223",  "\224",  "\225",  "\226",  "\227",
   "\230",  "\231",  "\232",  "\233",  "\234",  "\235",  "\236",  "\237",
   "\240",  "\241",  "\242",  "\243",  "\244",  "\245",  "\246",  "\247",
   "\250",  "\251",  "\252",  "\253",  "\254",  "\255",  "\256",  "\257",
   "\260",  "\261",  "\262",  "\263",  "\264",  "\265",  "\266",  "\267",
   "\270",  "\271",  "\272",  "\273",  "\274",  "\275",  "\276",  "\277",
   "\300",  "\301",  "\302",  "\303",  "\304",  "\305",  "\306",  "\307",
   "\310",  "\311",  "\312",  "\313",  "\314",  "\315",  "\316",  "\317",
   "\320",  "\321",  "\322",  "\323",  "\324",  "\325",  "\326",  "\327",
   "\330",  "\331",  "\332",  "\333",  "\334",  "\335",  "\336",  "\337",
   "\340",  "\341",  "\342",  "\343",  "\344",  "\345",  "\346",  "\347",
   "\350",  "\351",  "\352",  "\353",  "\354",  "\355",  "\356",  "\357",
   "\360",  "\361",  "\362",  "\363",  "\364",  "\365",  "\366",  "\367",
   "\370",  "\371",  "\372",  "\373",  "\374",  "\375",  "\376",  "\377",
};

char *ttprinttab[256] = {
   "\0x",   "\\^A",  "\\^B",  "\\^C",  "\\^D",  "\\^E",  "\\^F",  "\\^G",
   "\\^H",  "\t",    "}}\n",  "\\^K",  "\0x",   "\\^M",  "\\^N",  "\\^O",
   "\\^P",  "\\^Q",  "\\^R",  "\\^S",  "\\^T",  "\\^U",  "\\^V",  "\\^W",
   "\\^X",  "\\^Y",  "\\^Z",  "\\^[",  "\\^\\!","\\^]",  "\\^\\^","\\^\\_",
   " ",     "!",     "{34}",  "{35}",  "{36}",  "{37}",  "{38}",  "{39}",
   "(",     ")",     "*",     "+",     ",",     "{45}",  ".",     "/",
   "0",     "1",     "2",     "3",     "4",     "5",     "6",     "7",
   "8",     "9",     ":",     ";",     "{60}",  "=",     "{62}",  "?",
   "@",     "A",     "B",     "C",     "D",     "E",     "F",     "G",
   "H",     "I",     "J",     "K",     "L",     "M",     "N",     "O",
   "P",     "Q",     "R",     "S",     "T",     "U",     "V",     "W",
   "X",     "Y",     "Z",     "[",     "{92}",  "]",     "{94}",  "{95}",
   "{96}",  "a",     "b",     "c",     "d",     "e",     "f",     "g",
   "h",     "i",     "j",     "k",     "l",     "m",     "n",     "o",
   "p",     "q",     "r",     "s",     "t",     "u",     "v",     "w",
   "x",     "y",     "z",     "{123}", "{124}", "{125}", "{126}", "\\^?",
   "\200",  "\201",  "\202",  "\203",  "\204",  "\205",  "\206",  "\207",
   "\210",  "\211",  "\212",  "\213",  "\214",  "\215",  "\216",  "\217",
   "\220",  "\221",  "\222",  "\223",  "\224",  "\225",  "\226",  "\227",
   "\230",  "\231",  "\232",  "\233",  "\234",  "\235",  "\236",  "\237",
   "\240",  "\241",  "\242",  "\243",  "\244",  "\245",  "\246",  "\247",
   "\250",  "\251",  "\252",  "\253",  "\254",  "\255",  "\256",  "\257",
   "\260",  "\261",  "\262",  "\263",  "\264",  "\265",  "\266",  "\267",
   "\270",  "\271",  "\272",  "\273",  "\274",  "\275",  "\276",  "\277",
   "\300",  "\301",  "\302",  "\303",  "\304",  "\305",  "\306",  "\307",
   "\310",  "\311",  "\312",  "\313",  "\314",  "\315",  "\316",  "\317",
   "\320",  "\321",  "\322",  "\323",  "\324",  "\325",  "\326",  "\327",
   "\330",  "\331",  "\332",  "\333",  "\334",  "\335",  "\336",  "\337",
   "\340",  "\341",  "\342",  "\343",  "\344",  "\345",  "\346",  "\347",
   "\350",  "\351",  "\352",  "\353",  "\354",  "\355",  "\356",  "\357",
   "\360",  "\361",  "\362",  "\363",  "\364",  "\365",  "\366",  "\367",
   "\370",  "\371",  "\372",  "\373",  "\374",  "\375",  "\376",  "\377",
};



#define EMDASH (-1)
/*
 * Output one character, fixed up as required.	Since there is no call-back
 * to tell @outchar()@ to flush what it has stored, it must always produce
 * some output --- it can't simply retain state.  This makes certain
 * translations impossible, but we can live without them for now....
 */
void outchar(int c)
{
	if (!latex_tt)
	{
		if (c == ' ') {
			putchar('_');
			goto fin;
		}
		switch (lastout) {
			case '.':
			case '|':
				if (c == lastout)
					printf("\\,");
				break;
			case ' ':
#if 0   /* gvr hates this trick */
				if (incomm && c == '-') {
					printf("---");
					c = EMDASH;    /* For future cleverness... */
					goto fin;
				}
#endif
				break;
			case '[':
				if (c == ']')
					printf("\\,");
				break;
			case '-':
				if (c == '>')
					printf("\\!");
				break;
			case '<':
				if (c == '-')
					printf("\\!");
				break;
		}
		if (incomm && c == '-') {
			putchar('-');
			goto fin;
		}
		printtab[(unsigned char)c][1] ?
			printf("%s", printtab[(unsigned char)c]) : putchar(c);
	fin:
		lastout = c;
	}
	else
		c==32 ? putchar('~') :
			ttprinttab[(unsigned char)c][1] ?
			printf("\\symbol%s", ttprinttab[(unsigned char)c]) : putchar(c);
}


/*
 *	Look for a procedure beginning on this line
 */
boolean isprocNorm(char *s)
{
    pname[0] = '\0';
    if ((!l_toplex || blklevel == 0)
	    && expmatch(s, l_prcbeg, (char **) NULL, pname) != NULL
	    && expmatch(s, l_noproc, (char **) NULL, (char *) NULL) == NULL)
    {
	procedures_pending++;
	blklevel++;
	return TRUE;
    }
    return FALSE;
}

/*	Special version of the above for C functions */
boolean isprocC(char *s)
{
   char		cheat[BUFFERSIZE];
   char		*j=s, *i=cheat;
   boolean	comm=FALSE, string=FALSE, schar=FALSE;
   int		brack=0;

   if (blklevel!=0) return FALSE;
   while (*j)
   {
     if (*j=='"' && !comm && !schar) string=(string+1)%2;
     else if (*j=='\'' && !comm && !string) schar=(schar+1)%2;
     else if (*j=='\\' && !comm) j++;
     else if (!comm && !string && !schar && *j=='{') brack++;   
     else if (!comm && !string && !schar && *j=='}') brack--;
     else if (!comm && !string && !schar && *j=='#') break;
     else if (!comm && !string && !schar && *j=='/' && *(j+1)=='/') break;
     else if (!comm && !string && !schar && *j=='/' && *(j+1)=='*') comm=TRUE;
     else if (         !string && !schar && *j=='*' && *(j+1)=='/') 
       {comm=FALSE; j++;}
     else if (!brack && !comm && !string && !schar)
       *i++=*j;
     j++;
   }
   *i = '\0';
 
   return isprocNorm(cheat);
}


/* The VMS code below has been absolutely untested for the last few years.
 * Don't ask me about it. Please. MPi
 */

/*
 * @getredirection()@ is intended to aid in porting C programs
 * to VMS (Vax-11 C) which does not support %|>|% and %|<|%
 * I/O redirection.  With suitable modification, it may
 * useful for other portability problems as well.
 *
 * Modified, 24-Jan-86 by Jerry Leichter
 *	When creating a new output file, force the maximum record size to
 *	512; otherwise, it ends up as 0 (though the C I/O system won't write
 *	a record longer than 512 bytes anyway) which will cause problems if
 *	the file is later opened for @APPEND@ --- if the maximum record size
 *	is 0, C will use the length of the longest record written to the file
 *	for its buffer!
 */

#ifdef	vms
#  include	<stdio.h>
#  include	<errno.h>

   int
getredirection(argc, argv)
   int	argc;
   char **argv;
/*
 * Process VMS redirection args.  Exit if any error is seen.
 * If @getredirection()@ processes an argument, it is erased
 * from the vector.  @getredirection()@ returns a new @argc@ value.
 *
 * Warning: do not try to simplify the code for VMS.  The code
 * presupposes that @getredirection()@ is called before any data is
 * read from @stdin@ or written to @stdout@.
 *
 * Normal usage is as follows:
 *
 *@	main(argc, argv)
 *	int		argc;
 *	char		*argv[];
 *	{
 *		argc = getredirection(argc, argv);
 *	}@
 */
{
   register char	*ap;	/* Argument pointer */
   int			i;	/* @argv[]@ index */
   int			j;	/* Output index */
   int			file;	/* File_descriptor */

   for (j = i = 1; i < argc; i++) {   /* Do all arguments */
      switch (*(ap = argv[i])) {
      case '<':                 /* %|<file|% */
	 if (freopen(++ap, "r", stdin) == NULL) {
	    perror(ap); 	/* Can't find file */
	    exit(errno);	/* Is a fatal error */
	 }
	 break;

      case '>':                 /* %|>file|% or %|>>file|% */
	 if (*++ap == '>') {    /* %|>>file|% */
	    /*
	     * If the file exists, and is writable by us,
	     * call @freopen()@ to append to the file (using the
	     * file's current attributes).  Otherwise, create
	     * a new file with "vanilla" attributes as if
	     * the argument was given as %|>filename|%.
	     * @access(name, 2)@ is @TRUE@ if we can write on
	     * the specified file.
	     */
	    if (access(++ap, 2) == 0) {
	       if (freopen(ap, "a", stdout) != NULL)
		  break;	/* Exit @case@ statement */
	       perror(ap);	/* Error, can't append */
	       exit(errno);	/* After @access@ test */
	    }			/* If file accessable */
	 }
	 /*
	  * On VMS, we want to create the file using "standard"
	  * record attributes.	@create(...)@ creates the file
	  * using the caller's default protection mask and
	  * "variable length, implied carriage return"
	  * attributes.  @dup2()@ associates the file with @stdout@.
	  */
	 if ((file = creat(ap, 0, "rat=cr", "rfm=var", "mrs=512")) == -1
	     || dup2(file, fileno(stdout)) == -1) {
	    perror(ap); 	/* Can't create file    */
	    exit(errno);	/* is a fatal error	*/
	 }			/* If %|>|% creation	*/
	 break; 		/* Exit @case@ test	*/

      default:
	 argv[j++] = ap;	/* Not a redirector	*/
	 break; 		/* Exit @case@ test	*/
      }
   }				/* For all arguments	*/
   argv[j] = NULL;		/* Terminate @argv[]@	*/
   return j;			/* Return new @argc@	*/
}

#else	/* @!vms@ */

int getredirection(int argc, char **argv)
   /*
    * Dummy routine.
    */
{
   return argc;
}

#endif	/* @!vms@ */

#include "lgutil.c"
/* Helper functions */

