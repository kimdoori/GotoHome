#include <iostream>
#include <string>

#include "StoreScreen.h"

#include "Screen.h"

#include "SetWindows.h"
#include "ConnectDB.h"

void StoreScreen::printScreen(){
	if (Screen::failPurchase){
	SetWindows::gotoxy(5, 30);
	printf("                                 ");
	printf("- ������ �ݾ��� �ʹ� �����ϴ� -");
	Screen::failPurchase = false;

	}
	if (Screen::prePurchase){
		SetWindows::gotoxy(5, 30);
		printf("                                 ");
		printf("- �̹� �����Ͻ� ĳ�����Դϴ� -");
		Screen::prePurchase = false;
	}

	SetWindows::gotoxy(45, 3);
	printf("ĳ���� ����");
	
	
	
	SetWindows::gotoxy(45, 7);

	if (Screen::userChar1 == 'y'){
		char1Message = "���� �Ϸ�";
	}
	if (Screen::userChar2 == 'y'){
		char2Message = "���� �Ϸ�";

	}
	if (Screen::userChar3 == 'y'){
		char3Message = "���� �Ϸ�";

	}

	SetWindows::gotoxy(80, 7);

	printf("���� ���� : %d", Screen::userCoin);
	

	SetWindows::setColor(14, 0);
	SetWindows::gotoxy(14, 13);
	printf(char1Message.c_str());
	SetWindows::setColor(15, 0);

	SetWindows::gotoxy(17, 15);
	printf("��");
	SetWindows::gotoxy(11, 18);
	SetWindows::setColor(15, 0);
	printf("ǫ��ǫ�� ���Ͼ�");
	SetWindows::gotoxy(11, 20);
	printf("�ִ� ��� : 3��");
	SetWindows::gotoxy(11, 21);
	printf("���� ȹ�� : 1��");

	SetWindows::gotoxy(11, 25);
	printf("���� (����) : 0��");

	SetWindows::gotoxy(6, 27);
	SetWindows::setColor(8, 0);
	printf("�����Ϸ��� 1�� �����ּ���.");




	SetWindows::setColor(14, 0);
	SetWindows::gotoxy(46, 13);
	printf(char2Message.c_str());
	SetWindows::setColor(11, 0);
	SetWindows::gotoxy(49, 15);
	printf("��");
	SetWindows::gotoxy(44,18);
	SetWindows::setColor(11, 0);
	printf("���Ǹ��� ����");
	SetWindows::gotoxy(43, 20);
	printf("�ִ� ��� : 5��");
	SetWindows::gotoxy(43, 21);
	printf("���� ȹ�� : 2��");

	SetWindows::gotoxy(43, 25);
	printf("���� (����) : 50��");
	SetWindows::gotoxy(38, 27);
	SetWindows::setColor(8, 0);
	printf("�����Ϸ��� 2�� �����ּ���.");


	SetWindows::setColor(14, 0);
	SetWindows::gotoxy(76, 13);
	printf(char3Message.c_str());
	SetWindows::setColor(13, 0);
	SetWindows::gotoxy(79, 15);
	printf("��");
	SetWindows::gotoxy(75, 18);
	SetWindows::setColor(13, 0);
	printf("��ũ��ũ ��Ʈ");

	SetWindows::gotoxy(74, 20);
	printf("�ִ� ��� : 5��");
	SetWindows::gotoxy(74, 21);
	printf("��Ȱ ���� : 1��");

	SetWindows::gotoxy(74, 25);
	printf("���� (����) : 150��");
	
	SetWindows::gotoxy(70, 27);
	SetWindows::setColor(8, 0);
	printf("�����Ϸ��� 3�� �����ּ���.");

	SetWindows::setColor(15, 0);




	SetWindows::gotoxy(85, 32);
	printf("�� ����");
	cursor(30,30);

}
void StoreScreen::change(char key, int *x, int *y){
	if (key == 13){
	switch (*y){
	case 32://������ ȭ������
		Screen::screen = "mypage";
		break;
	}
}
	
}
void StoreScreen::cursor(int y_h, int y_l){
	char key;
	int x = 80, y = 32;
	do{
		SetWindows::gotoxy(x, y);
		printf(">");
		key = _getch();
		SetWindows::gotoxy(x, y);
		printf(" ");
		checkCharInfo(key);
		
	//	Screen::move_arrow_key(key, &x, &y, y_h, y_l);
	} while (key != 13 && key != 49 && key != 50 && key != 51);//����ġ�� ����������
	change(key,&x, &y);
}
void StoreScreen::checkCharInfo(char key){
	switch (key){
	case 49:
		if (Screen::userChar1 == 'n'){
			updateCharInfo("char1",0);
		}
		else{
			Screen::prePurchase = true;
			//�̹� �����ߴٴ� �޽���
		}
		
		break;
	case 50:
		if (Screen::userChar2 == 'n'){
			updateCharInfo("char2", 50);
		}
		else{
			//�̹� �����ߴٴ� �޽���
			Screen::prePurchase = true;

		}
		break;
	case 51:
		if (Screen::userChar3 == 'n'){
			updateCharInfo("char3", 150);
		}
		else{
			//�̹� �����ߴٴ� �޽���
			Screen::prePurchase = true;

		}
		break;

	}

}
void StoreScreen::updateCharInfo(string column,int charCoin){
	ConnectDB connectDB;
	connectDB.Mysql();

	string query = "";
	if (Screen::userCoin >= charCoin){//update �ϱ�
	query.append("UPDATE userGameInfo SET ");
	query.append(column + " = 'y', coin = ");
	query.append(to_string(Screen::userCoin - charCoin));
	query.append("  WHERE id = '");
	query.append(Screen::userId + "'");
		//UPDATE ���̺�� SET �ʵ�� = "�ٲ� ��" WHERE �ʵ��= "���� ��" 
	PlaySound(TEXT("2501source/purchase.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);

	mysql_query(&connectDB.mysql, query.c_str());
	}
	else{
		//���� ���ٴ� �޽���
		mysql_close(&connectDB.mysql);
		Screen::failPurchase = true;
	
		return;
	}
	query = "SELECT * FROM userGameInfo where id = '" + Screen::userId + "'";
	mysql_query(&connectDB.mysql, query.c_str());
	connectDB.res = mysql_store_result(&connectDB.mysql);
	if (connectDB.row = mysql_fetch_row(connectDB.res)){
		Screen::userCoin = atoi(connectDB.row[2]);
		Screen::userChar1 = *connectDB.row[3];
		Screen::userChar2 = *connectDB.row[4];
		Screen::userChar3 = *connectDB.row[5];

	}
	mysql_free_result(connectDB.res);
	mysql_close(&connectDB.mysql);

}