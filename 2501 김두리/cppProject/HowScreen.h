#ifndef HOWSCREEN_H
#define HOWSCREEN_H

#include "Screen.h"
class HowScreen : public Screen{
public:
	void printScreen();

	static void change(int *x, int *y);

	void cursor();

};
//end[HowScreen]class -->게임방법 화면
#endif