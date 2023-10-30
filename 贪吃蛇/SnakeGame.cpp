#include"snake.h"
void Move(int x, int y);//函数声明
void SnakeMove(int x);//函数声明

 //删除移动时的尾巴
 void DeleBody(int x, int y)
 {
	 gotoxy(x, y);
	// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x00);
	 printf("  ");
 }

//移动过程的实现
 void Move(int x,int y)
 {
	 Snake* p = AllocSnakeHead(x, y);
	 //新的头
	 Snake* t = sHead;
	 Snake* t1 = t->next;
	 //记录旧的头

	 t->body = "●";
	 //原来的头变为身体

	 p->next = t;
	 //链接
	 sHead = p;
	 //新的头赋值给sHead
	
	 //去掉最后一个节点
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

 //蛇移动
 void SnakeMove(int x)
 {
	 //不可往相反的方向走
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
		printf("游戏结束，继续加油 `(*>﹏<*)′");
		gotoxy(68, 18);
		printf("==>按Esc退出，按L继续<==");
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
			 conut = 0; //蛇头创建处
			 win = 0;//输赢打印
			 play.score = 0;
			 return 2;
		 default:
			 break;
		 }
		 b = getch();
	 }
	 return 0;
 }

//添加身体
void AddBody()
{

	//也可以使用尾插入，会更简单。
	Snake* p = sHead;
	//找到最后的一个节点
	while (p->next)
	{
		p = p->next;
	}
	Snake* t = AllocSnakeBody(p->x, p->y,0);
	p->next = t;
}

void EatFoodSet()
{
	//原来的食物，会被蛇头覆盖掉，因此是要添加蛇尾就可以。

	AddBody(); //移动身体
	CreatFood();//产生新的食物
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
	printf("得分:  %d （￣︶￣）　", play.score);
	SnakeLenth++;
}
int win = 0;
int JudgeWin()
{
	gotoxy(68, 16);
	//每一个输出对应位置要等长
	printf("游戏胜利      (●'-'●)       ");
	gotoxy(68, 18);
	printf("成功获得蛇王的称号      ");
	gotoxy(68, 20);
	printf("按Esc退出，按L继续");
	win = 1;
	return FinishSet();
}
int JudgeHitWall()
{
	return  FinishSet();
}
int JudgeFood()
{
   EatFoodSet();//吃到食物设置
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
 //判断
 int Judge()
 {
	 //判断输赢
	 if (play.score == Win)
	 return JudgeWin();
	 //判断是否撞墙
	 if (sHead->x == Map_x_left + 1 || sHead->x == Map_x_left ||
		 sHead->x == Map_x_right - 1 || sHead->x == Map_x_right ||
		 sHead->y == Map_y_up || sHead->y == Map_y_down)
	 return JudgeHitWall();
	 //判断是否迟到食物,吃到食物  将食物变为头，原来的头变为身体 -->Move函数
	 if (sHead->x == food->x && sHead->y == food->y )
	  return JudgeFood();

	 //判断是否撞到自己
	 if (JudgeHitSelf())
	 {
		 ;
	 }
	 else//是否撞到障碍物
		return JudgeObstacle();

	 return 0;
 }

//按键
int key = 0;//当前方向的值
int key1 = 0; //只记录前一次蛇移动按键
int j = 0;//加速标记
int i = 0; //减速标记
int o = 1; //正常速度标记
int GetKeyboard()
{
	key = sHead->direction;
	while (1)
	{
		int b = kbhit();
		sHead->direction = key;
		if (kbhit())
		{    //左右需要移动2个单位移动，上下1个单位移动
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
				j = 1;//加速标记
				i = 0; //减速标记
				o = 0; //正常速度标记
				key = key1;
				break;
			case 'I':
			case 'i':
				j = 0;//加速标记
				i = 1; //减速标记
				o = 0; //正常速度标记
				key = key1;
				break;
			case 'o':
			case 'O':
				j = 0;//加速标记
				i = 0; //减速标记
				o = 1; //正常速度标记
				key = key1;
				break;

			default:
				key = key1;
				break;
			}
		}
     	else//自动走的设置
		{
			SnakeMove(key);
			if (j)
				Sleep(150);
			if (i)
				Sleep(250);
			if (o)
				Sleep(200);
		}
		if (int ret = Judge())//判断是否吃到食物/是否死亡/赢
		{
			//返回值为真结束游戏 --- 死亡
			return ret;
		}
	}
	return 0;
}


//游戏创建
void DrawGameInterface()
{
	//绘制墙
	PaintWall();
	//绘制玩家属性
	PaintPlayInfa();
	//创建食物
	CreatFood();
	//创建蛇
	CreatSnake();
	//创建障碍物
	CreatObstacle();
}

