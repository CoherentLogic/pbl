/* @(#) symtab.c 1.3@(#) 01/03/04
 * PBL Interpreter
 *
 *  symtab.c
 *  implementation of the symbol table
 *
 * John Willis
 *  willisj@atlantis.clogic-int.com
 *
 */

#include <stdlib.h>



#include "glob.h"


SYMTAB *symlook(char *);
SYMTAB *symadd(char *, int, double, char *, FILE *);

/* symlook():	returns a symtab entry matching *sname */
SYMTAB *symlook(char *sname)
{
  SYMTAB *pST;

  for(pST = lsym; pST != (SYMTAB *) 0; pST = pST->stlink)
    {
      if(strcmp(pST->symname, sname) == 0)
	{
	  return pST;
	}
    }

  return 0;
} /* symlook() */

/* symadd():	adds a symbol to the front of the symtab */
SYMTAB *symadd(char *sname, int stype, double dval, char *sval, FILE *fp)
{
  
  SYMTAB *pST;

  pST = (SYMTAB *)malloc(sizeof(SYMTAB));
  pST->symname = malloc(strlen(sname) + 1);

  strcpy(pST->symname, sname);

  switch(stype)
    {
    case SYMTYPE_STRING:
      pST->symtype = SYMTYPE_STRING;
      pST->varvals.strval = malloc(strlen(sval) + 1);
      strcpy(pST->varvals.strval, sval);

      break;
    case SYMTYPE_NUMBER:
      pST->symtype = SYMTYPE_NUMBER;
      pST->varvals.numval = dval;

      break;
    case SYMTYPE_FILE:
      pST->symtype = SYMTYPE_FILE;
      pST->varvals.fp = fp;

      break;
    default:
      /* invalid stype */
      printf("internal error\n");

      exit(2);
    }
  pST->stlink = lsym;
  lsym = pST;

  return pST;
	
}

strvar_create(name, val)
     char *name;
     char *val;
{
  symadd(name, SYMTYPE_STRING, 0, val, 0);
}


numvar_create(name, val)
     char *name;
     float val;
{
  return;
}

install_env(name)
     char *name;
{
  char *ev;
  ev = getenv(name);

  if(ev!=NULL)
    strvar_create(name, ev);
}
