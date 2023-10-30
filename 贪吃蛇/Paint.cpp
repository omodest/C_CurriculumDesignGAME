#include"snake.h"
void gotoxy(int x, int y)
{
	COORD pos; //位置 COORD是库里定义的类型。
	HANDLE hOutput;
	pos.X = x;//水平方向
	pos.Y = y;//垂直方向
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	//获取缓冲区中的数据，地址赋值给句柄
	SetConsoleCursorPosition(hOutput, pos);
	/*定位光标位置的函数，坐标为GetStdHandle（）返回标准的输出的句柄，
	也就是获得输出屏幕缓冲区的句柄，并赋值给对象 pos*/

	/*隐藏光标操作 */
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	SetConsoleCursorInfo(hOutput, &cursor);
}

/*注意这里横坐标是每次+2 因为控制台字符宽高比为 1：2 */

//游戏欢迎界面设置
void gotopaintWel(int x, int y)
{
	/*字体颜色*/
	gotoxy(x, y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	printf("□");
}

//游戏说明界面设置
void gotopaintDes(int x, int y)
{
	gotoxy(x, y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	printf("□");
}

//游戏运行界面--围墙
void gotopaintWall(int x, int y)
{
	gotoxy(x, y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);
	printf("■");
}

//玩家属性界面
void gotopaintPler(int x, int y)
{
	gotoxy(x, y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0e);
	printf("□");
}

//绘制 欢迎/说明界面
void PaintInterface()
{
	/*注意这里横坐标是每次+2 因为控制台字符宽高比为 1：2  x = 2y  */
	int i = 0;
	static int j = 1;//每一次调用打印不同的形状
	//坐标
	// (20,2)-(60,2)
	// (20,23)-(60,23)
	for (i = Infa_x_left; i < Infa_x_right + 1; i += 2)//上边
	{
		if (j == 1)
			gotopaintWel(i, Infa_y_up);
		if (j == 2)
			gotopaintDes(i, Infa_y_up);

	}
	for (i = Infa_y_up; i < Infa_y_down; i++)//左边
	{
		if (j == 1)
			gotopaintWel(Infa_x_left, i);
		if (j == 2)
			gotopaintDes(Infa_x_left, i);
	}
	for (i = Infa_x_left; i < Infa_x_right + 1; i += 2)//下边
	{
		if (j == 1)
			gotopaintWel(i, Infa_y_down);
		if (j == 2)
			gotopaintDes(i, Infa_y_down);
	}
	for (i = Infa_y_up; i < Infa_y_down; i++)//右边
	{
		if (j == 1)
			gotopaintWel(Infa_x_right, i);
		if (j == 2)
			gotopaintDes(Infa_x_right, i);
	}
	j++;
}

//欢迎界面
void GameWelcome()
{
	PaintInterface();
	//区域坐标范围   20,2 -- 60,2
	//               20,22-- 60,22 
	gotoxy(48, 7);
	printf("▄︻┻┳═一 ○○○○○○");
	gotoxy(48, 9);
	printf("Welcome to Snake Game");
	gotoxy(48, 11);
	printf("你做好准备了嘛-.-");
	gotoxy(48, 13);
	printf("游戏即将开始：");
	//倒计时
	int i = 3;
	for (; i >= 0; i--)
	{
		gotoxy(66, 13);
		printf("%d", i);
		Sleep(1000);
	}
	if (i == -1)
		system("cls");

}

//游戏说明界面
void GameDescription()
{
	PaintInterface();

	gotoxy(46, 5);
	printf("按键说明:");
	gotoxy(46, 7);
	printf("w ↑:上,s↓:下,a←:左 ,d→:右");
	gotoxy(46, 9);
	printf("加速：J/j 减速：I/i 正常：O/o");
	gotoxy(46, 11);
	printf("Esc：退出游戏 L：游戏继续");
	gotoxy(46, 11);
	printf("按任意键进入游戏");
	gotoxy(46, 15);
	printf("游戏说明:\n");
	gotoxy(46, 17);
	printf("食物：★，障碍物：■\n");
	gotoxy(46, 19);
	printf("小蛇不可回头，撞墙/障碍物死亡");
	Sleep(5000);
	system("cls");
}

//绘制墙
void PaintWall()
{
	int i = 0;
	//2,4-52,4
	//2,29-52,29
	for (i = Map_x_left; i < Map_x_right + 1; i += 2)//上边
	{
		gotopaintWall(i, Map_y_up);
	}
	for (i = Map_y_up; i < Map_y_down; i++)//左边
	{
		gotopaintWall(Map_x_left, i);
	}
	for (i = Map_x_left; i < Map_x_right + 1; i += 2)//下边
	{
		gotopaintWall(i, Map_y_down);
	}
	for (i = Map_y_up; i < Map_y_down; i++)//右边
	{
		gotopaintWall(Map_x_right, i);
	}
}

//绘制玩家属性界面
char* Gettime()
{
	time_t rawtime;
	struct tm* info;
	//static char buffer[80];
	char* buffer = (char*)malloc(80);
	time(&rawtime);

	info = localtime(&rawtime);

	strftime(buffer, 80, "%Y-%m-%d %H:%M:%S   %A", info);
	return  buffer;

}
//玩家属性
Player play = { 0 };
//全局变量

void PlayInfaAttr()
{
	gotoxy(58, 2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0b);
	printf("贪吃蛇");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
	gotoxy(74, 10);
	printf("o(*^＠^*)o");
	gotoxy(72, 16);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
	//获取当前时间
	gotoxy(64, 21);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x09);
	printf("%s", Gettime());

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
	gotoxy(68, 16);
	printf("游戏进行中                    ");
	gotoxy(68, 18);
	printf("还不错哟,继续加油  ^_^  ");
	gotoxy(68, 20);
	printf("                  ");

	gotoxy(64, 28);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
	printf("制作者：日向晚，声声慢");
}

//绘制玩家属性界面
void PaintPlayInfa()
{
	int i = 0;
	for (i = Play_x_left; i < Play_x_right + 1; i += 2)//上边
	{
		gotopaintPler(i, Play_y_up);
	}
	for (i = Play_y_up; i < Play_y_down; i++)//左边
	{
		gotopaintPler(Play_x_left, i);
	}
	for (i = Play_x_left; i < Play_x_right + 1; i += 2)//下边
	{
		gotopaintPler(i, Play_y_down);
	}
	for (i = Play_y_up; i < Play_y_down; i++)//右边
	{
		gotopaintPler(Play_x_right, i);
	}
	PlayInfaAttr();
}




