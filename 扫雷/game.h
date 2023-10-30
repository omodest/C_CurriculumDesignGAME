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


//雷盘初始化,初始化是参数要为11*11，防止数组越界，打印只需要9*9的就行了
void init_board(char board[ROWS][COLS], int rows, int cols, char set);


//打印雷盘
void display_board(char board[ROWS][COLS], int row, int col);

//布雷
void set_mine(char board[ROWS][COLS], int row, int col);

//排雷
void find_mine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);



