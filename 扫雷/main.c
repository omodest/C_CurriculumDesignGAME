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
	//1：雷盘创建，mine数组用来存放雷，show数组用来显示排雷
	char mine[ROWS][COLS] = { 0 };
	char show[ROWS][COLS] = { 0 };

	//2：雷盘初始化
	//mine数组初始化为0其中1为雷
	//show数组初始化为*
	init_board(mine, ROWS, COLS, '0');
	init_board(show, ROWS, COLS, '*');

	//3：雷盘打印
	display_board(mine, ROW, COL);
	display_board(show, ROW, COL);

	//4：布雷,雷要布在9*9的格子里
	set_mine(mine, ROW, COL);
	//display_board(mine, ROW, COL);

	//排雷
	find_mine(mine, show, ROW, COL);

}

int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		printf("请选择:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("输入错误，请重新输入\n");
			break;
		}
	} while (input);
	return 0;
}

