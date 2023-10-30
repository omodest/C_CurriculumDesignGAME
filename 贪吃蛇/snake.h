#pragma once
#include<stdio.h>
#include<windows.h>
#include<ctime>
#include<string.h>
#include<conio.h>//getch()������ͷ�ļ�
#include<iostream> //���롢�������ͷ�ļ�
#include<time.h>
#include<stdlib.h>

//���� 4996 ����
#pragma warning(disable: 4996)

enum MoveKey
{
	LEFT = 1,
	DOWN,
	RIGHT,
	UP,
};

//�ߵ�����
typedef struct Snake 
{
	int x; //x,y �ߵ�λ��
	int y;
	const char* head;
	const char* body;
	struct Snake* next; //��������������Ĳ�����
	int direction;
}Snake;

//ʳ��
typedef struct Food
{
	int x; //x,y ʳ���λ��
	int y;
	const char* head;
}Food;

//�ϰ������� ���ŷ��������Ӷ�����
typedef struct Obstacle
{
	int x; //x,y �ϰ����λ��
	int y;
	const char* body;
	struct  Obstacle* next;   //5
}Obstacle;

typedef struct Player
{
	int score;
}Player;

//׹�����ǵ��±����
typedef struct Star
{
	int x;
	int y;
}Star;


//ȫ�ֱ���
extern int j;//���ٱ��
extern int i; //���ٱ��
extern int o; //�����ٶȱ��

extern int win;//��Ӯ���ж�
extern Player play;//�������
extern int SnakeLenth;//�߳���
extern Snake* sHead;//��ͷָ��
extern Snake* sEnd;//��βָ�봴����ʱ����
extern Food* food;//ʳ��
extern Obstacle* obstacle;//�ϰ���
extern int conut; //AllocSnakeHead�����е�ȫ�ֱ��� �����������
extern int ObstacleConut;//�ϰ������
extern int flagob;
// �����С����
// ��ͼ  
#define Map_x_left 2
#define Map_x_right 52
#define Mid_x 25
#define Map_y_up 2
#define Map_y_down 29
#define Mid_y 12

//��ʤ����
#define Win  20

//���ֵ�Ĳ���
//��
#define Diff_x    (Map_x_right - Map_x_left - 4*2 )//ͷ+�� -- 4
#define Dif_x     (4*2 + Map_x_left)   
#define Diff_y    (Map_y_down  - Map_y_up - 1)
#define Dif_y     (Map_y_up + 1)
//ʳ��
#define Foodd_x   (Map_x_right - Map_x_left - 3)//4-50-->0-46-->47
#define Food_x    4
#define Foodd_y   (Map_y_down - Map_y_up - 2)
#define Food_y    4


// ��ӭ/˵�� ����
#define Infa_x_left  38  //20
#define Infa_x_right 78//60
#define Infa_y_up 2
#define Infa_y_down 23
//��ҵ÷ֽ���
#define Play_x_left 60
#define Play_x_right 98
#define Play_y_up 9
#define Play_y_down 22

//��������

//��ָ��λ�����
extern void gotoxy(int x, int y);
//�ս�����Ϸ�Ľ���
extern void GameWelcome();
//��Ϸ˵��
extern void GameDescription();
//������Ϸ���н��� ����ͼ��������Խ��棩
extern void DrawGameInterface();
//�Ӽ��̻�ȡ��Ϣ
extern int GetKeyboard();
//����
extern int GetKeyboard();

//Creat�к�������
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

//Paint�к���
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

