#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include "Screen.h"
//start[StartScreen]class -->����ȭ��
class StartScreen : public Screen{
public:


	void printScreen();//ȭ�� ���
	static void change(int *x, int *y);//ȭ����ȯ
	void cursor(int y_h, int y_l);//Ű �Է¹޴� �Լ�
		
};
//end[StartScreen]class -->����ȭ��
#endif