#ifndef lint
#ifdef standalone_lgutil
static char sccsid[] = "@(#)lgutil.c     3.6 (MPi) 24/3/98";
static char rcsid[] =
   "$Id: lgutil.c,v 1.7 1999/12/18 21:54:29 mike Exp $";
#endif /* standalone_lgutil */
#endif

/* lgutil.c
 * Utility Functions for LGrind
 * This file is @#include@d from lgrind.c (likely to change)
 */

/* Copyright %%\copyright%% 1998,1999 Michael Piefel
 *
 * This file is something like GPL, though LGrind is BSD.
 * I don't want to become a lawyer.
 */

/*
 * Internal_Help() --- show help
 */

void Internal_Help()
{
   printf("lgrind -- general purpose \"pretty printer\" for use with LaTeX.\n");
   printf("usage:  lgrind  [options] <name> ...\n");
   printf("-e     process embedded text in a LaTeX file\n");
   printf("-i     format source code for inclusion in a LaTeX document.\n");
   printf("-n     don't boldface keywords.\n");
   printf("-a     don't treat @, etc. specially in LaTeX.\n");
   printf("-c     don't treat @, etc. specially in comments.\n");
   printf("-      take input from standard input.\n");
   printf("-o <file>     write to file (instead of standard output).\n");
   printf("-t <width>    change tab width (default 8).\n");
   printf("-h <header>   specifies text in header (default: none).\n");
   printf("-v <varfile>  take variable substitutions from file.\n");
   printf("-d <deffile>  use a different language definitions file, default:\
\n              \"%s\"\n", defsfile);
   printf("-l<language>  choose the language to use.\n");
   printf("-s     show a list of currently known languages.\n\n");
   printf("If neither -e nor -i are specified, a complete LaTeX-file is produced.\n\n");
   printf("Direct comments and questions to lgrind@gmx.net\n");
}


typedef struct langRec {
	char *name;
	char *alternatives;
	struct langRec *next; } langRec;

void AddToLList(char *line, langRec **into, int *chainLength)
{
	char *token, *item, *alts;

	if (*line!='#' && *line!='\n')
	{
		item=strdup(line);
		if ((token=strtok(item, "|:\\\n")) == NULL) return;
		(**into).next=(langRec*)malloc(sizeof(langRec));
		*into=(**into).next;
		(**into).name=strdup(token);
		(*chainLength)++;
		if ((token=strtok(NULL, "|:\\\n")) == NULL)
		{
			(**into).alternatives="\0";
			return;
		}
		(**into).alternatives=strdup(token);
		while ((token=strtok(NULL, "|:\\\n")) != NULL)
		{
			alts=(**into).alternatives;
			(**into).alternatives=(char*)malloc(
				strlen((**into).alternatives)+strlen(token)+1);
			/* This is extremely poor style and dangerous. I leave memory
			 * allocated here because after invocation of this help facility
			 * the program will stop anyway. In this context it is safe. */
			strcpy((**into).alternatives, alts);
			strcat((**into).alternatives, ", ");
			strcat((**into).alternatives, token);
		}
	}
}

void Internal_Help_Language_List()
{
	FILE *tf;
	int check, i, llch;
	langRec *lch, *rch, *currlch;
	/*	@lch2@ was originally "language chain", but I guess
		it's "left" as well */

	printf("When specifying a language case is insignificant. You can use the\n");
	printf("name of the language, or, where available, one of the synonyms in\n");
	printf("parantheses. Thus the following are legal and mark Tcl/Tk, Pascal\n");
	printf("and Fortran input, respectively:\n");
	printf("   lgrind -ltcl/tk ...\n");
	printf("   lgrind -lpaSCAL ...\n");
	printf("   lgrind -lf ...\n");
	printf("The list of languages currently available in your lgrindef file:\n");
	tf = fopen(defsfile, "rt");
	if (tf == NULL)
	{
		fprintf(stderr,  "cannot find lgrindef file `%s'\n", defsfile);
		return;
	}

	llch=0;
	currlch=lch=(langRec*)malloc(sizeof(langRec));
	(*currlch).name="";
	*config='\n';
	do {
		check=0;
		if (*config=='\n' || config[strlen(config)-2]!='\\')
			check=1;
		if (fgets(config, BUFFERSIZE, tf)==NULL) break;
		if (check!=0) AddToLList(config, &currlch, &llch);
	} while (strcmp((*currlch).name, "EndOfLanguageDefinitions")!=0);
	rch=lch;
	for (check=0; check<llch/2; check++)
		rch=(*rch).next;
	for (check=0; check<llch/2; check++)
	{
		lch=(*lch).next;
		rch=(*rch).next;
		printf("    %s", (*lch).name);
		if (*((*lch).alternatives)) printf("  (%s)", (*lch).alternatives);
		else printf("    ");
		for (i=strlen((*lch).name)+strlen((*lch).alternatives);
				i<30; i++) putchar(' ');
		if (rch!=currlch)
		{
			printf("%s", (*rch).name);
			if (*((*rch).alternatives)) printf("  (%s)", (*rch).alternatives);
		}
		printf("\n");
	}
}


/*
 * Redefine Chartab from lgrindef file
 */
void parsechartab(void)
{
    char *i=buf, *j=chartab, c;
    int  charnum=0;

    while (*i++!=':') {}
    while ((c=*i++)!='\0') {
		if (c==':') continue;
		charnum=(c>='0' && c<='9') ? (int)c-48 : tolower(c)-87;
		charnum=charnum << 4; c=*i++;
		charnum+=(c>='0' && c<='9') ? (int)c-48 : tolower(c)-87;
		i++;

		printtab[charnum]=j;
		while (*i!=':')
			if (*i=='\\') {
				switch (*++i) {
				case ':':  *j++=':'; break;
				case '\\': *j++='\\'; break;
				}; i++;
			} else *j++=*i++;
		*j++='\0';
	}

}

/*
 * Parses the %|lgrindef|% file for a preamble
 */
void parsepreamble(char *destination)
{
    char *i=buf, *j=destination;

    while (*i++!=':') ;
    while (*i) {
      if (*i=='\\') {
	switch (*++i) {
	  case 'n':  *j++='\n'; break;
	  case 't':  *j++='\t'; break;
	  case 'f':  *j++='\f'; break;
	  case '\\': *j++='\\'; break;
	  default:   fprintf(stderr, "Bad preamble entry: incorrect '\\'\n");
	}; i++;
      } else *j++=*i++;
      *j='\0';
    }
}

/*
 * Sets the default preambles
 */
void setpreambles(void)
{
    strcpy(preamble,
"\\documentclass[a4paper]{article}\n\
\\usepackage[procnames,noindent]{lgrind}\n\
\\usepackage{fancyhdr}\n\
\\pagestyle{fancy}\n\
\\begin{document}\n");
    strcpy(postamble, "\\end{document}\n");
    strcpy(preamble2,
"\\lhead[\\fancyplain{}{\\bf\\thepage}]\
{\\fancyplain{}{\\bf \f}}\n\
\\rhead[\\fancyplain{}{\\bf \f}]\
{\\fancyplain{}{\\bf\\thepage}}\n\
\\cfoot{}\n");
    strcpy(config, "");
}

/*
 * prints a preamble, substituting %|\f|% with the current
 * file's name (sorry, no more form feeds)
 */
void printpreamble(char *string)
{
   char *i;
   while (*string)
     if (*string=='\f')
	{ i=fname-1;
	  while (*(++i)) outchar(*i);
          string++;
	}
     else putchar(*string++);
}

/*
 * try to create an executable file to store the new lgrindef-file
 */
void writeDefsfileInExe(char *progname, char *newdefsfile)
{
	char	*buffer, *i;
	FILE     *progfile, *newfile;
	long     pos=0;
	int      ret;

	buffer = (char*) malloc(30000);
	/* So small? Why in chunks? Well, it's gotta run on machines with
	  only limited access to their resources (you know, the IBM PC) */
	progfile=fopen(progname, "rb");
	newfile=fopen("lgrind.new", "wb");

	if (buffer && progfile && newfile)
	{
		fread(buffer, 1, 200, progfile);
		do {
			ret=fread(buffer+200, 1, 29500, progfile);
			for(i=buffer; i<buffer+ret; i++)
			if (*i=='D' &&
				*(i+1)=='e' &&
				*(i+2)=='F' &&
				*(i+3)=='s' &&
				*(i+4)=='B' &&
				*(i+5)=='u' &&
				*(i+6)=='F' &&
					strcmp(defsfile, i+7)==0) {
				memcpy(i+7, newdefsfile, strlen(newdefsfile)+1);
			}
			fwrite(buffer, 1, ret==29500 ? ret : ret+200, newfile);
			memcpy(buffer, buffer+29500, 200);
			pos+=29500;
		} while (ret==29500);
		fclose(progfile);
		fclose(newfile);
	}
	free(buffer);
}

/*
 * Reads a variable substitution table from a file
 */
varsubst *parsevartab(char* fname)
{
	FILE *f = fopen(fname, "rt");
	char linebuf[201], *cp;
	varsubst *varsubsts=NULL, *substitem, *substlistpos;

	if (f==NULL) return;
	while (!feof(f))
	{
		fscanf(f, "%200[^\n]", linebuf);
		fscanf(f, "\n");
		cp=strchr(linebuf, '=');
		if (cp==NULL) continue;
		*cp++='\0';
		substitem=(varsubst*)malloc(sizeof(varsubst));
		substitem->var=strdup(linebuf);
		substitem->subst=strdup(cp);
		substitem->next=NULL;
		if (varsubsts==NULL)
		{
			varsubsts=substitem;
			substlistpos=substitem;
		} else {
			substlistpos->next=substitem;
			substlistpos=substitem;
		}
	}
	fclose(f);
	return varsubsts;
}

/*
 * Replaces a variable by alternate representation
 */
int substvarname(char **ident, int i)
{
	varsubst *substlistpos = varsubstlist;

	while (substlistpos!=NULL)
	{
		if (re_strncmp(*ident, substlistpos->var, i)==0)
		{
			*ident+=i; /* skip i characters in input */
			printf("%s", substlistpos->subst);
			return 0;
		}
		substlistpos=substlistpos->next;
	}
	return i;
}
