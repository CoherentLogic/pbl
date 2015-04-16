/*
 * loadcode.c
 *  loads code from a non-stdin file
 *
 * John Willis
 * willisj@atlantis.clogic-int.com
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "loadcode.h"

int
loadfile(fname)
     char *fname;
{
  FILE *fp;
  int c;

  if(!fexist(fname))
    return NULL;

  fsiz = fsize(fname);
  if(!(fbuf = malloc(fsiz)))
    return NULL;

  if(!(fp = fopen(fname, "r")))
    return NULL;

  while((c = getc(fp)) != EOF)
    *(fbuf++) = (char) c;

  fclose(fp);
  return 1;
}

int
fsize(file)
     char *file;
{
  FILE *fp;
  fp = fopen(file, "r");

  int c, ct;
  ct = 0;
  while((c = getc(fp)) != EOF)
    ct++;

  fclose(fp);

  return ct;
}

int
fexist(file)
     char *file;
{
  FILE *fp;
  fp = fopen(file, "r");
  return (fp == NULL) ? 0 : 1;
}
