/* @(#) glob.h 1.4@(#) 01/03/04
 * PBL Interpreter
 *
 *  glob.h
 *  global defs
 *
 * John Willis
 * jwillis@zianet.com
 *
 * 1/31/1999 7:48 PM	moved lines array from pbl.c
 *
 * 1/30/1999 12:25 AM	beautified the revision history
 *
 * 1/29/1999 2:43 PM 	initial work
 *
 */

#include <stdio.h>

#ifndef __PBL_GLOB
#define __PBL_GLOB
                 
/* limitations */
#define MAXARGS			20
#define _MAXCHARS		255
#define _CHARSAD		254     
#define _ARGSAD			19
#define _STACKS			255

/* booleans */
#define _TRUE			1
#define _FALSE			0

/* errors */
#define ERROR_UNBAL_PARENS	100
#define EXIT_STACK_OVERFLOW	2
#define EMPTY_STACK_POP		3

/* global variables */
char 	lines[_MAXCHARS][_MAXCHARS];
char 	arglist[MAXARGS][_MAXCHARS];

/* THE SYMBOL TABLE */
typedef struct SYMTAB
{
  char	*symname;			/* the symbol name */
  short	symtype;

  union
  {
    double numval; /* number vars */
    char *strval; /* string vars */
    FILE *fp; /* file handle */

  } varvals;
  struct SYMTAB	*stlink;
} SYMTAB;

/* this creates an instance of linked list SYMTAB */
static SYMTAB *lsym;

/* symbol types */
#define	SYMTYPE_STRING	1
#define	SYMTYPE_NUMBER	2
#define SYMTYPE_FILE 3

int stack[_STACKS];		/* the stack itself */ 
int stackindex;

//int verbose = 0;
#endif
