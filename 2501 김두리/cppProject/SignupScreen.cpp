#include <iostream>
#include <string>

#include "SignupScreen.h"

#include "Screen.h"

#include "SetWindows.h"
#include "ConnectDB.h"

using namespace std;

void SignupScreen :: printScreen(){
	/*if (Screen::againSign){
		SetWindows::gotoxy(40, 32);
		printf("�̹� ������ ���̵��Դϴ�.");
	}
	SetWindows::gotoxy(40, 10);
	printf("ID : ");
	SetWindows::gotoxy(40, 12);
	printf("�̸� : ");
	SetWindows::gotoxy(40, 14);
	printf("�ֹι�ȣ ���ڸ� : ");
	SetWindows::gotoxy(40, 16);
	printf("Password : ");
	SetWindows::gotoxy(80, 30);
	printf("ȸ������");
	SetWindows::gotoxy(80, 32);
	printf("����ȭ������");
	cursor(30, 32);*/
}
void SignupScreen :: move_input_key(string input, int *x, int *y){//�Է��Ҷ�
	//y+2
	switch (*y)
	{
	case 10:
		id = input;
		break;
	case 12:
		name = input;
		break;
	case 14:
		jumin = input;
		break;
	case 16:
		password = input;
		break;
	default:
		break;
	}
	*y = *y + 2;
	if (*y > 16) key = 9;
}
void SignupScreen :: insertUserInfo(){//������ ��ġ�� ���̵� ���ٸ� ȸ������

	ConnectDB connectDB;
	connectDB.Mysql();

	string query = "SELECT * FROM userInfo where id = '";
	query.append(id);
	query.append("'");

	mysql_query(&connectDB.mysql, query.c_str());
	connectDB.res = mysql_store_result(&connectDB.mysql);
	if (mysql_fetch_row(connectDB.res) == NULL){//�ߺ� ���̵� ���� ��� �Է��� ���� insert
		query = "INSERT INTO userInfo values('" + id + "','" + name + "','" + jumin + "','" + password + "')";
		mysql_query(&connectDB.mysql, query.c_str());
		Screen::userId = id;
		Screen::userName = name;
		Screen::userJumin = jumin;
		Screen::userPassword = password;
	}
	query = "INSERT INTO userGameInfo(id) values('" + id + "')";
	mysql_query(&connectDB.mysql, query.c_str());
	mysql_free_result(connectDB.res);
	mysql_close(&connectDB.mysql);

}

void SignupScreen :: change(int *x, int *y){
	//switch (*y){
	//case 30://login
	//	insertUserInfo();
	//	if (Screen::userId != "" && !Screen::statusSignup){
	//		SetWindows::gotoxy(40, 32);
	//		printf("������ ���������� ó���Ǿ����ϴ�.");
	//		SetWindows::gotoxy(80, 30);
	//		printf("�α��� �ϱ�");
	//		SetWindows::gotoxy(80, 32);
	//		printf("����ȭ������");
	//		Screen::statusSignup = true;
	//		cursor(30, 32);
	//	}
	//	else{
	//		Screen::againSign = true;
	//	}
	//	if (Screen::statusSignup){//�α���ȭ������
	//		Screen::againSign = false;
	//		Screen::statusSignup = false;
	//		Screen::screen = "signin";
	//	}
	//	break;
	//case 32://start ȭ��
	//	Screen::againSign = false;
	//	Screen::statusSignup = false;
	//	Screen::screen = "start";

	//	break;

	//}
}

void SignupScreen :: cursor(int y_h, int y_l){
	string input;
	int x, y;
	if (Screen::userId == ""){
		x = 60, y = 10;
		SetWindows::setCursor(true);
		do{
			SetWindows::gotoxy(x, y);
			cin >> input;
			move_input_key(input, &x, &y);

		} while (key != 9);//��ġ�� ����������
	}
	SetWindows::setCursor(false);

	x = 75, y = 30;
	do{
		SetWindows::gotoxy(x, y);
		printf(">");
		key = _getch();
		SetWindows::gotoxy(x, y);
		printf(" ");
		Screen::move_arrow_key(key, &x, &y, y_h, y_l);
	} while (key != 13);//����ġ�� ����������
	change(&x, &y);
}