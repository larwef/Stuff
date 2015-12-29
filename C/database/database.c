#include <stdio.h>
#include <mysql/mysql.h>

int main(void){
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *server = "your.server";
	char *user = "your.username";
	char *password = "your.password";
	char *database = "your.database";
	conn = mysql_init(NULL);
	/* Connect to database */
	if(!mysql_real_connect(conn, server,
		user, password, database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		return 1;
	}
	/* send SQL query */
	if (mysql_query(conn, "show tables")) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		return 1;
	}
	res = mysql_use_result(conn);
	/* output table name */
	printf("MySQL Tables in mysql database:\n");
	while ((row = mysql_fetch_row(res)) != NULL){
		printf("%s \n", row[0]);
	}

	printf("\n");

	if (mysql_query(conn, "insert into Bruker (brukerNavn, passord) values('test', 'test')")) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		return 1;
	}

	printf("\n");

	if (mysql_query(conn, "select * from Bruker")) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		return 1;
	}
	res = mysql_use_result(conn);
	while ((row = mysql_fetch_row(res)) != NULL){
		printf("%s %s %s \n", row[0], row[1], row[2]);
	}

	/* close connection */
	mysql_free_result(res);
	mysql_close(conn);

	return 0;
}