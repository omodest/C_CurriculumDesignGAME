#include"snake.h"

void Game()
{	
	srand((unsigned int)time(NULL));//�������
	GameWelcome();//��Ϸ��ӭ����
	GameDescription();//��Ϸ˵��
	while (1)
	{
		DrawGameInterface();//������Ϸ���н���
		if ( GetKeyboard()== 1 )//��������ȥ��Ϸ
		{
			break;
		}
	}		
}
int main()
{
	Game();
	return 0;
}

