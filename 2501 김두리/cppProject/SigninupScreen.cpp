#include <iostream>
#include <string>

#include "SigninupScreen.h"
#include "Screen.h"

#include "SetWindows.h"

using namespace std;

void SigninupScreen :: printScreen(){
	SetWindows::gotoxy(45, 18);
	printf("로그인");
	SetWindows::gotoxy(45, 20);
	printf("회원가입");
	SetWindows::gotoxy(45, 22);
	printf("시작화면으로");
	cursor(18, 22);
}

void SigninupScreen :: change(int *x, int *y){
	switch (*y){
	case 18://sign in버튼
		Screen::screen = "signin";
		break;
	case 20://signup 버튼
		Screen::screen = "signup";
		break;
	case 22:
		Screen::screen = "start";
		break;
	}
}

void SigninupScreen :: cursor(int y_h, int y_l){
	char key;
	int x = 40, y = 18;
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