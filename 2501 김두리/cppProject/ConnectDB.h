#ifndef CONNECTDB_H
#define CONNECTDB_H

#include <my_global.h> 
#include <winsock2.h> 
#include <mysql.h> 

#pragma comment(lib,"libmysql.lib")


class ConnectDB{
public:
	 MYSQL mysql;
	 MYSQL_RES *res;//���
	 MYSQL_ROW row;//��
	 int fields;//�ʵ尹��

	void Mysql();

};

#endif