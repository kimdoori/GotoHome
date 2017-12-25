#include<iostream>
#include <string>
#include "ResultScreen.h"
#include "Screen.h"
#include "GameScreen.h"

#include "SetWindows.h"
#include "ConnectDB.h"

using namespace std;

void ResultScreen :: printScreen(){
	updateGameInfo();

	SetWindows::gotoxy(45, 18);
	printf("�̹� �� ���� : %d", GameScreen::gameScore);
	SetWindows::gotoxy(45, 20);
	printf("�� �ְ� ���� : %d", Screen::userScore);

	SetWindows::gotoxy(45, 24);
	printf("ȹ���� ���� : %d", GameScreen::gameCoin);
	SetWindows::gotoxy(45, 26);
	printf("�� ���� ���� : %d", Screen::userCoin);

	SetWindows::gotoxy(85, 28);
	printf("���� �ٽ� ����");
	SetWindows::gotoxy(85, 30);
	printf("�� ���� ����");
	SetWindows::gotoxy(85, 32);
	printf("����ȭ������");
	cursor(28, 32);

}
void ResultScreen :: updateGameInfo(){//���罺�ھ �ְ��Ϻ��� ���� ��� ������Ʈ, ���ξ�����Ʈ
	ConnectDB connectDB;
	connectDB.Mysql();

	string query = "";

	if (Screen::userScore < GameScreen::gameScore){//update �ϱ�
		query = "UPDATE userGameInfo SET score = " + to_string(GameScreen::gameScore) + " WHERE id = '" + Screen::userId + "'";
		//UPDATE ���̺�� SET �ʵ�� = "�ٲ� ��" WHERE �ʵ��= "���� ��" 
		PlaySound(TEXT("2501source/record.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);

		SetWindows::gotoxy(40, 10);
		printf("�����ؿ�! ����� ����̾��!");

		mysql_query(&connectDB.mysql, query.c_str());
	}
	else{
		srand((unsigned)time(0));
		int messageRandom=rand() % 3;
		SetWindows::gotoxy(30, 10);
		if (messageRandom == 0){
			printf("�̷��� �����Ͻǰǰ���? �ű�Ͽ� �����غ�����!! X P");
		}
		else if (messageRandom == 1){
			printf("������ �����ôٸ� ĳ���͸� �ٲ㺸�°� �����? X D");
		}
		else{
			SetWindows::gotoxy(40, 10);
			printf("�� ���� ������ ���� ��������!!");
		}
	}
	query = "UPDATE userGameInfo SET coin = " + to_string(Screen::userCoin + GameScreen::gameCoin) + " WHERE id = '" + Screen::userId + "'";
	mysql_query(&connectDB.mysql, query.c_str());

	query = "SELECT * FROM userGameInfo where id = '" + Screen::userId + "'";
	mysql_query(&connectDB.mysql, query.c_str());
	connectDB.res = mysql_store_result(&connectDB.mysql);
	if (connectDB.row = mysql_fetch_row(connectDB.res)){
		Screen::userScore = atoi(connectDB.row[1]);
		Screen::userCoin = atoi(connectDB.row[2]);
	}
	mysql_free_result(connectDB.res);
	mysql_close(&connectDB.mysql);

}

void ResultScreen :: change(int *x, int *y){
	switch (*y){
	case 28://game ȭ������
		Screen::screen = "game";
		break;
	case 30://�� ���� ȭ������
		Screen::screen = "mypage";
		break;
	case 32://startȭ������
		Screen::screen = "start";
		break;
	}
}
void ResultScreen :: cursor(int y_h, int y_l){
	char key;
	int x = 80, y = 28;
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