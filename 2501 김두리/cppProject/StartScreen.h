#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include "Screen.h"
//start[StartScreen]class -->시작화면
class StartScreen : public Screen{
public:


	void printScreen();//화면 출력
	static void change(int *x, int *y);//화면전환
	void cursor(int y_h, int y_l);//키 입력받는 함수
		
};
//end[StartScreen]class -->시작화면
#endif