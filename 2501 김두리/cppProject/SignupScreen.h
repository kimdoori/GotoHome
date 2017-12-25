#ifndef SIGNUPSCREEN_H
#define SIGNUPSCREEN_H
#include <iostream>
#include <string>
#include "Screen.h"

using namespace std;
class SignupScreen : public Screen{
public:

	string id = "";//입력한 아이디
	string name = "";//입력한 이름
	string jumin = "";//입력한 주민번호
	string password = "";//입력한 비밀번호
	char key;

	void printScreen();
	void move_input_key(string input, int *x, int *y);//입력할때
	void insertUserInfo();//기존에 겹치는 아이디가 없다면 회원가입

	void change(int *x, int *y);
	void cursor(int y_h, int y_l);
};
#endif