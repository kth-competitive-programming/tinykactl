/* sccsid[] = "@(#)lgrindef.h   3.6 (MPi) 3/8/98";
 * rcsid[] =
 * "$Id: lgrindef.h,v 1.3 1999/05/26 07:30:03 mike Exp $";
 *
 * Created 19 February 1996
 */

#define BUFFERSIZE 8192
int tgetent(char *bp, char *name, char *file);
int tgetnum(char *id);
int tgetflag(char *id);
char *tgetstr(char *id, char **area);
