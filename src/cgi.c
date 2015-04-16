#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "inter.h"
#include "glob.h"

cgi_load()
{
  extern install_env(char *);
  
  install_env("SERVER_SOFTWARE");
  install_env("SERVER_NAME");
  install_env("GATEWAY_INTERFACE");
  install_env("SERVER_PROTOCOL");
  install_env("SERVER_PORT");
  install_env("REQUEST_METHOD");
  install_env("PATH_INFO");
  install_env("PATH_TRANSLATED");
  install_env("SCRIPT_NAME");
  install_env("QUERY_STRING");
  install_env("REMOTE_HOST");
  install_env("REMOTE_ADDR");
  install_env("AUTH_TYPE");
  install_env("REMOTE_USER");
  install_env("REMOTE_IDENT");
  install_env("CONTENT_TYPE");
  install_env("CONTENT_LENGTH");
  install_env("HTTP_ACCEPT");
  install_env("HTTP_USER_AGENT");
}

process_submit()
{
  int content_length;
  char c;
  char *cgi_data;
  char *cgi_var;
  char *cgi_val;
  char *tmp;

  int i=0;
  int var_p = 0;
  int val_p = 0;
 
  tmp = getenv("CONTENT_LENGTH");

  if(tmp != NULL)
    content_length=atoi(getenv("CONTENT_LENGTH"));
  else
    return;

  cgi_data = (char *)  malloc(content_length + 2);
  tmp = (char *) malloc(content_length + 2);

  gets(cgi_data);
  cgi_data[content_length] = '&';


  strvar_create("cgi_data", cgi_data);

  while(c = *cgi_data) {
    switch(c) {
    case '=': //finished getting var
      //free(cgi_var);
      val_p = 1;
      var_p = 0;
      cgi_var = (char *) malloc(strlen(tmp));
      strcpy(cgi_var, tmp);
      i = -1;
      tmp = calloc(content_length, sizeof(char));
      break;
    case '&': //finished getting value
      //free(cgi_val);
      val_p = 0;
      var_p = 1;
      cgi_val = (char *) malloc(strlen(tmp));
      strcpy(cgi_val, tmp);
      strvar_create(cgi_var, cgi_val);
      i = -1;
      tmp = calloc(content_length, sizeof(char));
      //free(tmp);
      break;
    default:  //get more chars
      //tmp = realloc(tmp, i);
      tmp[i] = c;
    } /* switch(c) */
    cgi_data++;
    i++;
  }

  if(val_p) {
    cgi_val = (char *) malloc(strlen(tmp));
    strcpy(cgi_val, tmp);
    strvar_create(cgi_var, cgi_val);
  }

}
