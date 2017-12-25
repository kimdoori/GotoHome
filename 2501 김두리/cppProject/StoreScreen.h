#ifndef STORESCREEN_H
#define STORESCREEN_H
#include "Screen.h"

class StoreScreen : public Screen{
public:
	string char1Message="";
	string char2Message="";
	string char3Message="";
	
	void printScreen();
	void change(char key,int *x, int *y);
	void cursor(int y_h,int y_l);
	void checkCharInfo(char key);
	void updateCharInfo(string column, int charCoin);


};
#endif