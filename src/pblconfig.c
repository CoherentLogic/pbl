/*
 * pblconfig.c
 * reads and parses the pbl.conf file
 *
 * John Willis
 * willisj@atlantis.clogic-int.com
 *
 */

#include "pblconfig.h"
#include "glob.h"
#include <stdio.h>

cfg_install(key, value)
     char *key;
     char *value;
{
  
  HCONFIG tcfg;

  tcfg = malloc(sizeof(PCONFIGTABLE));
  tcfg->key = malloc(strlen(key));
  tcfg->value = malloc(strlen(value));

  strcpy(tcfg->key, key);
  strcpy(tcfg->value, value);

  tcfg->next = cfg;
  cfg = tcfg;
}

char *
cfg_get(key)
     char *key;
{
  HCONFIG tcfg;

  for(tcfg = cfg; tcfg != (HCONFIG) 0; tcfg = tcfg->next) {
    if(strcmp(tcfg->key, key) == 0) {
      return tcfg->value;
    }
  }
}

init_config()
{
  FILE *fp;
  char cline[1000];
  int ac;
  int lineno = 0;

  fp = fopen(PBLCONF, "r");

  if(fp == NULL) {
    fprintf(stderr, "Could not load configuration from %s\n", PBLCONF);
    exit(1);
  }

  clearargs();

  while((fgets(cline, 1000, fp)) != NULL) {
    lineno++;
    ac = parse(cline);
    if(ac != 2) {
      printf("Error in %s line %d:\n\t%s\n", PBLCONF, lineno, cline);
      exit(1);
    }    
    else {
      cfg_install(arglist[1], arglist[2]);
    }
  }

}
