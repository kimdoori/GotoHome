#ifndef GAMESCREEN_H
#define GAMESCREEN_H
#include<time.h>

#include "Screen.h"

class GameScreen : public Screen{
public:


	int gameSpeed;
	int maxScore=0;

	string useCharprint="■";

	string maxUser="";

	int stage = 1;//스테이지
	int gameHeart;//목숨의 갯수 //캐릭터마다 목숨의 갯수 다름
	int coinPlus;//코인의 배수
	bool revival;//부활여부

	int stageColor1;//스테이지별 색깔
	int stageColor2;


	int userColor;


	int x = 40, y = 30;


	//start[Game] -->게임
	static int gameScore;
	static int gameCoin;

	struct Car{//자동차(방해물)
		int x;
		int y;
		int direction = -1;//자동차의 이동방향 -1:왼쪽으로 1:오른쪽으로
	};
	struct GroundLine{//땅색깔
		int x = 4;
		int y;
		int color;//10이면 초록 4이면 갈색
	};
	struct Coin{//코인
		int x;
		int y;
	};
	struct Light{//신호등
		int x = 83;
		int y;
		int color;
	};

	Car * car; //생성될 자동차
	Coin * coin;//생성될 코인
	GroundLine line[33];//생성될 땅라인 (색)

	Light light[3];//생성될 신호등
	int carSize = 0;//랜덤으로 할당될 car 갯수
	int coinSize = 0; //랜덤으로 할당될 coin 갯수
	clock_t traffic;//신호등 구현을 위한 

	void printScreen();
	void cursor();

	void initializeGame();//게임을 초기화하는 함수
		
	//start[신호등]
	void trafficLight();//신호등을 바꾸는함수
	void printLight();//신호등색을 바꿔서 출력
	void checkCross();//사용자가 빨간불일때건너가는지
	//end[신호등]

	//start[자동차]
	void printCar();//화면에 자동차 출력하는 함수
	void checkCarHit();	//자동차와 맞았는지
	//end[자동차]

	//start[코인]
	void printCoin();//화면에 코인 출력하는 함수
	void checkCoinHit();//코인을 먹었는지
	//end[코인]

	void move_arrow_key(char key, int *x, int *y);
	void selectMaxGameUser();

};
//end[GameScreen]class -->게임화면

#endif