#pragma once
#include<stdio.h>
#include<windows.h>
#include<ctime>
#include<string.h>
#include<conio.h>//getch()函数的头文件
#include<iostream> //输入、输出流的头文件
#include<time.h>
#include<stdlib.h>

//屏蔽 4996 报错
#pragma warning(disable: 4996)

enum MoveKey
{
	LEFT = 1,
	DOWN,
	RIGHT,
	UP,
};

//蛇的属性
typedef struct Snake 
{
	int x; //x,y 蛇的位置
	int y;
	const char* head;
	const char* body;
	struct Snake* next; //链接蛇身（单链表的操作）
	int direction;
}Snake;

//食物
typedef struct Food
{
	int x; //x,y 食物的位置
	int y;
	const char* head;
}Food;

//障碍物属性 随着分数的增加而增加
typedef struct Obstacle
{
	int x; //x,y 障碍物的位置
	int y;
	const char* body;
	struct  Obstacle* next;   //5
}Obstacle;

typedef struct Player
{
	int score;
}Player;

//坠落星星的下标参数
typedef struct Star
{
	int x;
	int y;
}Star;


//全局变量
extern int j;//加速标记
extern int i; //减速标记
extern int o; //正常速度标记

extern int win;//输赢的判断
extern Player play;//玩家属性
extern int SnakeLenth;//蛇长度
extern Snake* sHead;//蛇头指针
extern Snake* sEnd;//蛇尾指针创建的时候用
extern Food* food;//食物
extern Obstacle* obstacle;//障碍物
extern int conut; //AllocSnakeHead函数中的全局变量 添加身体所用
extern int ObstacleConut;//障碍物个数
extern int flagob;
// 界面大小设置
// 地图  
#define Map_x_left 2
#define Map_x_right 52
#define Mid_x 25
#define Map_y_up 2
#define Map_y_down 29
#define Mid_y 12

//获胜个数
#define Win  20

//随机值的产生
//蛇
#define Diff_x    (Map_x_right - Map_x_left - 4*2 )//头+身 -- 4
#define Dif_x     (4*2 + Map_x_left)   
#define Diff_y    (Map_y_down  - Map_y_up - 1)
#define Dif_y     (Map_y_up + 1)
//食物
#define Foodd_x   (Map_x_right - Map_x_left - 3)//4-50-->0-46-->47
#define Food_x    4
#define Foodd_y   (Map_y_down - Map_y_up - 2)
#define Food_y    4


// 欢迎/说明 界面
#define Infa_x_left  38  //20
#define Infa_x_right 78//60
#define Infa_y_up 2
#define Infa_y_down 23
//玩家得分界面
#define Play_x_left 60
#define Play_x_right 98
#define Play_y_up 9
#define Play_y_down 22

//函数声明

//从指定位置输出
extern void gotoxy(int x, int y);
//刚进入游戏的界面
extern void GameWelcome();
//游戏说明
extern void GameDescription();
//绘制游戏运行界面 （地图、玩家属性界面）
extern void DrawGameInterface();
//从键盘获取信息
extern int GetKeyboard();
//按键
extern int GetKeyboard();

//Creat中函数声明
extern  Snake* AllocSnakeHead(int x, int y);
extern  Snake* AllocSnakeBody(int x, int y,int z);
extern void InitSnake(Snake** sEnd);
extern void ShowSnake(Snake* sHead);
extern void CreatSnake();

extern Food* AllocFood(Snake* sHead);
extern void ShowFood(Food* food);
extern void CreatFood();

extern void ShowObstacle(Obstacle* obstacle);
extern Obstacle* AllocObstacle();
extern void InitObstacle(Obstacle* obstacle);
extern  void CreatObstacle();

//Paint中函数
extern void gotoxy(int x, int y);
extern void gotopaintWel(int x, int y);
extern void gotopaintDes(int x, int y);
extern void gotopaintWall(int x, int y);
extern void gotopaintPler(int x, int y);
extern void PaintInterface();
extern void GameWelcome();
extern void GameDescription();
extern void PaintWall();
extern char* Gettime();
extern void PlayInfaAttr();
extern void PaintPlayInfa();

