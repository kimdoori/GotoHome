#include "MypageScreen.h"
#include "Screen.h"
#include "SetWindows.h"

using namespace std;

void MypageScreen::printScreen(){

	switch (Screen::useChar){
	case 1:
		SetWindows::gotoxy(17,17);
		printf("▼");
		break;
	case 2:
		SetWindows::gotoxy(49, 17);
		printf("▼");
		break;
	case 3:
		SetWindows::gotoxy(80, 17);
		printf("▼");
		break;

	}
	

	SetWindows::gotoxy(45, 3);
	printf("내 정보");

	SetWindows::gotoxy(77, 5);
	printf("내 최고 기록 : %d", Screen::userScore);


	SetWindows::gotoxy(80, 7);
	printf("보유 코인 : %d", Screen::userCoin);

	int y_h = 28;

	SetWindows::gotoxy(45, 14);
	printf("보유 캐릭터");
	
	if (Screen::userChar1 == 'y'){
		SetWindows::setColor(15, 0);
		SetWindows::gotoxy(17, 19);
		printf("■");
		
		SetWindows::gotoxy(11, 22);
		SetWindows::setColor(15, 0);
		printf("푹신푹신 새하양");
		SetWindows::gotoxy(6, 25);
		SetWindows::setColor(8, 0);
		printf("선택하려면 1을 눌러주세요.");

	}

	SetWindows::setColor(15, 0);
	if (Screen::userChar2 == 'y'){
		SetWindows::setColor(11, 0);
		SetWindows::gotoxy(49, 19);
		printf("▦");
		
		SetWindows::gotoxy(43, 22);
		SetWindows::setColor(11, 0);
		printf("몽실몽실 구름");
		SetWindows::gotoxy(38, 25);
		SetWindows::setColor(8, 0);
		printf("선택하려면 2를 눌러주세요.");

	}
	if (Screen::userChar3 == 'y'){
		SetWindows::setColor(13, 0);
		SetWindows::gotoxy(80, 19);
		printf("♥");

		SetWindows::gotoxy(75, 22);
		SetWindows::setColor(13, 0);
		printf("핑크핑크 하트");
		SetWindows::gotoxy(70, 25);
		SetWindows::setColor(8, 0);
		printf("선택하려면 3을 눌러주세요.");

	}
	SetWindows::setColor(15, 0);

	SetWindows::gotoxy(85, 28);
	printf("게임 시작");
	SetWindows::gotoxy(85, 30);
	printf("상점으로");


	SetWindows::gotoxy(85, 32);
	printf("시작화면으로");
	cursor(y_h, 32);

}
void MypageScreen::change(char key,int *x, int *y){
	if (key == 13){
		switch (*y){
		case 28://game 화면으로
			Screen::screen = "game";
			break;

		case 30://상점화면으로
			Screen::screen = "store";
			break;
		case 32://start화면으로
			Screen::screen = "start";
			break;
		}
	}
}
void MypageScreen::cursor(int y_h, int y_l){
	char key;
	int x = 80, y = 28;
	do{
		SetWindows::gotoxy(x, y);
		printf(">");
		key = _getch();
		SetWindows::gotoxy(x, y);
		printf(" ");

		chooseChar(key);

		Screen::move_arrow_key(key, &x, &y, y_h, y_l);
	} while (key != 13 && key != 49 && key != 50 && key != 51);//엔터치면 빠져나오기
	change(key,&x, &y);
}
void MypageScreen::chooseChar(char key){
	switch (key){
	case 49:
		if (Screen::userChar1 == 'y'){
			PlaySound(TEXT("2501source/selectChar.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
			Screen::useChar = 1;
		}
		break;
	case 50:
		if (Screen::userChar2 == 'y'){
			PlaySound(TEXT("2501source/selectChar.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
			Screen::useChar = 2;
		}

		break;
	case 51:
		if (Screen::userChar3 == 'y'){
			PlaySound(TEXT("2501source/selectChar.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
			Screen::useChar = 3;
		}

		break;

	}

}