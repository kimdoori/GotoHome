#include <string.h>
#include <iostream>
#include <conio.h>

#include "ConnectDB.h"

#ifndef SCREEN_H
#define SCREEN_H

using namespace std;

class Screen{
public:

	static bool failPurchase;
	static bool prePurchase;

	static int useChar;

	static string screen;//출력할 스크린 이름
	static bool statusSign; //로그인한 상태
	static bool againSignin; // 다시 로그인 요청된 상태
	static bool againSignup; // 다시 로그인 요청된 상태
	static bool againInput; // 다시 로그인 요청된 상태
	
	static bool missChoice; // 로그인이 필요한 메뉴를 눌렀을 경우

	static bool statusSignup;//회원가입한 상태

	//로그인하면 생성될 정보
	static string userId; // 유저 아이디
	static string userPassword; //유저 비밀번호
	static int userCoin; //유저 코인
	static int userScore; //유저 점수
	static char userChar1; //유저 캐릭터1 여부
	static char userChar2; //유저 캐릭터2 여부
	static char userChar3; //유저 캐릭터3 여부


	void print();//screen에 저장된 스크린의 이름에 따라 해당 화면 출력
		
	static void printFrame();//화면의 프레임을 출력하는 함수
		


	static void move_arrow_key(char key, int *x, int *y, int y_h, int y_l);//입력된 키보드 값에 따라 좌표 변경

};


#endif