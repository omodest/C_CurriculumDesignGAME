#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


#define ROW 9
#define COL 9

#define ROWS ROW+2
#define COLS COL+2

#define EASY_COUNT 10


//���̳�ʼ��,��ʼ���ǲ���ҪΪ11*11����ֹ����Խ�磬��ӡֻ��Ҫ9*9�ľ�����
void init_board(char board[ROWS][COLS], int rows, int cols, char set);


//��ӡ����
void display_board(char board[ROWS][COLS], int row, int col);

//����
void set_mine(char board[ROWS][COLS], int row, int col);

//����
void find_mine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);



