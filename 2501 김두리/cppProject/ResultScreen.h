#ifndef RESULTSCREEN_H
#define RESULTSCREEN_H

#include "Screen.h"
class ResultScreen : public Screen{
public:
	void printScreen();
	void updateGameInfo();//���罺�ھ �ְ��Ϻ��� ���� ��� ������Ʈ, ���ξ�����Ʈ

	void change(int *x, int *y);
	void cursor(int y_h, int y_l);
};
#endif