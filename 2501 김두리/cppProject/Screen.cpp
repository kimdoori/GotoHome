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
string Screen::userId = ""; // 유저 아이디
string Screen::userPassword = ""; //유저 비밀번호
int Screen::userCoin = 0; //유저 코인
int Screen::userScore = 0; //유저 점수
char Screen::userChar1='y'; //유저 캐릭터1 여부
char Screen::userChar2='n'; //유저 캐릭터2 여부
char Screen::userChar3 = 'n'; //유저 캐릭터3 여부



void Screen :: print(){//screen에 저장된 스크린의 이름에 따라 해당 화면 출력


	while (1){
		system("cls");
		system("color 0F");

		if (screen != "signin"){
			system("mode  con lines=37   cols=106 ");
			printFrame();
		}
		if (screen == "start"){//start화면이면
			SetWindows::setCursor(false);
			StartScreen startScreen;
			startScreen.printScreen();
		}
		else if (screen == "signin"){
			system("mode  con lines=20   cols=40 ");
			SetWindows::gotoxy(28, 19);
			SetWindows::setColor(7, 0);
			printf("2501 김두리");
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
void Screen :: printFrame(){//화면의 프레임을 출력하는 함수

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
		cout << "파일을 찾을 수 없습니다!" << endl;
	}
}
void Screen :: move_arrow_key(char key, int *x, int *y, int y_h, int y_l){//입력된 키보드 값에 따라 좌표 변경
	switch (key){
	case 72://위
		*y = *y - 2;
		if (*y<y_h) *y = y_l;
		break;
	case 80://아래
		*y = *y + 2;
		if (*y>y_l) *y = y_h;
		break;
	default:
		return;
	}
}