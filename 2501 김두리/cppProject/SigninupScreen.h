#ifndef SIGNINUPSCREEN_H
#define SIGNINUPSCREEN_H

#include "Screen.h"
//start[SigninupScreen]class -->�α��� �Ǵ� ȸ�������� ���� ȭ��
class SigninupScreen : public Screen{
public:
	void printScreen();

	static void change(int *x, int *y);
	void cursor(int y_h, int y_l);
};
//end[SigninupScreen]class -->�α��� �Ǵ� ȸ�������� ���� ȭ��
#endif