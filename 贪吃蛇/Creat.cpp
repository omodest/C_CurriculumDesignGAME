#include"snake.h"

//��ʼ����ͷ/����
int conut = 0;
Snake* AllocSnakeHead(int x, int y)
{
	Snake* p = (Snake*)malloc(sizeof(Snake));//��ͷ

	//��һ��
	if (!conut)
	{
		p->x = rand() % Diff_x + Dif_x;
		p->y = rand() % Diff_y + Dif_y;
		while (p->x % 2)//x������ҪΪż��
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
	p->head = "��";
	p->next = NULL;
	return p;
}
//��ʼ������

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
	p->body = "��";
	p->next = NULL;
	return p;
}

//�������ͷ����
void InitSnake(Snake** sEnd)
{
	Snake* p = (Snake*)AllocSnakeBody((*sEnd)->x, (*sEnd)->y,1);
	(*sEnd)->next = p;//sHead->next = p
	*sEnd = p;
}
//�ڵ�ͼ�ϻ���
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

Snake* sHead;//ȫ�ֱ���--�ڴ���ʳ���ʱ������
Snake* sEnd;//ȫ�ֱ���
int SnakeLenth = 0;//�ߵĳ���
//������

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
	//�ߵ��������
	sHead->direction = rand() % 4 + 1;
	while (sHead->direction == LEFT)
	{
		sHead->direction = rand() % 4 + 1;
	}
	ShowSnake(sHead);
}

//��ʼ��ʳ��
Food* AllocFood(Snake* sHead)
{
	Food* p = (Food*)malloc(sizeof(Food));//ʳ��

	p->x = rand() % Foodd_x + Food_x;
	p->y = rand() % Foodd_y + Food_y;
	while (p->x % 2)
	{
		p->x = rand() % Foodd_x + Food_x;

	}
	p->head = "��";
	int flag = 0;
	//�ж�ʳ��������Ƿ�Ϸ�
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
//�ڵ�ͼ����ʾʳ��
void ShowFood(Food* food)
{
	gotoxy(food->x, food->y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0e);
	printf("%s", food->head);
}
//����ʳ��
Food* food;//��ʼ��ʳ��
void CreatFood()
{
	food = AllocFood(sHead);
	flagob = 1;
	ShowFood(food);//չʾ
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

int flagob = 0;//��ǣ�ʳ�ﴴ���꣬���ж��Ƿ��ظ�
Obstacle* AllocObstacle()
{
	Obstacle* p = (Obstacle*)malloc(sizeof(Obstacle));//�ϰ���
	p->x = rand() % Foodd_x + Food_x;
	p->y = rand() % Foodd_y + Food_y;
	while (p->x % 2)
	{
		p->x = rand() % Foodd_x + Food_x;
	}
	p->body = "��";
	p->next = NULL;

	int flag = 0;
	//�ж��ϰ���������Ƿ�Ϸ�
	while (1)
	{
		Snake* t = sHead;
		//�ж�������
		while (t)
		{
			if (t->x == p->x && t->y == p->y)
			{
				flag = 1;
				break;
			}
			t = t->next;
		}
		//�ж�ʳ������
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

Obstacle* obstacle = AllocObstacle(); //ȫ�ֱ���
//�����ϰ���
int ObstacleConut = 0;
void CreatObstacle()
{
	InitObstacle(obstacle);//ͷ�巨����
	ObstacleConut++;
	ShowObstacle(obstacle);//չʾ
}

