#ifndef MYSCREEN_H
#define MYSCREEN_H

#include "Screen.h"

class MypageScreen : public Screen{
public:
	void printScreen();
	void change(char key,int *x, int *y);
	void cursor(int y_h, int y_l);
	void chooseChar(char key);
};
#endif