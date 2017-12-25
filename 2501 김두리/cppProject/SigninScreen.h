#ifndef SIGNINSCREEN_H
#define SIGNINSCREEN_H
#include <iostream>
#include <string>

using namespace std;

#include "SigninScreen.h"
#include "Screen.h"

//start[SigninScreen]class -->로그인 화면
class SigninScreen : public Screen{
public:

	string id = "";//입력한 아이디
	string password = "";//입력한 패스워드
	char key;
	void printScreen();

	void move_input_key(string input, int *x, int *y);//내용을 입력할때

	void selectUserInfo();//입력한 아이디와 패스워드로 가입한 정보가 있는지

	void insertUserInfo();
	
	void change(int *x, int *y);
		
	void cursor(int y_h, int y_l);
};

#endif