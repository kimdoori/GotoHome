#ifndef GAMESCREEN_H
#define GAMESCREEN_H
#include<time.h>

#include "Screen.h"

class GameScreen : public Screen{
public:


	int gameSpeed;
	int maxScore=0;

	string useCharprint="��";

	string maxUser="";

	int stage = 1;//��������
	int gameHeart;//����� ���� //ĳ���͸��� ����� ���� �ٸ�
	int coinPlus;//������ ���
	bool revival;//��Ȱ����

	int stageColor1;//���������� ����
	int stageColor2;


	int userColor;


	int x = 40, y = 30;


	//start[Game] -->����
	static int gameScore;
	static int gameCoin;

	struct Car{//�ڵ���(���ع�)
		int x;
		int y;
		int direction = -1;//�ڵ����� �̵����� -1:�������� 1:����������
	};
	struct GroundLine{//������
		int x = 4;
		int y;
		int color;//10�̸� �ʷ� 4�̸� ����
	};
	struct Coin{//����
		int x;
		int y;
	};
	struct Light{//��ȣ��
		int x = 83;
		int y;
		int color;
	};

	Car * car; //������ �ڵ���
	Coin * coin;//������ ����
	GroundLine line[33];//������ ������ (��)

	Light light[3];//������ ��ȣ��
	int carSize = 0;//�������� �Ҵ�� car ����
	int coinSize = 0; //�������� �Ҵ�� coin ����
	clock_t traffic;//��ȣ�� ������ ���� 

	void printScreen();
	void cursor();

	void initializeGame();//������ �ʱ�ȭ�ϴ� �Լ�
		
	//start[��ȣ��]
	void trafficLight();//��ȣ���� �ٲٴ��Լ�
	void printLight();//��ȣ����� �ٲ㼭 ���
	void checkCross();//����ڰ� �������϶��ǳʰ�����
	//end[��ȣ��]

	//start[�ڵ���]
	void printCar();//ȭ�鿡 �ڵ��� ����ϴ� �Լ�
	void checkCarHit();	//�ڵ����� �¾Ҵ���
	//end[�ڵ���]

	//start[����]
	void printCoin();//ȭ�鿡 ���� ����ϴ� �Լ�
	void checkCoinHit();//������ �Ծ�����
	//end[����]

	void move_arrow_key(char key, int *x, int *y);
	void selectMaxGameUser();

};
//end[GameScreen]class -->����ȭ��

#endif