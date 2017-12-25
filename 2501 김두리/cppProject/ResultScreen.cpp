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
	printf("이번 판 점수 : %d", GameScreen::gameScore);
	SetWindows::gotoxy(45, 20);
	printf("내 최고 점수 : %d", Screen::userScore);

	SetWindows::gotoxy(45, 24);
	printf("획득한 코인 : %d", GameScreen::gameCoin);
	SetWindows::gotoxy(45, 26);
	printf("총 보유 코인 : %d", Screen::userCoin);

	SetWindows::gotoxy(85, 28);
	printf("게임 다시 시작");
	SetWindows::gotoxy(85, 30);
	printf("내 정보 보기");
	SetWindows::gotoxy(85, 32);
	printf("시작화면으로");
	cursor(28, 32);

}
void ResultScreen :: updateGameInfo(){//현재스코어가 최고기록보다 많을 경우 없데이트, 코인업데이트
	ConnectDB connectDB;
	connectDB.Mysql();

	string query = "";

	if (Screen::userScore < GameScreen::gameScore){//update 하기
		query = "UPDATE userGameInfo SET score = " + to_string(GameScreen::gameScore) + " WHERE id = '" + Screen::userId + "'";
		//UPDATE 테이블명 SET 필드명 = "바꿀 값" WHERE 필드명= "조건 값" 
		PlaySound(TEXT("2501source/record.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);

		SetWindows::gotoxy(40, 10);
		printf("축하해요! 기록을 세우셨어요!");

		mysql_query(&connectDB.mysql, query.c_str());
	}
	else{
		srand((unsigned)time(0));
		int messageRandom=rand() % 3;
		SetWindows::gotoxy(30, 10);
		if (messageRandom == 0){
			printf("이렇게 포기하실건가요? 신기록에 도전해보세요!! X P");
		}
		else if (messageRandom == 1){
			printf("게임이 어려우시다면 캐릭터를 바꿔보는건 어떠세요? X D");
		}
		else{
			SetWindows::gotoxy(40, 10);
			printf("더 높은 점수를 위해 힘내세요!!");
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
	case 28://game 화면으로
		Screen::screen = "game";
		break;
	case 30://내 정보 화면으로
		Screen::screen = "mypage";
		break;
	case 32://start화면으로
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
	} while (key != 13);//엔터치면 빠져나오기
	change(&x, &y);
}