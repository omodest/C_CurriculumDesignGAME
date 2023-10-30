#define _CRT_SECURE_NO_WARNINGS 1

#include "game.h"


void init_board(char board[ROWS][COLS], int rows, int cols, char set)
{
	int i = 0;
	for (i = 0; i < rows; i++)
	{
		int j = 0;
		for (j = 0; j < cols; j++)
		{
			board[i][j] = set;
		}
	}
}

//打印9*9的就行了
void display_board(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	//打印列号
	for (j = 0; j <= col; j++)
	{
		printf("%d ", j);
	}
	printf("\n");
	for (i = 1; i <= row; i++)
	{
		printf("%d ", i);  //打印行号
		for (j = 1; j <= col; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}


//布雷
//1:要随机生成两个数，横坐标x,纵坐标y
//2:该位置是否被布过雷
void set_mine(char board[ROWS][COLS], int row, int col)
{
	int count = EASY_COUNT;
	while (count)
	{
		int x = rand() % row + 1;  //取余生成的数是0-row-1的
		int y = rand() % col + 1;  //取余生成的数是0-row-1的
		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			count--;
		}
	}
}



//获取雷数
static int get_mine_count(char mine[ROWS][COLS], int x, int y)
{
	return (mine[x - 1][y - 1] +
		mine[x - 1][y] +
		mine[x - 1][y + 1] +
		mine[x][y - 1] +
		mine[x][y + 1] +
		mine[x + 1][y - 1] +
		mine[x + 1][y] +
		mine[x + 1][y + 1] - 8 * '0');
}


//递归展开
static void expand(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y, int* win)
{
	if (x >= 1 && x <= ROW && y >= 1 && y <=  COL)
	{
		int count = get_mine_count(mine, x, y);
		if (count == 0)
		{
				//如果(x,y)坐标四周没有雷,将其改为空格，并且向四周扩散
				show[x][y] = ' ';
				int i = 0;
				for (i = x - 1; i <= x + 1; i++)
				{
					int j = 0;
					for (j = y - 1; j <= y + 1; j++)
					{
						//只对*进行递归，防止死循环
						if (show[i][j] == '*')
						{
							expand(mine, show, i, j,win);
						}
					}
				}
		}
		else  //四周有雷显示雷数
		{
			show[x][y] = count + '0';
		}
		(*win)++;
	}
}


//排雷
//1:输入坐标是否合法
//2:输入坐标是否排过雷

//3:排雷结束标志,全部排完，或者踩雷
void find_mine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int win = 0;

	while (win < row * col - EASY_COUNT)
	{
		printf("------------------------------\n");
		printf("请输入要排雷的坐标:>");
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			//判断是否排过雷
			if (show[x][y] == '*')
			{
				//踩雷了
				if (mine[x][y] == '1')
				{
					printf("很遗憾，你被雷裤衩子都炸没了\n");
					//Sleep(1000);
					//system("cls");
					display_board(mine, ROW, COL);
					break;
				}
				else
				{
					//int count = get_mine_count(mine, x, y);
					//show[x][y] = count + '0';
					expand(mine, show, x, y, &win);
					display_board(show, ROW, COL);
					//win++;
				}
			}
			else
			{
				printf("该位置已经排过雷了，请重新输入\n");
			}
		}
		else
		{
			printf("坐标非法，请重新输入\n");
		}
	}
	if (win == row * col - EASY_COUNT)
	{
		printf("恭喜你排雷成功\n");
		display_board(mine, ROW, COL);
	}
}



