/*
 * pr_mysql.c
 *
 * PBL DBI provider for MySQL
 *
 * John Willis
 * willisj@atlantis.clogic-int.com
 *
 */

#include "../../pbl_dbi.h"
#include <mysql/mysql.h>
#include <stdio.h>

#define PROVIDERNAME "PBL DBI Provider for MySQL 4"
#define PROVIDERVERSION "0.98"

MYSQL *mysql;

void 
pr_init() 
{
  mysql = NULL;

 
  if((mysql = mysql_init(mysql)) == NULL) {
    
    return;
  }

}

char *
pr_getname()
{
  return PROVIDERNAME;
}

char *
pr_getversion()
{
  return PROVIDERVERSION;
}
