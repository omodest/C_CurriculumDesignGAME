#include"snake.h"

//初始化蛇头/蛇身
int conut = 0;
Snake* AllocSnakeHead(int x, int y)
{
	Snake* p = (Snake*)malloc(sizeof(Snake));//蛇头

	//第一次
	if (!conut)
	{
		p->x = rand() % Diff_x + Dif_x;
		p->y = rand() % Diff_y + Dif_y;
		while (p->x % 2)//x的坐标要为偶数
		{
			p->x = rand() % Diff_x + Dif_x;
		}
		conut = 1;
	}
	else
	{
		p->x = x;
		p->y = y;
	}
	p->head = "⊙";
	p->next = NULL;
	return p;
}
//初始化蛇身

void Add(Snake* p,int x, int y)
{
	if (x < Mid_x && y > Mid_y)
	{
		if (sHead->direction == UP)
		{
			p->x = x + 2;
			p->y = y;
		}
		if (sHead->direction == RIGHT)
		{
			p->x = x;
			p->y = y - 1;
		}
			
	}
	else if (x < Mid_x && y < Mid_y)
	{
		if (sHead->direction == DOWN)
		{
			p->x = x + 2 ;
			p->y = y;
		}
		if (sHead->direction == RIGHT)
		{
			p->x = x;
			p->y = y + 1;
		}
	}
	else if (x > Mid_x && y < Mid_y)
	{
		if (sHead->direction == DOWN)
		{
			p->x = x - 2;
			p->y = y;
		}
		if (sHead->direction == LEFT)
		{
			p->x = x;
			p->y = y + 1;
		}
	}
	else if (x < Mid_x && y < Mid_y)
	{
		if (sHead->direction == UP)
		{
			p->x = x - 2;
			p->y = y;
		}
		if (sHead->direction == LEFT)
		{
			p->x = x;
			p->y = y - 1;
		}
	}
}
Snake* AllocSnakeBody(int x, int y,int z)
{
	Snake* p = (Snake*)malloc(sizeof(Snake));
	if (z)
	{
		p->x = x - 2;
		p->y = y;
	}
	else
	{
		Add(p ,x, y);
	}
	p->body = "●";
	p->next = NULL;
	return p;
}

//蛇身和蛇头链接
void InitSnake(Snake** sEnd)
{
	Snake* p = (Snake*)AllocSnakeBody((*sEnd)->x, (*sEnd)->y,1);
	(*sEnd)->next = p;//sHead->next = p
	*sEnd = p;
}
//在地图上画蛇
void ShowSnake(Snake* sHead)
{
	Snake* p = sHead;
	int flag = 1;
	while (p)
	{
		gotoxy(p->x, p->y);
		if (flag)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
			printf("%s", p->head);
			flag = 0;
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
			printf("%s", p->body);
		}
		p = p->next;
	}
}

Snake* sHead;//全局变量--在创建食物的时候有用
Snake* sEnd;//全局变量
int SnakeLenth = 0;//蛇的长度
//创建蛇

void CreatSnake()
{
	sHead = AllocSnakeHead(0, 0);
	sEnd = sHead;
	int i = 3;
	while (i--)
	{
		InitSnake(&sEnd);
		SnakeLenth++;
	}
	//蛇的随机方向
	sHead->direction = rand() % 4 + 1;
	while (sHead->direction == LEFT)
	{
		sHead->direction = rand() % 4 + 1;
	}
	ShowSnake(sHead);
}

//初始化食物
Food* AllocFood(Snake* sHead)
{
	Food* p = (Food*)malloc(sizeof(Food));//食物

	p->x = rand() % Foodd_x + Food_x;
	p->y = rand() % Foodd_y + Food_y;
	while (p->x % 2)
	{
		p->x = rand() % Foodd_x + Food_x;

	}
	p->head = "★";
	int flag = 0;
	//判断食物的坐标是否合法
	while (1)
	{
		Snake* t = sHead;
		while (t)
		{
			if (t->x == p->x && t->y == p->y)
			{
				flag = 1;
				break;
			}
			t = t->next;
		}
		if (flag)
		{
			p->x = rand() % Foodd_x + Food_x;
			while (p->x % 2)
			{
				p->x = rand() % Foodd_x + Food_x;
			}
			p->y = rand() % Foodd_y + Food_y + 1;
		}
		else
		{
			break;
		}
	}
	return p;
}
//在地图上显示食物
void ShowFood(Food* food)
{
	gotoxy(food->x, food->y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0e);
	printf("%s", food->head);
}
//创建食物
Food* food;//初始化食物
void CreatFood()
{
	food = AllocFood(sHead);
	flagob = 1;
	ShowFood(food);//展示
}

void ShowObstacle(Obstacle* obstacle)
{
	Obstacle* p = obstacle;
	int flag = 1;
	while (p)
	{
		gotoxy(p->x, p->y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x09);
		printf("%s", p->body);
		p = p->next;
	}
}

int flagob = 0;//标记：食物创建完，在判断是否重复
Obstacle* AllocObstacle()
{
	Obstacle* p = (Obstacle*)malloc(sizeof(Obstacle));//障碍物
	p->x = rand() % Foodd_x + Food_x;
	p->y = rand() % Foodd_y + Food_y;
	while (p->x % 2)
	{
		p->x = rand() % Foodd_x + Food_x;
	}
	p->body = "■";
	p->next = NULL;

	int flag = 0;
	//判断障碍物的坐标是否合法
	while (1)
	{
		Snake* t = sHead;
		//判断蛇坐标
		while (t)
		{
			if (t->x == p->x && t->y == p->y)
			{
				flag = 1;
				break;
			}
			t = t->next;
		}
		//判断食物坐标
		if (flagob)
		{
			if (food->x == p->x && food->y == p->y)
			{
				flag = 1;
			}
		}
		if (flag)
		{
			p->x = rand() % Foodd_x + Food_x + 1;
			while (p->x % 2)
			{
				p->x = rand() % Foodd_x + Food_x;
			}
			p->y = rand() % Foodd_y + Food_y + 1;
		}
		else
		{
			break;
		}
	}
	return p;
}

void InitObstacle(Obstacle* obstacle)
{
	Obstacle* p = AllocObstacle();
	p->next = obstacle->next;
	obstacle->next = p;
}

Obstacle* obstacle = AllocObstacle(); //全局变量
//创建障碍物
int ObstacleConut = 0;
void CreatObstacle()
{
	InitObstacle(obstacle);//头插法创建
	ObstacleConut++;
	ShowObstacle(obstacle);//展示
}

