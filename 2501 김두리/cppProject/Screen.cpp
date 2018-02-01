#include <my_global.h> 
#include <winsock2.h> 
#include <iostream>
#include <conio.h>
#include <string.h>
#include <fstream>

#include <mmsystem.h>    
#pragma comment(lib,"winmm.lib") 

#include "Screen.h"
#include "StartScreen.h"
#include "SigninScreen.h"
#include "HowScreen.h"
#include "MypageScreen.h"
#include "StoreScreen.h"
#include "GameScreen.h"
#include "ResultScreen.h"

#include "ConnectDB.h"
#include "SetWindows.h"


using namespace std;


string Screen::screen = "start";
int Screen::useChar = 1;

bool Screen::failPurchase = false;
bool Screen::prePurchase = false;
bool Screen::statusSign = false;
bool Screen::againSignin = false;
bool Screen::againSignup = false;
bool Screen::againInput = false;

bool Screen::missChoice = false;
bool Screen::statusSignup = false;
string Screen::userId = ""; // ���� ���̵�
string Screen::userPassword = ""; //���� ��й�ȣ
int Screen::userCoin = 0; //���� ����
int Screen::userScore = 0; //���� ����
char Screen::userChar1='y'; //���� ĳ����1 ����
char Screen::userChar2='n'; //���� ĳ����2 ����
char Screen::userChar3 = 'n'; //���� ĳ����3 ����



void Screen :: print(){//screen�� ����� ��ũ���� �̸��� ���� �ش� ȭ�� ���


	while (1){
		system("cls");
		system("color 0F");

		if (screen != "signin"){
			system("mode  con lines=37   cols=106 ");
			printFrame();
		}
		if (screen == "start"){//startȭ���̸�
			SetWindows::setCursor(false);
			StartScreen startScreen;
			startScreen.printScreen();
		}
		else if (screen == "signin"){
			system("mode  con lines=20   cols=40 ");
			SetWindows::gotoxy(28, 19);
			SetWindows::setColor(7, 0);
			printf("2501 ��θ�");
			SetWindows::setColor(15, 0);
			SigninScreen signinScreen;
			signinScreen.printScreen();

		}
		else if (screen == "how"){
			HowScreen howScreen;
			howScreen.printScreen();
		}
		else if (screen == "mypage"){

			MypageScreen mypageScreen;
			mypageScreen.printScreen();
		}
		else if (screen == "store"){
			StoreScreen storeScreen;
			storeScreen.printScreen();
		}
		else if (screen == "game"){
			GameScreen gameScreen;
			gameScreen.printScreen();
		}
		else if (screen == "result"){
			ResultScreen resultScreen;
			resultScreen.printScreen();
		}
		system("cls");
	}
}
void Screen :: printFrame(){//ȭ���� �������� ����ϴ� �Լ�

	string frame = "2501source/frame.txt";
	

	ifstream in(frame);

	string s;
	if (in.is_open()) {
		int line = 1;
		while (!in.eof()) {
			getline(in, s);
			SetWindows::gotoxy(2, line++);
			cout << s << endl;
		}
	}
	else {
		cout << "������ ã�� �� �����ϴ�!" << endl;
	}
}
void Screen :: move_arrow_key(char key, int *x, int *y, int y_h, int y_l){//�Էµ� Ű���� ���� ���� ��ǥ ����
	switch (key){
	case 72://��
		*y = *y - 2;
		if (*y<y_h) *y = y_l;
		break;
	case 80://�Ʒ�
		*y = *y + 2;
		if (*y>y_l) *y = y_h;
		break;
	default:
		return;
	}
}