/*
 * pbl_dbi.c
 *
 *  Database connectivity routines
 *
 * John Willis
 * willisj@atlantis.clogic-int.com
 *
 */

#include <errno.h>
#include <dlfcn.h>
#include "glob.h"
#include "pbl_dbi.h"
#include "log.h"
#include "parse.h"

//***
// provider_inst(lib)
//  lib must be an absolute path to the library which is being loaded
DBPROVIDER *
provider_inst(lib)
     char *lib;
{
  DBPROVIDER *pDBP;
  void *libptr;

  pDBP = (DBPROVIDER *) malloc(sizeof(DBPROVIDER));

  if(pDBP == (DBPROVIDER *) NULL) {
    if(errno == ENOMEM)
     logprint("Could not allocate memory for database provider.\n");

    return (DBPROVIDER *) NULL;
  }

  if(libptr = dlopen(lib, RTLD_LAZY)) {
    pDBP->pr_init = dlsym(libptr, "pr_init");
    pDBP->pr_getname = dlsym(libptr, "pr_getname");
    pDBP->pr_getversion = dlsym(libptr, "pr_getversion");

    pDBP->name = (*(pDBP->pr_getname))();
    pDBP->version = (*(pDBP->pr_getversion))();
    (*(pDBP->pr_init))();
    logprint("dbi:  loaded provider from %s\n\tProvider name:\t\t%s\n\tProvider version:\t%s\n", lib, (*(pDBP->pr_getname))(), (*(pDBP->pr_getversion))());

  }
  else {
    logprint("Could not open PBL DBI provider %s\n", lib);
    free(pDBP);

    return (DBPROVIDER *) NULL;
  }

  pDBP->next = providers;
  providers = pDBP;

  return (DBPROVIDER *) pDBP;
}

DBPROVIDER *
load_provider(provider_name)
     char *provider_name;
{
  FILE *fp;
  char cur_line[_MAXCHARS];
  int argcount;


  fp = fopen(PROVIDERS, "r");
  if (!fp) {
    fprintf(stderr, "Cannot read providers file %s\n", PROVIDERS);
    return (DBPROVIDER *) NULL;
  }

  clearargs();

  while((fgets(cur_line, _MAXCHARS, fp)) != EOF) {
    argcount = parse(cur_line);

    if(strcmp(arglist[1], "Provider") == 0) {
      if(strcmp(arglist[2], provider_name) == 0) {
	return provider_inst(arglist[3]);
      }
    }
  }
  logprint("The requested provider '%s' is not listed in %s\n", provider_name, PROVIDERS);
  return 0;
}


