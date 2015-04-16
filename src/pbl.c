/* @(#) pbl.c 1.4@(#) 01/03/04
   
    pbl.c
    the actual interpreter     
  
    Copyright 1999, 2004 John Willis
    
    This file is part of pbl.
 
    pbl is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    pbl is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with pbl; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */  
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h> 
#include <signal.h>
#include <stdlib.h>   
#include <unistd.h>
  
#pragma warning(disable : 4047 4024 4013 4101 4035 4113)

#include "glob.h"
#include "cgi.h"
#include "parse.h"
#include "support.h"
#include "pbl_dbi.h"
#include "pblconfig.h"

typedef enum {
  err_none = 0,
  err_nomain,
  err_noend
} errors;

typedef enum {
  /* MISCELLANEOUS */
  toknone = 0,	        /* no token */
  tokgoto,		/* goto */
  tokdoproc,		/* doproc */
  tokendproc,		/* endproc */
  tokendprog,		/* endprog */
  tokpsc,		/* psc */
  toksvar,		/* $strvar */
  toknvar,		/* %numvar */
  toksasgn,             /* define string */
  toknasgn,             /* define number */

  /* DECISION CONSTRUCTS */
  tokif,		/* if */
  tokelse,		/* else */
  tokelif,		/* elif */
  tokchoose,		/* choose */
  tokthis,		/* this */
  tokotherwise,		/* otherwise */

  /* LOOP CONSTRUCTS */
  tokstart,		/* start */
  tokfinish,		/* finish */
  tokloop,		/* loop */

  /* INPUT/OUTPUT */
  tokprint,		/* print */
  tokreadcon,		/* readcon */

  /* OPERATORS */
  tokplus,		/* addition (+) */		
  tokminus,		/* subtraction (-) */
  tokmult,		/* multiplication (*) */
  tokdiv,	        /* division (/) */
  tokmod,		/* modulus (%) */
  tokexp	        /* exponentiation (^) */
} tokens;


errors lasterr;
tokens nexttoken;       

int nl=0;
int cl=0;

int main(argc, argv)   
     int argc;
     char *argv[];
{  

  int i;    
  int c;
  int iMode = 0;
  int cgi = 0;

  int mainstart = 0;		/* start of main() */
  int mainend = 0;		/* end of main() */
  char *progname = argv[0];
  int ec;

  init_config();

  if (argc > 1) {
    if (strcmp(argv[1], "-i") == 0) {
      iMode=1;
    }
    if (strcmp(argv[1], "-cgi") == 0) {
      cgi=1;
      cgi_load();
      process_submit();
    }
  }
  
  if(iMode) {
    printf ("Coherent Logic PBL %s\n", VERSION);
    printf ("Copyright 1999, 2004 Coherent Logic Development.\n\n");
    printf ("PBL is free software, covered by the GNU General Public License.\n");
    printf ("Please see the file COPYING, included with this distribution,\n");
    printf ("for the conditions of this license.\n\n");

    interactive();
  }
  else {
    if (argc == 2) {
      loadcode(argv[1]);
    }
    else if (argc == 1) {
      nl = readlines();
    }
    else {
      loadcode(argv[2]);
      printf("Content-type: text/html\n\n");
    }
  }

  blockexec(0, nl);
	
  return 0;
}

/* readlines()  get source code from standard input and copy it
   into the lines[] array */
int readlines()
{
  char tmp[_MAXCHARS];

  int nextchar;
  int lcount, llen;
  int i, j;
	
  i = 0;
  j = 0;
  lcount = -1;
  llen = -1;

  clearlines();

  for(i = 0; i <= _CHARSAD; i++)
    tmp[i] = 0;

  while((nextchar = getchar()) != EOF) {
    llen++;

    if(nextchar == '\n') {
      if(lcount >= (_MAXCHARS - 1)) {   /* make sure line buffer isn't full */
	printf("Code buffer overflow\n");
	return lcount;
      }
      else {
	lcount++;
      }
      strcpy(lines[lcount], tmp); 

      for(i = 0; i <= _CHARSAD; i++)
	tmp[i] = 0;
       llen = -1;
    }
    else {
      tmp[llen] = nextchar;
    }
  }

  return lcount;
} /* readlines() */

/* blockexec():	execute block of code from l. first to l. last */
int blockexec(first, last)
     int first;
     int last;
{
	
  int ps, pe;				/* proc. start/end */
  int i, j;				/* loop counters */
  int argcount;			/* argument count */
  char curline[_MAXCHARS];	/* current line */
  char tmp[_MAXCHARS];
  char vtmp[_MAXCHARS];
  SYMTAB *cret;
	
  for(i = 0; i <= _CHARSAD; i++)
    vtmp[i] = 0;	

  for(i = 0; i <= _CHARSAD; i++)
    curline[i] = 0;

  for(i = 0; i <= _CHARSAD; i++)
    tmp[i] = 0;

  for(cl = first; cl <= last; cl++)
    {
      for(i = 0; i <= _CHARSAD; i++)
	curline[i] = 0;		

      strcpy(curline, lines[cl]);
      clearargs();
      argcount = parse(curline);
      tokenize();
      expandargs();

      switch(nexttoken) {
      case toksasgn:
	strvar_create(arglist[2], arglist[3]);
	break;
      case toknasgn:
	//numvar_create(arglist[2], atof(arglist[3]));
	break;

      case tokstart:
	strcpy(tmp, arglist[2]);
				
	ps = findstart(tmp, nl);
	pe = startend(tmp, nl);
				
		
	for(i = atoi(arglist[3]); i <= atoi(arglist[4]); i++)
	  blockexec(ps, pe);
			
	break;
      case tokdoproc:
	strcpy(tmp, arglist[2]);

	ps = findproc(tmp, nl);
	pe = procend(tmp, nl);
	push(cl);
	blockexec(ps, pe);
	
	break;
      case tokendproc:
	cl = pop();

	break;
      case tokgoto:
	cl = atoi(arglist[2]);
	break;
      default:
	push(argcount);
	dostatement();
	break;
      }
    }
} /* blockexec() */

/* dostatement():	implements each PBL language statement */
dostatement()
{
  int i = 0;
  int arg_count = 0;

  arg_count = pop();

  switch(nexttoken) {
  case tokprint:
    for(i = 2; i <= arg_count; i++)
      printf("%s ", arglist[i]);

    printf("\n");

    break;
  case tokendprog:
    raise(SIGINT);
    break; 
  }			
}

tokenize()
{

  if(arglist[1][0] == '$')
    nexttoken = toksvar;

  if(arglist[1][1] == '%')
    nexttoken = toknvar;

  if(strcmp(arglist[1], "String") == 0)
    nexttoken = toksasgn;

  if(strcmp(arglist[1], "Number") == 0)
    nexttoken = toknasgn;

  if(strcmp(arglist[1], "print") == 0)
    nexttoken = tokprint;

  if(strcmp(arglist[1], "doproc") == 0)
    nexttoken = tokdoproc;
	
  if(strcmp(arglist[1], "endproc") == 0)
    nexttoken = tokendproc;

  if(strcmp(arglist[1], "endprog") == 0)
    nexttoken = tokendprog;

  if(strcmp(arglist[1], "psc") == 0)
    nexttoken = tokpsc;
	
  if(strcmp(arglist[1], "goto") == 0)
    nexttoken = tokgoto;

  if(strcmp(arglist[1], "start") == 0)
    nexttoken = tokstart;
} /* tokenize() */	

expandargs()
{
  int		i;
  char	*tmp;
  SYMTAB 	*symret;
  int j;

  tmp = malloc(_MAXCHARS);

  for(i = 0; i <= _CHARSAD; i++)
    tmp[i] = 0;

  for(i = 2; i <= _ARGSAD; i++) {
    if(arglist[i][0] == '$') {

      for(j=1;j<strlen(arglist[i]);j++)
	tmp[j-1]=arglist[i][j];

      symret = (SYMTAB *) symlook(tmp);

      if(symret)
	strcpy(arglist[i], symret->varvals.strval);
      else
	printf("%s undefined\n", arglist[i]);
    }
  }
			
}
