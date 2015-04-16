#include <stdio.h>
#include <mysql/mysql.h>


main()
{
  printf("MySQL Client %s\n", mysql_get_client_info());
}
