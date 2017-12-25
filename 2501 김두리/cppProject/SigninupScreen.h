#ifndef SIGNINUPSCREEN_H
#define SIGNINUPSCREEN_H

#include "Screen.h"
//start[SigninupScreen]class -->로그인 또는 회원가입을 묻는 화면
class SigninupScreen : public Screen{
public:
	void printScreen();

	static void change(int *x, int *y);
	void cursor(int y_h, int y_l);
};
//end[SigninupScreen]class -->로그인 또는 회원가입을 묻는 화면
#endif