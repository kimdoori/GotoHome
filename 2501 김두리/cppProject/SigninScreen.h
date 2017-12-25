#ifndef SIGNINSCREEN_H
#define SIGNINSCREEN_H
#include <iostream>
#include <string>

using namespace std;

#include "SigninScreen.h"
#include "Screen.h"

//start[SigninScreen]class -->�α��� ȭ��
class SigninScreen : public Screen{
public:

	string id = "";//�Է��� ���̵�
	string password = "";//�Է��� �н�����
	char key;
	void printScreen();

	void move_input_key(string input, int *x, int *y);//������ �Է��Ҷ�

	void selectUserInfo();//�Է��� ���̵�� �н������ ������ ������ �ִ���

	void insertUserInfo();
	
	void change(int *x, int *y);
		
	void cursor(int y_h, int y_l);
};

#endif