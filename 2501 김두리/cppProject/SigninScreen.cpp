#include <my_global.h> 
#include <winsock2.h> 
#include <mysql.h> 
#include<iostream>
#include <string>
#include <conio.h>

#include "SigninScreen.h"
#include "Screen.h"

#include "SetWindows.h"
#include "ConnectDB.h"

#pragma comment(lib,"libmysql.lib")


using namespace std; 

void SigninScreen :: printScreen(){
	Screen::useChar = 1;
	SetWindows::gotoxy(6, 14);

	printf("                                 ");
	if (Screen::againSignin){
		SetWindows::gotoxy(6, 17);
		SetWindows::setColor(1, 0);
		printf("-�߸��� ������ �Է��ϼ̽��ϴ�-");
		SetWindows::setColor(15, 0);
		Screen::againSignin = false;
	}
	else if (Screen::againSignup){
		SetWindows::gotoxy(6, 17);
		SetWindows::setColor(1, 0);
		printf("-�̹� �����ϴ� ���̵��Դϴ�-");
		SetWindows::setColor(15,0 );
		Screen::againSignup = false;
	}
	else if (Screen::statusSignup){
		SetWindows::gotoxy(6, 17);
		SetWindows::setColor(1, 0);
		printf("-ȸ�������� �Ϸ�Ǿ����ϴ�-");
		SetWindows::setColor(15,0);
		Screen::statusSignup = false;
	}
	else if (Screen::againInput){
		SetWindows::gotoxy(6, 17);
		SetWindows::setColor(1, 0);
		printf("-1~10�ڸ��� �Է����ּ���. -");
		SetWindows::setColor(15, 0);
		Screen::againInput = false;

	}
	SetWindows::gotoxy(14, 5);
	printf("ID : ");
	SetWindows::gotoxy(8, 7);
	printf("Password : ");

	SetWindows::gotoxy(1,1);
	SetWindows::setColor(14,0);
	printf("  ������ �Է��ϰ� enter�� �����ּ��� ");
	SetWindows::gotoxy(6, 3);
	printf("  �޴��� ��� ����Ű�� �̵�  ");

	SetWindows::setColor(15, 0);
	SetWindows::gotoxy(26, 10);
	printf("�α����ϱ�");
	SetWindows::gotoxy(24, 12);
	printf("ȸ�������ϱ�");
	SetWindows::gotoxy(28, 14);
	printf("�����ϱ�");
	cursor(10, 14);
}

void SigninScreen :: move_input_key(string input, int *x, int *y){//������ �Է��Ҷ�
	switch (*y)
	{
	case 5:
		id = input;
		break;
	case 7:
		password = input;
		break;
	default:
		break;
	}
	*y = *y + 2;
	if (*y > 7) key = 9;
}
void SigninScreen :: selectUserInfo(){//�Է��� ���̵�� �н������ ������ ������ �ִ���
	SetWindows::gotoxy(0, 0);
	ConnectDB connectDB;
	connectDB.Mysql();
	string query = "SELECT * FROM userInfo where id = '";
	query.append(id);
	query.append("' and pw = '");
	query.append(password);
	query.append("'");

	mysql_query(&connectDB.mysql, query.c_str()); // ������ ������.
	connectDB.res = mysql_store_result(&connectDB.mysql);  // ��� ��� ����� �������� �ѹ��� �� �޾ƿ�
	if (connectDB.row = mysql_fetch_row(connectDB.res)){//����� ù��° ��
		Screen::userId = connectDB.row[0];
		Screen::userPassword = connectDB.row[1];
	}
	
	if (Screen::userId == ""){//���̵� ���� ���
		Screen::againSignin = true;
		return;
	}
	query = "SELECT * FROM userGameInfo where id = '";
	query.append(Screen::userId);
	query.append("'");
	mysql_query(&connectDB.mysql, query.c_str()); // userGameInfo�� ���̺� ������ ������.
	connectDB.res = mysql_store_result(&connectDB.mysql);
	if (connectDB.row = mysql_fetch_row(connectDB.res)){
		Screen::userScore = atoi(connectDB.row[1]);
		Screen::userCoin = atoi(connectDB.row[2]);
		Screen::userChar1 = *connectDB.row[3];
		Screen::userChar2 = *connectDB.row[4];
		Screen::userChar3 = *connectDB.row[5];
	}
	mysql_free_result(connectDB.res);
	mysql_close(&connectDB.mysql);

}
void SigninScreen::insertUserInfo(){//������ ��ġ�� ���̵� ���ٸ� ȸ������

	ConnectDB connectDB;
	connectDB.Mysql();

	string query = "SELECT * FROM userInfo where id = '";
	query.append(id);
	query.append("'");

	mysql_query(&connectDB.mysql, query.c_str());
	connectDB.res = mysql_store_result(&connectDB.mysql);
	if (mysql_fetch_row(connectDB.res) == NULL){//�ߺ� ���̵� ���� ��� �Է��� ���� insert
		query = "INSERT INTO userInfo values('" + id + "','" + password + "')";
		mysql_query(&connectDB.mysql, query.c_str());
		Screen::userId = id;
		Screen::userPassword = password;
		Screen::statusSignup = true;

		query = "INSERT INTO userGameInfo(id) values('" + id + "')";
		mysql_query(&connectDB.mysql, query.c_str());
		
	}
	else{
		//ȸ������ ���н� 
		Screen::againSignup = true;
	}
	
	mysql_free_result(connectDB.res);
	mysql_close(&connectDB.mysql);
}

void SigninScreen :: change(int *x, int *y){
	if (id.length() > 10 || password.length() > 10){
		againInput = true;
	}else{
		switch (*y){
		case 10://�α���
			selectUserInfo();
			if (Screen::againSignin){
				Screen::screen = "signin";
			}
			else{
				Screen::againSignin = false;
				Screen::againSignup = false;
				Screen::statusSign = true;
				Screen::statusSignup = false;
				Screen::screen = "start";

			}

			break;
		case 12://ȸ�������ϱ�
			insertUserInfo();
			break;
		case 14://�����ϱ�
			SetWindows::gotoxy(6, 16);
			exit(0);
			break;
		}
	}
}
void SigninScreen :: cursor(int y_h, int y_l){
	string input;
	int x, y;
	if (!Screen::statusSign){
		x = 20, y = 5;
		SetWindows::setCursor(true);
		do{
			SetWindows::gotoxy(x, y);

			cin >> input;
			move_input_key(input, &x, &y);

		} while (key != 9);//��ġ�� ����������
	}
	SetWindows::setCursor(false);
	x = 20, y = 10;
	do{
		SetWindows::gotoxy(x, y);
		printf(">");
		key = _getch();
		SetWindows::gotoxy(x, y);
		printf(" ");
		Screen::move_arrow_key(key, &x, &y, y_h, y_l);
	} while (key != 13 && key!=27);//����ġ�� ����������
	if (key == 27)
		exit(0);
	change(&x, &y);
}