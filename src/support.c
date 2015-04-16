/* @(#) support.c 1.4@(#) 01/03/04
 * PBL Interpreter
 *	
 *  support.c
 *  support routines
 *
 * John Willis
 * willisj@atlantis.clogic-int.com
 *
 * 2/5/99	1:44 PM		added clearlines()
 *
 * 2/2/99	12:15 PM	added clearargs()
 *
 * 2/2/99	12:10 PM	initial work
 */



#include "glob.h"


void clearargs(void);
void clearlines(void);  
/*void perror(int, int);*/

/* clearargs():		clear the argument list */
void clearargs(void)
{
	int i, j;

	for(i = 0; i <= _ARGSAD; i++)
	{
		for(j = 0; j <= _CHARSAD; j++)
			arglist[i][j] = 0;
	}
}

/* clearlines(): empty the lines array */
void clearlines(void)
{
	int i, j;
	for(i = 0; i <= _ARGSAD; i++)
	{	
		for(j = 0; j <= _CHARSAD; j++)
			lines[i][j] = 0;
	}
}

/*void perror(int code, int line)
{
	switch(code) {
		case 1:
			printf("pbl error #%d: procedure \"main\" not found\n", code);
			break;
		case 2:
			printf("pbl error #%d: unbalanced parens in line %d\n", code, line);
			break;
		case 3:
			printf("pbl error #%d: user break in line %d\n", code, line);
			break;
		default:
			printf("pbl error #%d: error in error handler\n", code);
			break;
	}
}*/
