/*
 * pblconfig.h
 * definitions for pblconfig.c
 *
 * John Willis
 * willisj@atlantis.clogic-int.com
 *
 */

#ifndef __PBL_CONFIG
#define __PBL_CONFIG

#define PBLCONF "/etc/pbl/pbl.conf"

typedef struct PCONFIGTABLE {
  char *key;
  char *value;

  struct PCONFIGTABLE *next;
} PCONFIGTABLE;

typedef PCONFIGTABLE * HCONFIG;


static HCONFIG cfg;

extern init_config();
extern char *cfg_get(key);
extern cfg_install(key, value);

#endif
