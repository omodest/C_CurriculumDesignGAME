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

//��ӡ9*9�ľ�����
void display_board(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	//��ӡ�к�
	for (j = 0; j <= col; j++)
	{
		printf("%d ", j);
	}
	printf("\n");
	for (i = 1; i <= row; i++)
	{
		printf("%d ", i);  //��ӡ�к�
		for (j = 1; j <= col; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}


//����
//1:Ҫ���������������������x,������y
//2:��λ���Ƿ񱻲�����
void set_mine(char board[ROWS][COLS], int row, int col)
{
	int count = EASY_COUNT;
	while (count)
	{
		int x = rand() % row + 1;  //ȡ�����ɵ�����0-row-1��
		int y = rand() % col + 1;  //ȡ�����ɵ�����0-row-1��
		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			count--;
		}
	}
}



//��ȡ����
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


//�ݹ�չ��
static void expand(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y, int* win)
{
	if (x >= 1 && x <= ROW && y >= 1 && y <=  COL)
	{
		int count = get_mine_count(mine, x, y);
		if (count == 0)
		{
				//���(x,y)��������û����,�����Ϊ�ո񣬲�����������ɢ
				show[x][y] = ' ';
				int i = 0;
				for (i = x - 1; i <= x + 1; i++)
				{
					int j = 0;
					for (j = y - 1; j <= y + 1; j++)
					{
						//ֻ��*���еݹ飬��ֹ��ѭ��
						if (show[i][j] == '*')
						{
							expand(mine, show, i, j,win);
						}
					}
				}
		}
		else  //����������ʾ����
		{
			show[x][y] = count + '0';
		}
		(*win)++;
	}
}


//����
//1:���������Ƿ�Ϸ�
//2:���������Ƿ��Ź���

//3:���׽�����־,ȫ�����꣬���߲���
void find_mine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int win = 0;

	while (win < row * col - EASY_COUNT)
	{
		printf("------------------------------\n");
		printf("������Ҫ���׵�����:>");
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			//�ж��Ƿ��Ź���
			if (show[x][y] == '*')
			{
				//������
				if (mine[x][y] == '1')
				{
					printf("���ź����㱻�׿����Ӷ�ըû��\n");
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
				printf("��λ���Ѿ��Ź����ˣ�����������\n");
			}
		}
		else
		{
			printf("����Ƿ�������������\n");
		}
	}
	if (win == row * col - EASY_COUNT)
	{
		printf("��ϲ�����׳ɹ�\n");
		display_board(mine, ROW, COL);
	}
}



