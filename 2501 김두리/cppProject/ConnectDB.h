#ifndef CONNECTDB_H
#define CONNECTDB_H

#include <my_global.h> 
#include <winsock2.h> 
#include <mysql.h> 

#pragma comment(lib,"libmysql.lib")


class ConnectDB{
public:
	 MYSQL mysql;
	 MYSQL_RES *res;//결과
	 MYSQL_ROW row;//행
	 int fields;//필드갯수

	void Mysql();

};

#endif