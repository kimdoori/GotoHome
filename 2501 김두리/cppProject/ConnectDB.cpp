#include "ConnectDB.h"

using namespace std;


void ConnectDB::Mysql(){//mysql�� �����ϴ� �Լ�
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "euckr");
	mysql_options(&mysql, MYSQL_INIT_COMMAND, "SET NAMES euckr");
	if (!mysql_real_connect(&mysql, "13.115.231.53", "root", "0228", "gotoHome", 3306, NULL, 0)){
	}
	else {

	}
}
