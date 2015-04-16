mysql4: mysql4.so.1

mysql4.so.1: pr_mysql.o 
	gcc -shared pr_mysql.o -o mysql4.so.1 -I/opt/sfw/mysql/include -L/opt/sfw/mysql/lib/mysql -lmysqlclient

pr_mysql.o: pr_mysql.c
	gcc -fPIC -c pr_mysql.c