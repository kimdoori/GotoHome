#include <windows.h>

#include "SetWindows.h"

using namespace std;

void SetWindows :: gotoxy(int x, int y){//��ǥ�̵� �Լ�
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void SetWindows :: setColor(int color, int bgcolor){//������
	color &= 0xf;
	bgcolor &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}
void SetWindows :: setCursor(bool bVisible){//Ŀ�� ���� ����
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = bVisible; // true ����, false �Ⱥ���
	ConsoleCursor.dwSize = 1; // Ŀ��������
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor); // ����
}