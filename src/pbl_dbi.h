/*
 * pbl_dbi.h
 *
 *  Structure defs for pbl's database interface
 *
 * John Willis
 *  willisj@atlantis.clogic-int.com
 *
 */
 

#define PROVIDERS "/etc/pbl/dbi/providers"

typedef struct DBPROVIDER {
  char *name;
  char *version;

  void (*pr_init)(void);
  char *(*pr_getname)(void);
  char *(*pr_getversion)(void);

  struct DBPROVIDER *next;
} DBPROVIDER;

static DBPROVIDER *providers;

extern DBPROVIDER *provider_inst(char *lib);
extern DBPROVIDER *load_provider(provider_name);





