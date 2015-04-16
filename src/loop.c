/* @(#) loop.c 1.4@(#) 01/03/04
 * PBL Interpreter
 *
 *  loop.c
 *  code to find loops     
 *
 * John Willis
 *  willisj@atlantis.clogic-int.com
 */
 


#include "glob.h"

 
int findstart(char name[_MAXCHARS], int lt);
int startend(char input[_MAXCHARS], int lt);

char tmp[_MAXCHARS]; 	/* global to this module */

/* findstart():	find a sentinel loop and return the line at which it begins */
int findstart(char name[_MAXCHARS], int lt)
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

		
      /* parse it */
      clearargs();
      argc = parse(tmp);
		
      /* compare name array to arg 2 */ 
      if(strcmp(arglist[2], name) == 0)
	{
	  if(strcmp(arglist[1], "start") == 0)
	    {	
	      /* found */
	      return i + 1;
	    }
			
	}
    }	
  return 0; /* not found */
}

/* startend():  find the line a which a sentinel loop ends */
int startend(char input[_MAXCHARS], int lt)
{
  int procstart = 0;
  int i = 0;
  int argc = 0;

  char tmp[_MAXCHARS];
	
  /* empty the tmp array */
  tmpempty();

  /* find the start of the procedure */
  procstart = findproc(input, lt);
	
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

      if((strcmp(arglist[1], "finish")) == 0)
	return i + 1;
		
    }
}
