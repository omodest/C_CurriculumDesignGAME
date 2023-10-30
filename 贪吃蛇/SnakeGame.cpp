#include"snake.h"
void Move(int x, int y);//��������
void SnakeMove(int x);//��������

 //ɾ���ƶ�ʱ��β��
 void DeleBody(int x, int y)
 {
	 gotoxy(x, y);
	// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x00);
	 printf("  ");
 }

//�ƶ����̵�ʵ��
 void Move(int x,int y)
 {
	 Snake* p = AllocSnakeHead(x, y);
	 //�µ�ͷ
	 Snake* t = sHead;
	 Snake* t1 = t->next;
	 //��¼�ɵ�ͷ

	 t->body = "��";
	 //ԭ����ͷ��Ϊ����

	 p->next = t;
	 //����
	 sHead = p;
	 //�µ�ͷ��ֵ��sHead
	
	 //ȥ�����һ���ڵ�
	 while (t1->next)
	 {
		 t = t->next;
		 t1 = t1->next;
	 }
	 DeleBody(t1->x, t1->y);
	 t->next = NULL;
	 free(t1);
	 p = NULL;
 }

 //���ƶ�
 void SnakeMove(int x)
 {
	 //�������෴�ķ�����
	 switch (x)
	 {
	 case UP:
		 if (x != DOWN)
		 {
			 Move(sHead->x,sHead->y - 1);
			 ShowSnake(sHead);
		 }
		 break;
	 case DOWN:
		 if (x != UP)
		 {
			 Move(sHead->x, sHead->y + 1);
			 ShowSnake(sHead);
		 }
		 break;
	 case LEFT:
		 if (x != RIGHT)
		 {
			 Move(sHead->x - 2, sHead->y);
			 ShowSnake(sHead);
		 }
		 break;
	 case RIGHT:
		 if (x != LEFT)
		 {
			 Move(sHead->x + 2 , sHead->y);
			 ShowSnake(sHead);
		 }
		 break;
	 }
 }


int FinishSet()
 {
	if (ObstacleConut > 0)
	{
		Obstacle* p = obstacle->next;
		free(p);
		obstacle->next = NULL;
	}
	switch (win)
	{
	case 0:
		gotoxy(68, 16);
		printf("��Ϸ�������������� `(*>�n<*)��");
		gotoxy(68, 18);
		printf("==>��Esc�˳�����L����<==");
		gotoxy(68, 20);
		printf("                  ");
		break;
	case 1:
		break;
	}
	int b = getch();
	 while (b)
	 {
		 switch (b)
		 {
		 case 27:
			 system("cls");
			 return 1;
		 case 'l':
		 case 'L':
			 system("cls");
			 conut = 0; //��ͷ������
			 win = 0;//��Ӯ��ӡ
			 play.score = 0;
			 return 2;
		 default:
			 break;
		 }
		 b = getch();
	 }
	 return 0;
 }

//�������
void AddBody()
{

	//Ҳ����ʹ��β���룬����򵥡�
	Snake* p = sHead;
	//�ҵ�����һ���ڵ�
	while (p->next)
	{
		p = p->next;
	}
	Snake* t = AllocSnakeBody(p->x, p->y,0);
	p->next = t;
}

void EatFoodSet()
{
	//ԭ����ʳ��ᱻ��ͷ���ǵ��������Ҫ�����β�Ϳ��ԡ�

	AddBody(); //�ƶ�����
	CreatFood();//�����µ�ʳ��
	play.score++;
	switch (play.score)
	{
	case 2:
	case 4:
	case 6:
	case 8:
	case 10:
	case 12:
	case 14:
		CreatObstacle();
		CreatObstacle();
	default:
		break;
	}
	gotoxy(68, 13);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x05);
	printf("�÷�:  %d �����������", play.score);
	SnakeLenth++;
}
int win = 0;
int JudgeWin()
{
	gotoxy(68, 16);
	//ÿһ�������Ӧλ��Ҫ�ȳ�
	printf("��Ϸʤ��      (��'-'��)       ");
	gotoxy(68, 18);
	printf("�ɹ���������ĳƺ�      ");
	gotoxy(68, 20);
	printf("��Esc�˳�����L����");
	win = 1;
	return FinishSet();
}
int JudgeHitWall()
{
	return  FinishSet();
}
int JudgeFood()
{
   EatFoodSet();//�Ե�ʳ������
   return 0;
}
int JudgeHitSelf()
{
	Snake* p = sHead->next;
	while (p)
	{
		if (sHead->x == p->x && sHead->y == p->y)
			return  FinishSet();
		p = p->next;
	}
	return 0;
}
int JudgeObstacle()
{
	Obstacle* p = obstacle;
	while (p)
	{
		if (sHead->x == p->x && sHead->y == p->y)
			return  FinishSet();
		p = p->next;
	}
	return 0;
}
 //�ж�
 int Judge()
 {
	 //�ж���Ӯ
	 if (play.score == Win)
	 return JudgeWin();
	 //�ж��Ƿ�ײǽ
	 if (sHead->x == Map_x_left + 1 || sHead->x == Map_x_left ||
		 sHead->x == Map_x_right - 1 || sHead->x == Map_x_right ||
		 sHead->y == Map_y_up || sHead->y == Map_y_down)
	 return JudgeHitWall();
	 //�ж��Ƿ�ٵ�ʳ��,�Ե�ʳ��  ��ʳ���Ϊͷ��ԭ����ͷ��Ϊ���� -->Move����
	 if (sHead->x == food->x && sHead->y == food->y )
	  return JudgeFood();

	 //�ж��Ƿ�ײ���Լ�
	 if (JudgeHitSelf())
	 {
		 ;
	 }
	 else//�Ƿ�ײ���ϰ���
		return JudgeObstacle();

	 return 0;
 }

//����
int key = 0;//��ǰ�����ֵ
int key1 = 0; //ֻ��¼ǰһ�����ƶ�����
int j = 0;//���ٱ��
int i = 0; //���ٱ��
int o = 1; //�����ٶȱ��
int GetKeyboard()
{
	key = sHead->direction;
	while (1)
	{
		int b = kbhit();
		sHead->direction = key;
		if (kbhit())
		{    //������Ҫ�ƶ�2����λ�ƶ�������1����λ�ƶ�
			if (key == UP || key == DOWN || key == LEFT || key == RIGHT)
				key1 = key;
			key = getch();
			switch (key)
			{
			case 'a':
			case 'A':
			case 75:
				if (key1 != RIGHT)
					key = LEFT;
				else
					key = key1;
				break;
			case 's':
			case 'S':
			case 80:
				if (key1 != UP)
					key = DOWN;
				else
					key = key1;
				break;
			case 'd':
			case 'D':
			case 77:
				if (key1 != LEFT)
					key = RIGHT;
				else
					key = key1;
				break;
			case 'w':
			case 'W':
			case 72:
				if (key1 != DOWN)
					key = UP;
				else
					key = key1;
				break;
			case 'j':
			case 'J':
				j = 1;//���ٱ��
				i = 0; //���ٱ��
				o = 0; //�����ٶȱ��
				key = key1;
				break;
			case 'I':
			case 'i':
				j = 0;//���ٱ��
				i = 1; //���ٱ��
				o = 0; //�����ٶȱ��
				key = key1;
				break;
			case 'o':
			case 'O':
				j = 0;//���ٱ��
				i = 0; //���ٱ��
				o = 1; //�����ٶȱ��
				key = key1;
				break;

			default:
				key = key1;
				break;
			}
		}
     	else//�Զ��ߵ�����
		{
			SnakeMove(key);
			if (j)
				Sleep(150);
			if (i)
				Sleep(250);
			if (o)
				Sleep(200);
		}
		if (int ret = Judge())//�ж��Ƿ�Ե�ʳ��/�Ƿ�����/Ӯ
		{
			//����ֵΪ�������Ϸ --- ����
			return ret;
		}
	}
	return 0;
}


//��Ϸ����
void DrawGameInterface()
{
	//����ǽ
	PaintWall();
	//�����������
	PaintPlayInfa();
	//����ʳ��
	CreatFood();
	//������
	CreatSnake();
	//�����ϰ���
	CreatObstacle();
}

