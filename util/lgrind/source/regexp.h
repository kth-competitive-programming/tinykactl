/* sccsid[] = "@(#)regexp.h     3.6 (MPi) 3/8/98";
 * rcsid[] =
 * "$Id: regexp.h,v 1.3 1999/05/26 07:30:03 mike Exp $";
 * 
 * Created 19 February 1996
 */

typedef int    boolean;
#define TRUE   1
#define FALSE  0
int lc_strncmp(const char *s1, const char *s2, size_t len);
char *convexp(char *re);
char *expmatch(register char *s, register char *re, char **strtptr, char *mstring);
