/* @(#) parse.c 1.4@(#) 01/03/04
 * PBL Interpreter
 *
 *  parse.c
 *  parse routines for the pbl interpreter        
 *
 * John Willis
 *  willisj@atlantis.clogic-int.com
 *
 * 1/31/1999 3:41 PM	corrected some typecast warnings
 *
 * 1/31/1999 12:01 AM   we are now recognizing string literals!!!
 *
 * 1/30/1999 11:45 PM	attempting to recognize string literals
 *
 * 1/30/1999 12:23 AM   beautified the revision history
 *
 * 1/29/1999 11:11 PM 	added isdelimiter() and recognition
 *		      	for parens and the unbalanced parens error
 *			along with adding commas as delimiters
 *
 * 1/29/1999 7:25 PM 	got parse() to recognize spaces
 * 		     	as delimiters and to return the proper 
 *			number of args
 *
 * 1/29/1999 2:35 PM 	initial work
 */

#include <string.h>
#include "glob.h"
#include "parse.h"

int preceding = 0;

int parse(input)
     char input[_MAXCHARS];
{
  int count, i, j;
  int numargs = 0;
  int ilength;
  int arglen = -1;

  int litfoundflag = _FALSE;

  int inparen = _FALSE;
  int litstart = 0;
  char litchar = (char) "";
	
  char	tmp[_MAXCHARS];
	
  /*printf("call to parse with maxchars of %i\n",_MAXCHARS);*/
  ilength = strlen(input);
	
  for(count = 0; count <= ilength; count++) 
    {
      /* check for parens */
      if(input[count] == '(')
	{
	  preceding = numargs;
	  inparen = _TRUE;
	}
		
      if(input[count] == ')')
	inparen = _FALSE;
		
      /* check for non string-literals */
      if(input[count] != '\"')
	{
	  /* check for arguments */
	  if(isdelimiter((char)input[count]) != _TRUE)
	    {
	      ++arglen;
	      tmp[arglen] = input[count];
	    }
	  else
	    {
	      numargs++;
			
	      for(j = 0; j <= arglen; j++)
		arglist[numargs][j] = tmp[j];	
				
	      for(j = 0; j <= _MAXCHARS; j++)
		tmp[j] = (char) "";
				
	      arglen = -1;
	    }
	}
      else	/* a string literal has been found */
	{	
	  count++; /* skip the first quote */
	  j = -1;			

	  /* go until closing quote found */
	  for(litstart = count; litstart <= ilength; litstart++) 
	    {
	      j++; /* the length of the literal */

	      litchar = input[litstart];
				
	      if(litchar == '\"')
		{
		  numargs++;

		  /* copy the param into the array */
		  for(i = 0; i < j; i++)
		    arglist[numargs][i] = tmp[i];

		  /* empty tmp array */			
		  for(i = 0; i <= _MAXCHARS; i++)
		    tmp[i] = (char) "";

		  count += j; /* might need to add 1 */
		  litfoundflag = _TRUE;
		}
	      else
		{
		  /* keep copying */
		  if(litfoundflag == _FALSE)
		    tmp[j] = litchar;
		}
	      if(litfoundflag == _TRUE)
		break;
	    }
	
	}
    }	
  if(inparen == _TRUE) {
    /*perror(2, 0);*/
    exit(2);
  }
  else
    return numargs;
} 

int isdelimiter(itin)
     char itin;
{
  switch(itin)
    {
    case ';':
      break;
    case ' ':
      break;
    case '=':
      break;
    case ',':
      break;
    case '(':
      break;
    case ')':
      break;
    default:
      return _FALSE;
    }
  return _TRUE;
}	
