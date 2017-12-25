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
		printf("이미 가입한 아이디입니다.");
	}
	SetWindows::gotoxy(40, 10);
	printf("ID : ");
	SetWindows::gotoxy(40, 12);
	printf("이름 : ");
	SetWindows::gotoxy(40, 14);
	printf("주민번호 앞자리 : ");
	SetWindows::gotoxy(40, 16);
	printf("Password : ");
	SetWindows::gotoxy(80, 30);
	printf("회원가입");
	SetWindows::gotoxy(80, 32);
	printf("시작화면으로");
	cursor(30, 32);*/
}
void SignupScreen :: move_input_key(string input, int *x, int *y){//입력할때
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
void SignupScreen :: insertUserInfo(){//기존에 겹치는 아이디가 없다면 회원가입

	ConnectDB connectDB;
	connectDB.Mysql();

	string query = "SELECT * FROM userInfo where id = '";
	query.append(id);
	query.append("'");

	mysql_query(&connectDB.mysql, query.c_str());
	connectDB.res = mysql_store_result(&connectDB.mysql);
	if (mysql_fetch_row(connectDB.res) == NULL){//중복 아이디가 없을 경우 입력한 정보 insert
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
	//		printf("가입이 성공적으로 처리되었습니다.");
	//		SetWindows::gotoxy(80, 30);
	//		printf("로그인 하기");
	//		SetWindows::gotoxy(80, 32);
	//		printf("시작화면으로");
	//		Screen::statusSignup = true;
	//		cursor(30, 32);
	//	}
	//	else{
	//		Screen::againSign = true;
	//	}
	//	if (Screen::statusSignup){//로그인화면으로
	//		Screen::againSign = false;
	//		Screen::statusSignup = false;
	//		Screen::screen = "signin";
	//	}
	//	break;
	//case 32://start 화면
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

		} while (key != 9);//탭치면 빠져나오기
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
	} while (key != 13);//엔터치면 빠져나오기
	change(&x, &y);
}