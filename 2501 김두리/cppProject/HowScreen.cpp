#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>

#include "HowScreen.h"
#include "SetWindows.h"
#include "Screen.h"

using namespace std;

void HowScreen :: printScreen(){
	string frame = "2501source/howtoplay.txt";
	ifstream in(frame);
	string s;
	if (in.is_open()) {
		int line = 5;
		while (!in.eof()) {
			SetWindows::setColor(15, 0);
			getline(in, s);
			SetWindows::gotoxy(25, line += 2);
			if (line == 9 || line == 14 || line == 19 || line == 21 || line ==23 || line ==25) SetWindows::setColor(7, 0);
			if (line == 27 || line==29) SetWindows::setColor(12, 0);
			if (line == 9 || line == 14) line++;
			cout << s << endl;
		}
		SetWindows::gotoxy(49, 19);
		SetWindows::setColor(14, 0);
		printf("��");
		SetWindows::gotoxy(35, 31);
		printf("��   2��");

		SetWindows::gotoxy(25, 31);
		SetWindows::setColor(2, 0);
		printf("��   4��");

		SetWindows::gotoxy(45, 31);
		SetWindows::setColor(12, 0);
		printf("��   2��");
		SetWindows::setColor(15, 0);

	}
	else {
		cout << "������ ã�� �� �����ϴ�!" << endl;
	}
	SetWindows::setColor(15, 0);

	SetWindows::gotoxy(85, 33);
	printf("����ȭ������");
	cursor();
}
void HowScreen :: change(int *x, int *y){
	switch (*y){
	case 33://startȭ������
		Screen::screen = "start";
		break;
	}
}
void HowScreen :: cursor(){
	char key;
	int x = 80, y = 33;
	do{
		SetWindows::gotoxy(x, y);
		printf(">");
		key = _getch();
	} while (key != 13);//����ġ�� ����������
	change(&x, &y);
}