#include"snake.h"
void gotoxy(int x, int y)
{
	COORD pos; //λ�� COORD�ǿ��ﶨ������͡�
	HANDLE hOutput;
	pos.X = x;//ˮƽ����
	pos.Y = y;//��ֱ����
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	//��ȡ�������е����ݣ���ַ��ֵ�����
	SetConsoleCursorPosition(hOutput, pos);
	/*��λ���λ�õĺ���������ΪGetStdHandle�������ر�׼������ľ����
	Ҳ���ǻ�������Ļ�������ľ��������ֵ������ pos*/

	/*���ع����� */
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	SetConsoleCursorInfo(hOutput, &cursor);
}

/*ע�������������ÿ��+2 ��Ϊ����̨�ַ���߱�Ϊ 1��2 */

//��Ϸ��ӭ��������
void gotopaintWel(int x, int y)
{
	/*������ɫ*/
	gotoxy(x, y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	printf("��");
}

//��Ϸ˵����������
void gotopaintDes(int x, int y)
{
	gotoxy(x, y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	printf("��");
}

//��Ϸ���н���--Χǽ
void gotopaintWall(int x, int y)
{
	gotoxy(x, y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);
	printf("��");
}

//������Խ���
void gotopaintPler(int x, int y)
{
	gotoxy(x, y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0e);
	printf("��");
}

//���� ��ӭ/˵������
void PaintInterface()
{
	/*ע�������������ÿ��+2 ��Ϊ����̨�ַ���߱�Ϊ 1��2  x = 2y  */
	int i = 0;
	static int j = 1;//ÿһ�ε��ô�ӡ��ͬ����״
	//����
	// (20,2)-(60,2)
	// (20,23)-(60,23)
	for (i = Infa_x_left; i < Infa_x_right + 1; i += 2)//�ϱ�
	{
		if (j == 1)
			gotopaintWel(i, Infa_y_up);
		if (j == 2)
			gotopaintDes(i, Infa_y_up);

	}
	for (i = Infa_y_up; i < Infa_y_down; i++)//���
	{
		if (j == 1)
			gotopaintWel(Infa_x_left, i);
		if (j == 2)
			gotopaintDes(Infa_x_left, i);
	}
	for (i = Infa_x_left; i < Infa_x_right + 1; i += 2)//�±�
	{
		if (j == 1)
			gotopaintWel(i, Infa_y_down);
		if (j == 2)
			gotopaintDes(i, Infa_y_down);
	}
	for (i = Infa_y_up; i < Infa_y_down; i++)//�ұ�
	{
		if (j == 1)
			gotopaintWel(Infa_x_right, i);
		if (j == 2)
			gotopaintDes(Infa_x_right, i);
	}
	j++;
}

//��ӭ����
void GameWelcome()
{
	PaintInterface();
	//�������귶Χ   20,2 -- 60,2
	//               20,22-- 60,22 
	gotoxy(48, 7);
	printf("�{��ߩרTһ �������");
	gotoxy(48, 9);
	printf("Welcome to Snake Game");
	gotoxy(48, 11);
	printf("������׼������-.-");
	gotoxy(48, 13);
	printf("��Ϸ������ʼ��");
	//����ʱ
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

//��Ϸ˵������
void GameDescription()
{
	PaintInterface();

	gotoxy(46, 5);
	printf("����˵��:");
	gotoxy(46, 7);
	printf("w ��:��,s��:��,a��:�� ,d��:��");
	gotoxy(46, 9);
	printf("���٣�J/j ���٣�I/i ������O/o");
	gotoxy(46, 11);
	printf("Esc���˳���Ϸ L����Ϸ����");
	gotoxy(46, 11);
	printf("�������������Ϸ");
	gotoxy(46, 15);
	printf("��Ϸ˵��:\n");
	gotoxy(46, 17);
	printf("ʳ���ϰ����\n");
	gotoxy(46, 19);
	printf("С�߲��ɻ�ͷ��ײǽ/�ϰ�������");
	Sleep(5000);
	system("cls");
}

//����ǽ
void PaintWall()
{
	int i = 0;
	//2,4-52,4
	//2,29-52,29
	for (i = Map_x_left; i < Map_x_right + 1; i += 2)//�ϱ�
	{
		gotopaintWall(i, Map_y_up);
	}
	for (i = Map_y_up; i < Map_y_down; i++)//���
	{
		gotopaintWall(Map_x_left, i);
	}
	for (i = Map_x_left; i < Map_x_right + 1; i += 2)//�±�
	{
		gotopaintWall(i, Map_y_down);
	}
	for (i = Map_y_up; i < Map_y_down; i++)//�ұ�
	{
		gotopaintWall(Map_x_right, i);
	}
}

//����������Խ���
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
//�������
Player play = { 0 };
//ȫ�ֱ���

void PlayInfaAttr()
{
	gotoxy(58, 2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0b);
	printf("̰����");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
	gotoxy(74, 10);
	printf("o(*^��^*)o");
	gotoxy(72, 16);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
	//��ȡ��ǰʱ��
	gotoxy(64, 21);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x09);
	printf("%s", Gettime());

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
	gotoxy(68, 16);
	printf("��Ϸ������                    ");
	gotoxy(68, 18);
	printf("������Ӵ,��������  ^_^  ");
	gotoxy(68, 20);
	printf("                  ");

	gotoxy(64, 28);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
	printf("�����ߣ�������������");
}

//����������Խ���
void PaintPlayInfa()
{
	int i = 0;
	for (i = Play_x_left; i < Play_x_right + 1; i += 2)//�ϱ�
	{
		gotopaintPler(i, Play_y_up);
	}
	for (i = Play_y_up; i < Play_y_down; i++)//���
	{
		gotopaintPler(Play_x_left, i);
	}
	for (i = Play_x_left; i < Play_x_right + 1; i += 2)//�±�
	{
		gotopaintPler(i, Play_y_down);
	}
	for (i = Play_y_up; i < Play_y_down; i++)//�ұ�
	{
		gotopaintPler(Play_x_right, i);
	}
	PlayInfaAttr();
}




