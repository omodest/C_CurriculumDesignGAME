#include "game.h"


void menu()
{
	printf("****************************\n");
	printf("*********1. play ***********\n");
	printf("*********0. play ***********\n");
	printf("****************************\n");
}


void game()
{
	//1�����̴�����mine������������ף�show����������ʾ����
	char mine[ROWS][COLS] = { 0 };
	char show[ROWS][COLS] = { 0 };

	//2�����̳�ʼ��
	//mine�����ʼ��Ϊ0����1Ϊ��
	//show�����ʼ��Ϊ*
	init_board(mine, ROWS, COLS, '0');
	init_board(show, ROWS, COLS, '*');

	//3�����̴�ӡ
	display_board(mine, ROW, COL);
	display_board(show, ROW, COL);

	//4������,��Ҫ����9*9�ĸ�����
	set_mine(mine, ROW, COL);
	//display_board(mine, ROW, COL);

	//����
	find_mine(mine, show, ROW, COL);

}

int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		printf("��ѡ��:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("�˳���Ϸ\n");
			break;
		default:
			printf("�����������������\n");
			break;
		}
	} while (input);
	return 0;
}

