#include <stdio.h>
#include "glob.h"
#include "io.h"

SYMTAB *filehandle_create(name, fp)
     char *name;
     FILE *fp;
{
  SYMTAB *stmp;

  stmp = symadd(name, SYMTYPE_FILE, 0.0, NULL, fp);
  return stmp;
}

SYMTAB *filehandle_get(name)
     char *name;
{
  return symlook(name);
}

int
open_file(filename, mode)
     char *filename;
     char *mode;
{
  FILE *fp;
  fp = fopen(filename, mode);

  if(fp != NULL) {
    filehandle_create(filename, fp);
    return 1;
  }
  else {
    return 0;
  }
}

close_file(filehandle)
     char *filehandle;
{
  SYMTAB *ftmp;

  ftmp = filehandle_get(filehandle);
  fclose(ftmp->varvals.fp);
} 

int
pbl_fgets(filehandle, t, max)
     char *filehandle;
     char *t;
     int max;
{
  SYMTAB *ftmp;

  ftmp = filehandle_get(filehandle);
  
  if ((ftmp->varvals.fp) != NULL) {
    fgets(t, max, ftmp->varvals.fp);
    return t;
  }
  else {
    return NULL;
  }
}

int
pbl_fputs(s, filehandle)
     char *s;
     char *filehandle;
{
  SYMTAB *ftmp;
  ftmp = filehandle_get(filehandle);

  if((ftmp->varvals.fp) != NULL) {
    fputs(s, ftmp->varvals.fp);
  }
}



