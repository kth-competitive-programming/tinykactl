#ifndef lint
static char sccsid[] = "@(#)regexp.c     1.2 (LBL) 12/4/85";
static char rcsid[] =
   "$Id: regexp.c,v 1.3 1999/05/27 16:17:43 mike Exp $";
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

/*
 * Regular expression matching routines for lgrind/tgrind/tfontedpr.
 *
 * These routines were written by Dave Presotto (I think) for vgrind.
 * Minor mods & attempts to improve performance by Van Jacobson
 * (van@@lbl-rtsg) and Chris Torek (chris@@maryland).
 *
 * Modifications.
 * --------------
 *    Sep 91	George V Reilly	Fixed up some bogus uses of @NIL@ and @NULL@.
 * 30 Mar 85	Van & Chris	Changed @expmatch()@ to return pointer to
 *				start of what was matched in addition to
 *				pointer to match end.  Several changes to
 *				improve performance (too numerous to mention).
 * 11 Dec 84	Dave Presotto	Written.
 */


#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <string.h>
#include "regexp.h"

#define makelower(c) (isupper((c)) ? tolower((c)) : (c))

extern char *l_id;
static void expconv(void);	 /* forward declaration */

int    (*re_strncmp)(const char *, const char *, size_t);	 
			/* function used by @expmatch()@ to compare
			* strings.  The caller should make it point to
			* @strncmp()@ if case is significant &
			* @lc_strncmp()@ otherwise.
			*/


/*  @lc_strncmp()@ ---	like @strncmp()@ except that we convert the
 *			first string to lower case before comparing.
 */
int lc_strncmp(register const char *s1, register const char *s2, register size_t len)
{
   while (len-- > 0)
      if (*s2 - makelower(*s1))
	 return 1;
      else
	 s2++, s1++;
   
   return 0;
}


/*  The following routine converts an irregular expression to
 *  internal format.
 *
 *  Either meta symbols (%|\a|%, %|\d|%, or %|\p|%) or character strings
 *  or operations (alternation or parenthesizing) can be specified.
 *  Each starts with a descriptor byte.  The descriptor byte
 *  has @STR@ set for strings, @META@ set for meta symbols,
 *  and @OPER@ set for operations.  The descriptor byte can also have
 *  the @OPT@ bit set if the object defined is optional.  Also @ALT@
 *  can be set to indicate an alternation.
 *
 *  For metasymbols, the byte following the descriptor byte identities
 *  the meta symbol (containing an ASCII @'a'@, @'d'@, @'p'@, @'|'@,
 *  or @'('@).  For strings, the byte after the descriptor is a
 *  character count for the string:
 *@
 *	meta symbols :=	descriptor
 *			symbol
 *
 *	strings :=	descriptor
 *			character count
 *			the string
 *
 *	operations :=	descriptor
 *			symbol
 *			character count@
 */


/*
 *  handy macros for accessing parts of match blocks
 */
#define MSYM(A)	 (*(A+1))	/* symbol in a meta symbol block */
#define MNEXT(A) (A+2)		/* character following a metasymbol block */

#define OSYM(A)	 (*(A+1))	/* symbol in an operation block */
#define OCNT(A)	 (*(A+2))	/* character count */
#define ONEXT(A) (A+3)		/* next character after the operation */
#define OPTR(A)	 (A+*(A+2))	/* place pointed to by the operator */

#define SCNT(A)	 (*(A+1))	/* byte count of a string */
#define SSTR(A)	 (A+2)		/* address of the string */
#define SNEXT(A) (A+2+*(A+1))	/* character following the string */


/*
 *  bit flags in the descriptor 
 */
#define OPT	 1
#define STR	 2
#define META	 4
#define ALT	 8
#define OPER	16

char *ure;		/* pointer current position in unconverted exp */
char *ccre;		/* pointer to current position in converted exp */



/*
 * Convert an irregular expression to the internal form
 */
char *convexp(char *re)
/* re	 unconverted irregular expression */
{
   register char *cre;	/* pointer to converted regular expression */
   
   /* allocate room for the converted expression */
   if (re == NULL)
      return NULL;
   if (*re == '\0')
      return NULL;
   cre = (char*)malloc(4 * strlen(re) + 3);
   ccre = cre;
   ure = re;
   
   /* start the conversion with a %|\a|% */
   *cre = META | OPT;
   MSYM(cre) = 'a';
   ccre = MNEXT(cre);

   /* start the conversion (it's recursive) */
   expconv();
   *ccre = 0;
   return cre;
}


/*
 * Actually do the conversion
 */
static void expconv(void)
{
   register char *cs;	/* pointer to current symbol in converted exp */
   register char c;	/* character being processed */
   register char *acs;	/* pointer to last alternate */
   register int temp;

   /* let the conversion begin */
   acs = NULL;
   cs = NULL;
   while (*ure != '\0') {
	  switch (c = *ure++) {

	  case '\\':
	 switch (c = *ure++) {

		/* escaped characters are just characters */
	 default:
		if (cs == NULL || (*cs & STR) == 0) {
		   cs = ccre;
		   *cs = STR;
		   SCNT(cs) = 1;
		   ccre += 2;
		} else
		   SCNT(cs)++;
		*ccre++ = c;
		break;

		/* normal(?) metacharacters */
	 case 'a':
	 case 'd':
	 case 'e':
	 case 'p':
		if (acs != NULL && acs != cs) {
		   do {
		  temp = OCNT(acs);
		  OCNT(acs) = ccre - acs;
		  acs -= temp;
		   } while (temp != 0);
		   acs = NULL;
		}
		cs = ccre;
		*cs = META;
		MSYM(cs) = c;
	    ccre = MNEXT(cs);
	    break;
	 }
	 break;
	 
	 /* just put the symbol in */
      case '^':
      case '$':
	 if (acs != NULL && acs != cs) {
	    do {
	       temp = OCNT(acs);
	       OCNT(acs) = ccre - acs;
	       acs -= temp;
	    } while (temp != 0);
	    acs = NULL;
	 }
	 cs = ccre;
	 *cs = META;
	 MSYM(cs) = c;
	 ccre = MNEXT(cs);
	 break;
	 
	 /* mark the last match sequence as optional */
      case '?':
	 if (cs)
		*cs = *cs | OPT;
	 break;
	 
	 /* recurse and define a subexpression */
      case '(':
	 if (acs != NULL && acs != cs) {
	    do {
	       temp = OCNT(acs);
	       OCNT(acs) = ccre - acs;
	       acs -= temp;
	    } while (temp != 0);
	    acs = NULL;
	 }
	 cs = ccre;
	 *cs = OPER;
	 OSYM(cs) = '(';
	 ccre = ONEXT(cs);
	 expconv();
	 OCNT(cs) = ccre - cs;		/* offset to next symbol */
	 break;
	 
	 /* return from a recursion */
      case ')':
	 if (acs != NULL) {
	    do {
	       temp = OCNT(acs);
	       OCNT(acs) = ccre - acs;
	       acs -= temp;
	    } while (temp != 0);
	    acs = NULL;
	 }
	 cs = ccre;
	 *cs = META;
	 MSYM(cs) = c;
	 ccre = MNEXT(cs);
	 return;
	 
	 /* Mark the last match sequence as having an alternate. */
	 /* The third byte will contain an offset to jump over the */
	 /* alternate match in case the first did not fail */
      case '|':
	 if (acs != NULL && acs != cs)
	    OCNT(ccre) = ccre - acs;	/* make a back pointer */
	 else
	    OCNT(ccre) = 0;
	 *cs |= ALT;
	 cs = ccre;
	 *cs = OPER;
	 OSYM(cs) = '|';
	 ccre = ONEXT(cs);
	 acs = cs;	/* remember that the pointer is to be filled */
	 break;
	 
	 /* if it's not a metasymbol, just build a character string */
      default:
	 if (cs == NULL || (*cs & STR) == 0) {
	    cs = ccre;
	    *cs = STR;
	    SCNT(cs) = 1;
	    ccre = SSTR(cs);
	 } else
	    SCNT(cs)++;
	 *ccre++ = c;
	 break;
      }
   }
   if (acs != NULL) {
      do {
	 temp = OCNT(acs);
	 OCNT(acs) = ccre - acs;
	 acs -= temp;
      } while (temp != 0);
      acs = NULL;
   }
   return;
} /* end of @expconv()@ */


/*
 *  The following routine recognises an irregular expression
 *  with the following special characters:
 *
 *	%|\?|%		means last match was optional
 *	%|\a|%		matches any number of characters
 *	%|\d|%		matches any number of spaces and tabs
 *	%|\p|%		matches any number of alphanumeric characters.
 *			The characters matched will be copied into
 *			the area pointed to by @mstring@.
 *	%|\||%		alternation
 *	%|\( \)|%	grouping used mostly for alternation and
 *			optionality
 *
 *  The irregular expression must be translated to internal form
 *  prior to calling this routine
 *
 *  The value returned is the pointer to the last character matched.
 *  If @strtptr@ is non-@NULL@, a pointer to the start of the string matched
 *  (excluding %|\a|% matches) will be returned at @*strtptr@.  
 *  If @mstring@ is non-@NULL@, the string matched by a %|\p|% will be copied
 *  into @mstring@.
 */

boolean _escaped;		/* true if we are currently @_escaped@ */
char *_sstart;			/* start of string.  Set in @putScp()@. */


char *expmatch(
   register char *s,		/* string to check for a match in */
   register char *re,		/* a converted irregular expression */
   char **strtptr,		/* where to put ptr to start of match */
   char *mstring)		/* where to put whatever matches a %|\p|% */
{
   register char *cs;		/* the current symbol */
   register char *ptr, *s1;	/* temporary pointer */
   register char c;		/* temporary */
   boolean matched;		/* a temporary @boolean@ */
   
   /* initial conditions */
   if (strtptr)
      *strtptr = '\0';
   if (re == NULL)
      return NULL;
   cs = re;
   matched = FALSE;
   
   /* loop till expression string is exhausted (or at least pretty tired) */
   while (*cs) {
      switch (*cs & (OPER | STR | META)) {
	 
	 /* try to match a string */
      case STR:
	 matched = !((*re_strncmp)(s, SSTR(cs), SCNT(cs)));
	 if (matched) {
	    
	    /* hoorah: it matches */
	    s += SCNT(cs);
	    cs = SNEXT(cs);
	 } else if (*cs & ALT) {
	    
	    /* alternation: skip to next expression */
	    cs = SNEXT(cs);
	 } else if (*cs & OPT) {
	    
	    /* the match is optional */
	    cs = SNEXT(cs);
	    matched = 1;		/* indicate a successful match */
	 } else {
	    
	    /* no match: error return */
	    return NULL;
	 }
	 break;
	 
	 /* an operator: do something fancy */
      case OPER:
	 switch (OSYM(cs)) {
	    
	    /* this is an alternation */
	 case '|':
	    if (matched)
	       
	       /* last thing in the alternation was a match: skip ahead */
	       cs = OPTR(cs);
	    else
	       
	       /* no match: keep trying */
	       cs = ONEXT(cs);
	    break;
	    
	    /* this is a grouping: recurse */
	 case '(':
	    ptr = expmatch(s, ONEXT(cs), strtptr, mstring);
	    if (ptr != NULL) {
	       
	       /* the subexpression matched */
	       matched = 1;
	       s = ptr;
	    } else if (*cs & ALT) {
	       
	       /* alternation: skip to next expression */
	       matched = 0;
	    } else if (*cs & OPT) {
	       
	       /* the match is optional */
	       matched = 1;	/* indicate a successful match */
	    } else {
	       
	       /* no match: error return */
	       return NULL;
	    }
	    cs = OPTR(cs);
	    break;
	 }
	 break;
	 
	 /* try to match a metasymbol */
      case META:
	 switch (MSYM(cs)) {
	    
	    /* try to match anything and remember what was matched */
	 case 'p':
	    /*
	     *  This is really the same as trying the match the
	     *  remaining parts of the expression to any subset
	     *  of the string.
	     */
	    s1 = s;
	    do {
	       ptr = expmatch(s1, MNEXT(cs), strtptr, mstring);
	       if (ptr != NULL && s1 != s) {
		  
		  /* we have a match: remember the match */
		  if (mstring) {
		     strncpy(mstring, s, (size_t)(s1 - s));
		     mstring[(int)(s1 - s)] = '\0';
		  }
		  return ptr;
		  
	       } else if (ptr != NULL && (*cs & OPT)) {
		  
		  /* %|\p|% was optional, so no match is ok */
		  return ptr;
		  
	       } else if (ptr != NULL) {
		  
		  /* not optional and we still matched */
		  return NULL;
	       }
	       if (!isalnum(*s1) && !strchr(l_id, *s1))
		  return NULL;
	       if (*s1 == '\\')
		  _escaped = _escaped ? FALSE : TRUE;
	       else
		  _escaped = FALSE;
	    } while (*s1++);
	    return NULL;
	    
	    /* try to match anything */
	 case 'a':
	    /*
	     *  This is really the same as trying the match the
	     *  remaining parts of the expression to any subset
	     *  of the string.
	     */
	    s1 = s;
	    do {
	       /*
		* Hack for an important special case: if the next thing
		* in the pattern is a string, just gobble characters until
		* we find something that matches that string (this saves
		* the cost of a recursive call on @expmatch()@ while scanning
		* for the start of comments or strings).  Since many
		* patterns end with a string, we also treat that as a
		* special case.
		*/
	       if(*(ptr = MNEXT(cs)) == STR) {
		  c = *SSTR(ptr);
		  while(*s1 && *s1 != c)
		     s1++;
		  
		  if (*s1 == 0)
		     return NULL;
		  
		  if (SNEXT(ptr) == 0 && (s1 != s || *cs & OPT)) {
		     /* next item is a string, it's the last item and
		      * the %|\a|% match is ok --- just loop to try & match
		      * the string.
		      */
		     if (strtptr)
			*strtptr = s1;
		     
		     cs = ptr;
		     s = s1;
		     break;
		  }
	       }
	       ptr = expmatch(s1, MNEXT(cs), strtptr, mstring);
	       if (ptr != NULL && (s1 != s || *cs & OPT)) {
		  
		  /* we have a match */
		  if (strtptr)
		     *strtptr = s1;
		  
		  return ptr;
		  
	       } else if (ptr != NULL) {
		  
		  /* not optional and we still matched */
		  return NULL;
	       }
	       if (*s1 == '\\')
		  _escaped = _escaped ? FALSE : TRUE;
	       else
		  _escaped = FALSE;
	    } while (*s1++);
	    return NULL;
	    
	    /* fail if we are currently @_escaped@ */
	 case 'e':
	    if (_escaped)
	       return NULL;
	    cs = MNEXT(cs); 
	    break;
	    
	    /* match any number of tabs and spaces */
	 case 'd':
	    ptr = s;
	    while (*s == ' ' || *s == '\t')
	       s++;

	    if (s != ptr || s == _sstart) {
	       
	       /* match: be happy */
	       matched = 1;
	       cs = MNEXT(cs); 
	    } else if (*s == '\n' || *s == '\0') {
	       
	       /* match: be happy */
	       matched = 1;
	       cs = MNEXT(cs); 
	    } else if (*cs & ALT) {
	       
	       /* try the next part */
	       matched = 0;
	       cs = MNEXT(cs);
	    } else if (*cs & OPT) {
	       
	       /* doesn't matter */
	       matched = 1;
	       cs = MNEXT(cs);
	    } else
	       
	       /* no match: error return */
	       return NULL;

	    break;
	    
	    /* check for end of line */
	 case '$':
	    if (*s == '\0' || *s == '\n') {
	       
	       /* match: be happy */
	       /* s++; was here
		* removed; now $ is left in stream to be matched again, which
		* is not bad (EOL can end several things at once. Also it
		* leaves things like CE on the same line.
		*/
	       matched = 1;
	       cs = MNEXT(cs);
	    } else if (*cs & ALT) {
	       
	       /* try the next part */
	       matched = 0;
	       cs = MNEXT(cs);
	    } else if (*cs & OPT) {
	       
	       /* doesn't matter */
	       matched = 1;
	       cs = MNEXT(cs);
	    } else
	       
	       /* no match: error return */
	       return NULL;
	    break;
	    
	    /* check for start of line */
	 case '^':
	    if (s == _sstart) {
	       
	       /* match: be happy */
	       matched = 1;
	       cs = MNEXT(cs);
	    } else if (*cs & ALT) {
	       
	       /* try the next part */
	       matched = 0;
	       cs = MNEXT(cs);
	    } else if (*cs & OPT) {
	       
	       /* doesn't matter */
	       matched = 1;
	       cs = MNEXT(cs);
	    } else
	       
	       /* no match: error return */
	       return NULL;
	    break;
	    
	    /* end of a subexpression: return success */
	 case ')':
	    return s;
	 }
	 break;
      }
   }
   return s;
}
