#ifndef SIGNUPSCREEN_H
#define SIGNUPSCREEN_H
#include <iostream>
#include <string>
#include "Screen.h"

using namespace std;
class SignupScreen : public Screen{
public:

	string id = "";//�Է��� ���̵�
	string name = "";//�Է��� �̸�
	string jumin = "";//�Է��� �ֹι�ȣ
	string password = "";//�Է��� ��й�ȣ
	char key;

	void printScreen();
	void move_input_key(string input, int *x, int *y);//�Է��Ҷ�
	void insertUserInfo();//������ ��ġ�� ���̵� ���ٸ� ȸ������

	void change(int *x, int *y);
	void cursor(int y_h, int y_l);
};
#endif