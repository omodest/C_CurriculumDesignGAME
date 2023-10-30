#include"snake.h"

void Game()
{	
	srand((unsigned int)time(NULL));//随机种子
	GameWelcome();//游戏欢迎界面
	GameDescription();//游戏说明
	while (1)
	{
		DrawGameInterface();//绘制游戏运行界面
		if ( GetKeyboard()== 1 )//按键，进去游戏
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

