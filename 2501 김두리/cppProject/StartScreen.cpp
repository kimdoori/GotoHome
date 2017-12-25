#include <fstream>
#include <iostream>
#include <string>
#include <conio.h>

#include "StartScreen.h"
#include "Screen.h"

#include "SetWindows.h"

using namespace std;

void StartScreen::printScreen(){//화면 출력

	ifstream input("2501source/gotohome.txt");

	string str;
	if (input.is_open()) {
		int line = 4;
		SetWindows::setColor(10,0);
		while (!input.eof()) {
			getline(input, str);
			SetWindows::gotoxy(10, line++);
			cout << str << endl;
		}
		SetWindows::setColor(15, 0);

	}
	else {
		cout << "파일을 찾을 수 없습니다!" << endl;
	}

	int y_l = 28;

	SetWindows::gotoxy(45, 20);
	printf("게임 시작");
	SetWindows::gotoxy(45, 22);
	printf("게임 방법");
	SetWindows::gotoxy(45, 24);
	printf("내 정보");
	SetWindows::gotoxy(45, 26);
	printf("로그 아웃");

	SetWindows::gotoxy(45, 28);
	printf("게임 종료");
	
	SetWindows::setColor(8, 0);
	SetWindows::gotoxy(30, 31);
	printf("- ↑ ↓로 이동 후 enter로 선택하세요 -");
	SetWindows::setColor(15, 0);



	cursor(20, y_l);
}

void StartScreen :: change(int *x, int *y) {//화면 전환 //screen을 전환할 스크린의 이름으로 바꾼다.
	switch (*y){
	case 20://gamestart버튼 --> signup,signin
		Screen::screen = "game";

		break;
	case 22://howtoplay
		Screen::screen = "how";
		break;
	case 24://mypage
		Screen::screen = "mypage";
		break;
	case 26:
		Screen::userId = "";
		Screen::userPassword = "";
		Screen::statusSign = false;
		Screen::statusSignup = false;
		Screen::screen = "signin";
		break;

	case 28:
		SetWindows::gotoxy(1, 35);
		exit(0);
		break;
	}
}

void StartScreen :: cursor(int y_h, int y_l){//키 입력받는 함수
	char key;
	int x = 40, y = 20;
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