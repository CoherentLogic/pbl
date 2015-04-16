/* @(#) procs.c 1.4@(#) 01/03/04
 * PBL Interpreter
 *
 *  procs.c
 *  support for procedures
 *
 * John Willis
 * willisj@atlantis.clogic-int.com
 *
 * 2/2/1999	11:50 AM	added procend()
 *
 * 1/31/1999	8:00 PM		added findproc()
 *
 * 1/31/1999	7:46 PM		initial work
 *
 */

#include "glob.h"


int findproc(char name[_MAXCHARS], int lt);
int procend(char input[_MAXCHARS], int lt);
void tmpempty(void);

char tmp[_MAXCHARS]; 	/* global to this module */

/* findproc():	find a procedure and return the line at which it begins */
int findproc(char name[_MAXCHARS], int lt)
{
	int	i;
	int	argc = 0;
	
	/* empty the tmp array */
	tmpempty();	

	/* step through the lines of the program */
	for(i = 0; i <= lt; i++)
	{	
		tmpempty();	
	
		/* copy line i to tmp */
		strcpy(tmp, lines[i]);

		//printf("pbldebug:  line '%s' search\n", tmp);
		
		/* parse it */
		clearargs();
		argc = parse(tmp);
		
		//printf("pbldebug in FINDPROC: arg 1 %s, arg 2 %s\n", arglist[1], arglist[2]);		
		/* compare name array to arg 2 */ 
		if(strcmp(arglist[2], name) == 0)
		{
			if(strcmp(arglist[1], "procedure") == 0)
			{	
				/* found */
				return i + 1;
			}
			
		}
	}	
	return 9999; /* not found */
}

/* procend():  find the line a which a procedure ends */
int procend(char input[_MAXCHARS], int lt)
{
	int procstart = 0;
	int i = 0;
	int argc = 0;

	char tmp[_MAXCHARS];
	
	/* empty the tmp array */
	tmpempty();

	/* find the start of the procedure */
	procstart = findproc(input, lt);

	//printf("procend function finds, while searching through to line %d, that the function %s begins at line %d\n",lt,input,procstart);
	/* starting at procstart, step through the file line by line,
	   looking for the endproc statement */
	for(i = procstart; i <= lt; i++)
	{

		tmpempty();

		/* copy line i to tmp */
		strcpy(tmp, lines[i]);

		/* parse it */
		clearargs();
		argc = parse(tmp);	
		//printf("procend function finds that argument 1 on line %d is %s\n",i,arglist[1]);
		if((strcmp(arglist[1], "endproc")) == 0)
			return i + 1;
		
		if((strcmp(arglist[1], "endprog")) == 0)
			return i + 1;
	}
	return 9999; /* not found */  
}

/* tmpempty():	empty the tmp array */
void tmpempty(void)
{
	int i;

	for(i = 0; i <= _MAXCHARS; i++)
		tmp[i] = 0; 
}
