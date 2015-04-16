#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "glob.h"
#include <stdio.h>

extern int nl;
int nextl;
int dirty;
int qc;

interactive()
{
  int ac;
  char curline[_MAXCHARS];
  dirty = 0;
  qc = 0; /* quit check */

  while(1) {
      printf("pbl> ");
      gets(curline);
      sprintf(curline, "%s;", curline);

      ac = parse(curline);

      if(strcmp(arglist[1], "app") == 0) 
	append_at(nextl);
      if(strcmp(arglist[1], "ins") == 0) 
	append_at(atoi(arglist[2]));
      if(strcmp(arglist[1], "lis") == 0)
	prlines(atoi(arglist[2]), atoi(arglist[3]));
      if(strcmp(arglist[1], "run") == 0)
	blockexec(atoi(arglist[2]), atoi(arglist[3]));
      if(strcmp(arglist[1], "exa") == 0)
	examine(arglist[2]);
      if(strcmp(arglist[1], "dep") == 0)
	deposit(arglist[2], arglist[3]);
      if(strcmp(arglist[1], "sav") == 0)
	savecode(arglist[2]);
      if(strcmp(arglist[1], "lod") == 0)
	loadcode(arglist[2]);
      if(strcmp(arglist[1], "ver") == 0)
	printf("Coherent Logic PBL %s\n", VERSION);
      if(strcmp(arglist[1], "qui") == 0) {
	if(!qc && dirty) {
	  printf("?\n");
	  qc=1;
	}
	else {
	  exit(0);
	}
      }

      strcpy(curline, "");
      strcpy(arglist[1], "");
      clearargs();
  }
}

append_at(tgt)
     int tgt;
{
  int ln = tgt;
  while(1) {
    printf("%d:\t", ln);
    gets(lines[ln]);
    if(strcmp(lines[ln], ".") == 0) {
      strcpy(lines[ln], "");
      break;
    }
    else {
      ln++;
    }
  }
  nextl=ln;
  nl=ln;
  dirty=1;
}

prlines(s, e)
     int s;
     int e;
{
  int i;
  for(i = s; i <= e; i++)
    printf("%d:\t%s\n", i, lines[i]);
}

examine(s)
     char *s;
{
  SYMTAB *symret;
  symret = (SYMTAB *) symlook(s);
  printf("%s:\t%s\n", s, symret->varvals.strval);
}

deposit(v, s)
     char *v;
     char *s;
{
  strvar_create(v, s);
  return;
}

loadcode(s)
     char *s;
{
  int cl=0;
  FILE *fp;
  char *c;
  
  fp = fopen(s,"r");
  if(fp == NULL) {
    printf("Cannot open %s for reading\n", s);
    return;
  }
  while((c = fgets(lines[cl++], _MAXCHARS, fp)) != NULL)
    ;
  fclose(fp);
  nl = cl;
  nextl = cl;

}
       

savecode(s)
     char *s;
{
  int i;
  FILE *fp;
  fp=fopen(s, "w");
  if(fp == NULL) {
    printf("Cannot open %s\n", s);
    return;
  }
  for(i=0;i<=nl;i++) {
    fprintf(fp,"%s\n", lines[i]);
  }
  fclose(fp);
  //printf("Wrote %d lines\n", nl);
  dirty=0;
}
  
