#include <iostream>
#include <conio.h>


#include "GameScreen.h"
#include "Screen.h"
#include "SetWindows.h"

#include <tchar.h>
#include<windows.h>


using namespace std;

int GameScreen::gameScore = 0;
int GameScreen::gameCoin = 0;

void GameScreen::printScreen(){	//게임화면그리기

	selectMaxGameUser();//최고의 플레이어

	gameSpeed = 50;
	gameScore = 0;
	gameCoin = 0;
	stage = 1;

	switch (Screen::useChar){//사용자가 플레이하는 캐릭터에 따라 초기값 설정
	case 1:
		gameHeart = 3;
		coinPlus = 1;
		revival = false;
		userColor = 15;
		useCharprint = "■";
		break;
	case 2:
		gameHeart = 5;
		coinPlus = 2;
		revival = false;
		userColor = 11;
		useCharprint = "▦";
		break;
	case 3:
		gameHeart = 5;
		coinPlus = 1;
		revival = true;
		userColor = 13;
		useCharprint = "♥";
		break;
	}

	cursor();
}

void GameScreen::cursor(){//사용자가 입력하는 키값을 인식 & 게임 플레이
	int stageCount = 0;
	char key;
	SetWindows::gotoxy(x, y);
	SetWindows::setColor(userColor, 0);
	printf("%s", useCharprint.c_str());
	while (true){
		while (gameHeart > 0){
			initializeGame();//게임 초기화
			traffic = clock();
			do{
				int turnSecond = 4;
				if (light[0].color == 0 && light[1].color == 0){//빨간불이면
					turnSecond = 3;
				}
				else if (light[0].color == 0 && light[2].color == 0){//노랑불이면
					turnSecond = 2;
				}
				float trafficEnd = (float)(clock() - traffic) / CLOCKS_PER_SEC;
				if ((int)trafficEnd / turnSecond == 1){//4초마다 신호등이 바뀜
					trafficLight();//신호등 색을 바꾸는 함수
					traffic = clock();
				}
				checkCross();//신호등이 빨간불일 때 건너고 있는지
				if (_kbhit()){//사용자가 입력한 게 있을 경우
					key = _getch();
					SetWindows::setColor(line[x - 2].color, line[y - 2].color);//사용자가 있었던 색깔로
					SetWindows::gotoxy(x, y);
					printf(" ");
					move_arrow_key(key, &x, &y);
					SetWindows::setColor(userColor, line[y - 2].color); //-->사용자가 건너갈색깔로
					SetWindows::gotoxy(x, y);
					printf("%s", useCharprint.c_str());
					SetWindows::setColor(15, 0);
				}
				else{
					Sleep(gameSpeed);// 게임 속도 조절
					printCar();// 화면에 자동차 출력
					printCoin();// 화면에 코인 출력
					SetWindows::setColor(userColor, line[y - 2].color);
					SetWindows::gotoxy(x, y);
					printf("%s", useCharprint.c_str());
					SetWindows::setColor(15, 0);
				}
				// 자동차를 맞았는지 확인
				checkCarHit();
				// 코인을 먹었는지 확인
				checkCoinHit();
			} while (gameHeart > 0 && y != 2);//목숨이 다 없어지거나 화면 끝에 도달하면
			stageCount++;
			if (stageCount % 5 == 0 && gameHeart>0){
				stage++;
				system("cls");
				SetWindows::gotoxy(50, 10);
				gameSpeed -= 10;
				printf("스테이지 %d", stage);
				SetWindows::gotoxy(43, 28);
				printf("속도가 좀 더 빨라집니다.");
				SetWindows::gotoxy(42, 30);
				printf("더 조심해서 길을 건너세요!");
				Sleep(1500);
			}
			delete[] car;
			delete[] coin;
		}
		if (revival){
			system("cls");
			SetWindows::gotoxy(42, 15);
			printf("잠시 후 부활합니다.");
			SetWindows::gotoxy(37, 17);
			printf("더 높은 신기록을 향해 도전 !");

			Sleep(1500);
			gameHeart = 5;
			revival = false;
		}
		else break;

	}

	PlaySound(TEXT("2501source/gameDie.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
	
	//게임이 끝나면 결과창으로
	Screen::screen = "result";
}

void GameScreen::initializeGame(){//게임을 초기화하는 함수
	SetWindows::gotoxy(83, 5);
	SetWindows::setColor(2, 15);
	printf("■");
	SetWindows::gotoxy(83, 6);
	SetWindows::setColor(0, 15);
	printf("■");
	SetWindows::gotoxy(83, 7);
	SetWindows::setColor(0, 15);
	printf("■");

	SetWindows::setColor(15, 0);

	SetWindows::gotoxy(84, 10);
	printf("최고의 플레이어");
	SetWindows::gotoxy(82, 11);
	printf("--------------------");
	SetWindows::setColor(6, 0);

	SetWindows::gotoxy(82, 12);
	printf("최고점수 : %d 점", maxScore);
	SetWindows::gotoxy(82, 14);
	printf("유저 : %s ", maxUser.c_str());
	SetWindows::gotoxy(82, 15);
	SetWindows::setColor(15, 0);

	printf("--------------------");

	SetWindows::gotoxy(82, 18);
	printf("내 최고점수 : %d 점", Screen::userScore);
	SetWindows::gotoxy(82, 20);
	printf("현재 점수 : %d 점", gameScore);
	SetWindows::gotoxy(82, 25);
	printf("획득 코인 : %d 개", gameCoin);
	SetWindows::gotoxy(82, 30);
	printf("남은 목숨 : %d 개", gameHeart);

	carSize = 0;
	y = 34; //유저의 위치 다시 처음처럼
	srand((unsigned)time(0));
	//신호등 초기화
	light[0].y = 5;
	light[0].color = 2;
	light[1].y = 6;
	light[1].color = 0;
	light[2].y = 7;
	light[2].color = 0;
	//line 초기화
	line[0].y = 2;
	line[0].color = 10;

	int colorRandom;

	int loadCount = 0;
	for (int i = 1; i < 32; i++){
		line[i].y = i + 2;
		colorRandom = (rand() % 2); //0이나 1
		
		if (colorRandom==1){//1이면
			line[i].color = 4;
			loadCount++;
		}
		else{
			line[i].color = 10;
			loadCount = 0;
		}
		if (loadCount>=6){//도로가 6개 이상이면 초록색으로
			line[i].color = 10;
			loadCount = 0;
		}

	}
	line[32].color = 10;
	line[32].y = 34;

	//line 출력
	for (int i = 0; i < 33; i++){
		if (line[i].color == 4){
			carSize++;
		}
		SetWindows::setColor(line[i].color, line[i].color);
		SetWindows::gotoxy(line[i].x, line[i].y);
		printf("%76c", " ");
	}
	SetWindows::setColor(7, 0);
	//car 초기화
	int directionRandom;
	car = new Car[carSize];
	int carIndex = 0;
	for (int i = 0; i < 33; i++){
		if (carIndex >= carSize)
			break;
		if (line[i].color == 4){
			car[carIndex].x = ((rand() % 34) + 4) * 2;
			car[carIndex].y = line[i].y;
			directionRandom = (rand() % 2); //0이나 1
			if (directionRandom)//1이면
				car[carIndex].direction = 1;
			carIndex++;
		}
	}
	//coin 초기화
	coinSize = (rand() % 5) + 5;
	coin = new Coin[coinSize];
	for (int i = 0; i < coinSize; i++){
		coin[i].x = ((rand() % 34) + 4) * 2;
		coin[i].y = (rand() % 33) + 2;
	}
}

//start[신호등]
void GameScreen::trafficLight(){//신호등을 바꾸는함수
	if (light[0].color == 2){//초록불일경우
		light[0].color = 0;
		light[1].color = 14;
		light[2].color = 0;
	}
	else if (light[2].color == 12){//빨간불일경우
		light[0].color = 2;
		light[1].color = 0;
		light[2].color = 0;
	}
	else if (light[1].color == 14){//노랑불일경우
		light[0].color = 0;
		light[1].color = 0;
		light[2].color = 12;
	}
	printLight();//화면에 신호등색 바꿔서 출력
}
void GameScreen::printLight(){//신호등색을 바꿔서 출력
	SetWindows::gotoxy(light[0].x, light[0].y);
	SetWindows::setColor(light[0].color, 15);
	printf("■");
	SetWindows::gotoxy(light[1].x, light[1].y);
	SetWindows::setColor(light[1].color, 15);
	printf("■");
	SetWindows::gotoxy(light[2].x, light[2].y);
	SetWindows::setColor(light[2].color, 15);
	printf("■");
	SetWindows::setColor(15, 0);
}
void GameScreen::checkCross(){//사용자가 빨간불일때건너가는지
	if (light[2].color == 12 && line[y - 2].color == 4){//빨간불
		SetWindows::setColor(12, line[y - 2].color);
		SetWindows::gotoxy(x, y);
		printf("%s", useCharprint.c_str());
		SetWindows::setColor(15, 0);
		gameHeart--;
		SetWindows::gotoxy(82, 30);
		printf("남은 목숨 : %d 개", gameHeart);
	}
}
void GameScreen::printCar(){//화면에 자동차 출력하는 함수
	int count = 0;
	//자동차를 x값 증가 또는 x값 감소
	//끝에 다다르면 방향바꾸기 direnction 에 -1곱한다.
	for (count = 0; count < carSize; count++){
		if (car[count].x < 8){//만약 왼쪽끝에 닿으면 방향바꾸기
			car[count].direction *= -1;
		}
		else if (car[count].x > 74){//만약 오른쪽끝에 닿으면 방향바꾸기
			car[count].direction *= -1;
		}
		// 기존 위치의 자동차를 삭제한다.
		
		SetWindows::setColor(15, 4);
		SetWindows::gotoxy(car[count].x, car[count].y);
		printf("  ");
		car[count].x = car[count].x + 2 * car[count].direction;
		// 새로운 위치에 자동차를 출력한다.
		SetWindows::gotoxy(car[count].x, car[count].y);
		if (car[count].direction == -1)
			printf("◁");
		else{
			printf("▷");
		}
		SetWindows::setColor(15, 0);
	}
}
void GameScreen::checkCarHit(){	//자동차와 맞았는지
	int count = 0;
	for (count = 0; count < carSize; count++){// 현재 자동차의 수만큼 반복
		if (car[count].x == x){// 사용자와 같은 열인지 확인
			if (car[count].y == y){// 같은 행인지 확인
				PlaySound(TEXT("2501source/carHit.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);

				SetWindows::setColor(12, line[y - 2].color);
				SetWindows::gotoxy(x, y);
				printf("%s", useCharprint.c_str());
				SetWindows::setColor(15, 0);
				gameHeart--;
				SetWindows::gotoxy(82, 30);
				printf("남은 목숨 : %d 개", gameHeart);
			}
		}
	}
}void GameScreen::printCoin(){//화면에 코인 출력하는 함수
	int count = 0;
	for (count = 0; count < coinSize; count++){
		if (coin[count].x == 82 && coin[count].y == 21){//만약 코인을 먹어 코인이 위치가 닿지않는 곳으로 옮겨졌다면
			SetWindows::setColor(0, 0);
			printf("");
		}
		else{
			SetWindows::setColor(14, line[coin[count].y - 2].color);
			SetWindows::gotoxy(coin[count].x, coin[count].y);
			// 코인을 출력한다.
			printf("●");
		}
		SetWindows::setColor(15, 0);
	}
}
void GameScreen::checkCoinHit(){//코인을 먹었는지
	int count = 0;
	for (count = 0; count < coinSize; count++){// 현재 코인의 수만큼 반복
		if (coin[count].x == x){// 사용자와 같은 열인지 확인
			if (coin[count].y == y){// 같은 행인지 확인
				PlaySound(TEXT("2501source/COIN.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
				SetWindows::setColor(8, line[y - 2].color);
				SetWindows::gotoxy(x, y);
				printf("%s", useCharprint.c_str());
				SetWindows::setColor(15, 0);
				gameCoin += 1 * coinPlus;
				SetWindows::gotoxy(82, 25);
				printf("획득 코인 : %d 개", gameCoin);
				coin[count].x = 82;//코인을 먹으면 코인의 위치를 닿지 않는 곳으로 
				coin[count].y = 21;//코인을 먹으면 코인의 위치를 닿지 않는 곳으로 
			}
		}
	}

}
void GameScreen::move_arrow_key(char key, int *x, int *y){
	switch (key){
	case 72://위
		*y = *y - 1;
		gameScore += 10;
		SetWindows::gotoxy(82, 20);
		SetWindows::setColor(15, 0);
		printf("현재 점수 : %d 점", gameScore);
		if (*y<2) *y = 2;
		break;
	case 75://왼쪽
		*x = *x - 2;
		if (*x<8) *x = 8;
		break;
	case 77://오른쪽
		*x = *x + 2;
		if (*x>74) *x = 74;
		break;
	case 80://아래
		*y = *y + 1;
		if (*y>34) *y = 34;
		break;
	default:
		return;
	}
}
void GameScreen::selectMaxGameUser(){
	ConnectDB connectDB;
	connectDB.Mysql();
	string query = "SELECT id,score FROM userGameInfo group by score having max(score)";
	mysql_query(&connectDB.mysql, query.c_str()); // 쿼리를 보낸다.
	connectDB.res = mysql_store_result(&connectDB.mysql);  // 모든 출력 결과를 서버에서 한번에 다 받아옴
	if (connectDB.row = mysql_fetch_row(connectDB.res)){//결과의 첫번째 행
		maxUser = connectDB.row[0];
		maxScore = atoi(connectDB.row[1]);
	}

	mysql_free_result(connectDB.res);
	mysql_close(&connectDB.mysql);

}