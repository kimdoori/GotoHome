#include <string.h>
#include <iostream>
#include <conio.h>

#include "ConnectDB.h"

#ifndef SCREEN_H
#define SCREEN_H

using namespace std;

class Screen{
public:

	static bool failPurchase;
	static bool prePurchase;

	static int useChar;

	static string screen;//����� ��ũ�� �̸�
	static bool statusSign; //�α����� ����
	static bool againSignin; // �ٽ� �α��� ��û�� ����
	static bool againSignup; // �ٽ� �α��� ��û�� ����
	static bool againInput; // �ٽ� �α��� ��û�� ����


	static bool statusSignup;//ȸ�������� ����

	//�α����ϸ� ������ ����
	static string userId; // ���� ���̵�
	static string userPassword; //���� ��й�ȣ
	static int userCoin; //���� ����
	static int userScore; //���� ����
	static char userChar1; //���� ĳ����1 ����
	static char userChar2; //���� ĳ����2 ����
	static char userChar3; //���� ĳ����3 ����


	void print();//screen�� ����� ��ũ���� �̸��� ���� �ش� ȭ�� ���
		
	static void printFrame();//ȭ���� �������� ����ϴ� �Լ�
		


	static void move_arrow_key(char key, int *x, int *y, int y_h, int y_l);//�Էµ� Ű���� ���� ���� ��ǥ ����

};


#endif