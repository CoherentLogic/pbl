/*
 * log.c
 * pbl logging routines
 *
 * John Willis
 * willisj@atlantis.clogic-int.com
 *
 */

#include <stdarg.h>
#include <stdio.h>
#include <time.h>

#include "pblconfig.h"

void
logprint(char *fmt,...)
{
  time_t result;
  FILE *logptr;
  va_list ap;
  char *p, *sval, *ts;

  int ival;
  double dval;

  result = time(NULL);
  logptr = fopen(cfg_get("logfile"), "a");
  
  if(logptr == NULL) {
    fprintf(stderr, "Could not open log file %s for writing\n", cfg_get("logfile"));
    return;
  }  

  ts = malloc(255);
  strftime(ts, 255, "%Y%m%d %H:%M.%S", localtime(&result));

  fprintf(logptr, "%s: ", ts); 
  va_start(ap, fmt);
  for(p = fmt; *p; p++) {
    if (*p != '%') {
      fputc(*p, logptr);
      continue;
    }
    switch(*++p) {
    case 'd':
      ival = va_arg(ap, int);
      fprintf(logptr, "%d", ival);
      break;
    case 'f':
      dval = va_arg(ap, double);
      fprintf(logptr, "%f", dval);
      break;
    case 's':
      for(sval = va_arg(ap, char*); *sval; sval++)
	fputc(*sval, logptr);
      break;
    default:
      fputc(*p, logptr);
      break;
    }
  }
  va_end(ap);

  fclose(logptr);
}
