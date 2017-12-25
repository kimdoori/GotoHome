#ifndef SETWINDOWS_H
#define SETWINDOWS_H

class SetWindows{
public:
	static void gotoxy(int x, int y);//좌표이동 함수
		
	static void setColor(int color, int bgcolor);//색설정
		
	static void setCursor(bool bVisible);//커서 보임 여부
	
};
#endif