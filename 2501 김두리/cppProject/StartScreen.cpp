#include <fstream>
#include <iostream>
#include <string>
#include <conio.h>

#include "StartScreen.h"
#include "Screen.h"

#include "SetWindows.h"

using namespace std;

void StartScreen::printScreen(){//ȭ�� ���

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
		cout << "������ ã�� �� �����ϴ�!" << endl;
	}

	int y_l = 28;

	SetWindows::gotoxy(45, 20);
	if (Screen::userId == ""){
		printf("�α��� ");
		SetWindows::setColor(8, 0);
	}
	else{
		printf("���� ����");

	}
	
	SetWindows::gotoxy(45, 24);
	printf("�� ����");
	SetWindows::gotoxy(45, 26);
	printf("�α� �ƿ�");
	SetWindows::setColor(15, 0);
	SetWindows::gotoxy(45, 22);
	printf("���� ���");

	SetWindows::gotoxy(45, 28);
	printf("���� ����");
	
	SetWindows::setColor(8, 0);
	SetWindows::gotoxy(30, 31);
	printf("- �� ��� �̵� �� enter�� �����ϼ��� -");
	if (Screen::missChoice){
		SetWindows::gotoxy(37, 33);
		printf("- �α��� �� �̿����ּ��� -");
		Screen::missChoice = false;
	}
	SetWindows::setColor(15, 0);



	cursor(20, y_l);
}

void StartScreen :: change(int *x, int *y) {//ȭ�� ��ȯ //screen�� ��ȯ�� ��ũ���� �̸����� �ٲ۴�.
	switch (*y){
	case 20://gamestart��ư --> signup,signin
		if (Screen::userId == ""){
			Screen::screen = "signin";
		}
		else{
			Screen::screen = "game";
		}
		break;
	case 22://howtoplay
		Screen::screen = "how";
		break;
	case 24://mypage
		if (Screen::statusSign)
			Screen::screen = "mypage";
		else
			Screen::missChoice=true;
		break;
	case 26:
		if (Screen::statusSign){
			Screen::userId = "";
			Screen::userPassword = "";
			Screen::statusSign = false;
			Screen::statusSignup = false;
		}
		else
			Screen::missChoice=true;
		break;

	case 28:
		SetWindows::gotoxy(1, 35);
		exit(0);
		break;
	}
}

void StartScreen :: cursor(int y_h, int y_l){//Ű �Է¹޴� �Լ�
	char key;
	int x = 40, y = 20;
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

