#include "MypageScreen.h"
#include "Screen.h"
#include "SetWindows.h"

using namespace std;

void MypageScreen::printScreen(){

	switch (Screen::useChar){
	case 1:
		SetWindows::gotoxy(17,17);
		printf("��");
		break;
	case 2:
		SetWindows::gotoxy(49, 17);
		printf("��");
		break;
	case 3:
		SetWindows::gotoxy(80, 17);
		printf("��");
		break;

	}
	

	SetWindows::gotoxy(45, 3);
	printf("�� ����");

	SetWindows::gotoxy(77, 5);
	printf("�� �ְ� ��� : %d", Screen::userScore);


	SetWindows::gotoxy(80, 7);
	printf("���� ���� : %d", Screen::userCoin);

	int y_h = 28;

	SetWindows::gotoxy(45, 14);
	printf("���� ĳ����");
	
	if (Screen::userChar1 == 'y'){
		SetWindows::setColor(15, 0);
		SetWindows::gotoxy(17, 19);
		printf("��");
		
		SetWindows::gotoxy(11, 22);
		SetWindows::setColor(15, 0);
		printf("ǫ��ǫ�� ���Ͼ�");
		SetWindows::gotoxy(6, 25);
		SetWindows::setColor(8, 0);
		printf("�����Ϸ��� 1�� �����ּ���.");

	}

	SetWindows::setColor(15, 0);
	if (Screen::userChar2 == 'y'){
		SetWindows::setColor(11, 0);
		SetWindows::gotoxy(49, 19);
		printf("��");
		
		SetWindows::gotoxy(43, 22);
		SetWindows::setColor(11, 0);
		printf("���Ǹ��� ����");
		SetWindows::gotoxy(38, 25);
		SetWindows::setColor(8, 0);
		printf("�����Ϸ��� 2�� �����ּ���.");

	}
	if (Screen::userChar3 == 'y'){
		SetWindows::setColor(13, 0);
		SetWindows::gotoxy(80, 19);
		printf("��");

		SetWindows::gotoxy(75, 22);
		SetWindows::setColor(13, 0);
		printf("��ũ��ũ ��Ʈ");
		SetWindows::gotoxy(70, 25);
		SetWindows::setColor(8, 0);
		printf("�����Ϸ��� 3�� �����ּ���.");

	}
	SetWindows::setColor(15, 0);

	SetWindows::gotoxy(85, 28);
	printf("���� ����");
	SetWindows::gotoxy(85, 30);
	printf("��������");


	SetWindows::gotoxy(85, 32);
	printf("����ȭ������");
	cursor(y_h, 32);

}
void MypageScreen::change(char key,int *x, int *y){
	if (key == 13){
		switch (*y){
		case 28://game ȭ������
			Screen::screen = "game";
			break;

		case 30://����ȭ������
			Screen::screen = "store";
			break;
		case 32://startȭ������
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
	} while (key != 13 && key != 49 && key != 50 && key != 51);//����ġ�� ����������
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