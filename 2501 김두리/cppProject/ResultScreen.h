#ifndef RESULTSCREEN_H
#define RESULTSCREEN_H

#include "Screen.h"
class ResultScreen : public Screen{
public:
	void printScreen();
	void updateGameInfo();//현재스코어가 최고기록보다 많을 경우 없데이트, 코인업데이트

	void change(int *x, int *y);
	void cursor(int y_h, int y_l);
};
#endif