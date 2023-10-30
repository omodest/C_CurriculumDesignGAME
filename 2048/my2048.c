/*
 * Author: Billsheng
 * DateTime: 2023-05-25 10:00
 */

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <time.h>

static int cmd;
static char yesorno;
static char temp;
static int add_num_flag = 0;
static int score = 0;
static int best = 0;
static int game_over = 0;
static int game_win = 0;
static int flag = 1;
static int board[4][4];                                               /* 游戏数字面板，抽象为二维数组 */
int zimo[15] = {31, 47, 63, 79, 95, 111, 112, 143, 159, 160, 176,207,223,224,240}; // 用于存储数字对应颜色值
int zimoxu = 0;
int lieweixu[4] = {25, 38, 51, 63};
int hangweixu[4] = {12, 14, 16, 18}; // 列、行位序用于记录显示数值的位置

void gotoxy(int x, int y);
void number();
int color(int c);
void drawTheGameBox();
void Gameplay();
void Replay();
void check_game_over();
void title();      // 绘制标题2048
void choice();     // 选择
void rule();       // 规则
void explation();  // 按键说明
void move_left();  /* 左移 */
void move_right(); /* 右移 */
void move_up();    /* 上移 */
void move_down();  /* 下移 */
void clear_screen();
void exitSys();             // 退出
int get_null_count();       // 获取空白位数
static void add_rand_num(); // 添加随机数

int main()
{
    while (1)
    {
        clear_screen();
        title();
        choice();
    }
    return 0;
}

/* 获取屏幕光标位置 */
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

/* 设置文字颜色 */
int color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void number()
{
    color(11);
    gotoxy(19, 2);
    printf("■ ■ ■ ■    ■ ■ ■ ■         ■      ■ ■ ■ ■");
    gotoxy(19, 3);
    printf("         ■    ■       ■     ■  ■      ■       ■");
    gotoxy(19, 4);
    printf("■ ■ ■ ■    ■       ■   ■ ■ ■ ■   ■ ■ ■ ■");
    gotoxy(19, 5);
    printf("■             ■       ■         ■      ■       ■");
    gotoxy(19, 6);
    printf("■ ■ ■ ■    ■ ■ ■ ■         ■      ■ ■ ■ ■");
}

void title() // 绘制标题2048
{
    system("cls");
    number();
    color(12);
    gotoxy(19, 8);
    printf("######################################################");
    gotoxy(19, 9);
    printf("#                                                    #");
    gotoxy(19, 10);
    printf("#      1.开始游戏                   2.游戏规则       #");
    gotoxy(19, 11);
    printf("#                                                    #");
    gotoxy(19, 12);
    printf("#      3.按键说明                   4.退出游戏       #");
    gotoxy(19, 13);
    printf("#                                                    #");
    gotoxy(19, 14);
    printf("######################################################");
}

void choice() // 选择
{
    cmd = _getch(); /* 接收标准输入流字符命令 */
    switch (cmd)
    {
    case '1':
        Gameplay();
        break;
    case '2':
        rule();
        break;
    case '3':
        explation(); // 按键说明
        break;
    case '4':
        exitSys();
        break;
    }
    if (game_win == 1)
        return;
}

void rule() // 规则说明
{
    while (1)
    {
        system("cls");
        // clear_screen();
        number();
        color(12);
        gotoxy(19, 8);
        printf("######################################################");
        gotoxy(19, 9);
        printf("#                                                    #");
        gotoxy(19, 10);
        printf("#                     规则说明                       #");
        gotoxy(19, 11);
        printf("#                                                    #");
        gotoxy(19, 12);
        printf("#    1、上下左右滑动，相同数字合并为更高级数字；     #");
        gotoxy(19, 13);
        printf("#                                                    #");
        gotoxy(19, 14);
        printf("#    2、滑动格子会在随机位置出现随机的数字2和数字4； #");
        gotoxy(19, 15);
        printf("#                                                    #");
        gotoxy(19, 16);
        printf("#    3、游戏胜利：合并数字出现2048即为成功；         #");
        gotoxy(19, 17);
        printf("#                                                    #");
        gotoxy(19, 18);
        printf("#    4、游戏结束：游戏界面被数字填满不能再滑动；     #");
        gotoxy(19, 19);
        printf("#                                                    #");
        gotoxy(19, 20);
        printf("#    5、游戏总分数：游戏过程中的数字相加总和。       #");
        gotoxy(19, 21);
        printf("#                                                    #");
        gotoxy(19, 22);
        printf("######################################################");
        cmd = _getch(); /* 接收标准输入流字符命令 */
        if (cmd == 'q')
            break;
    }
}

void explation() // 按键说明
{
    while (1)
    {
        system("cls");
        clear_screen();
        number();
        color(12);
        gotoxy(19, 8);
        printf("######################################################");
        gotoxy(19, 9);
        printf("#                                                    #");
        gotoxy(19, 10);
        printf("#                     按键说明                       #");
        gotoxy(19, 11);
        printf("#                                                    #");
        gotoxy(19, 12);
        printf("#    [W]:向上 [S]:向下 [A]:向左 [D]:向右 [Q]:退出    #");
        gotoxy(19, 13);
        printf("#                                                    #");
        gotoxy(19, 14);
        printf("######################################################");
        int cmd = _getch(); /* 接收标准输入流字符命令 */
        if (cmd == 'q')
        {
            break;
        }
    }
}

void exitSys()
{
    system("cls");
    color(11);
    printf("你确定退出游戏吗？(y/n)\n");
    do
    {
        scanf("%c", &yesorno);
        if (yesorno != 'y' && yesorno != 'Y' && yesorno != 'n' && yesorno != 'N')
        {
            printf("输入有误，请重新输入：\n");
        }
        while ((temp = getchar()) != EOF && temp != '\n'); // 清空缓冲区
    } while (yesorno != 'y' && yesorno != 'Y' && yesorno != 'n' && yesorno != 'N');

    if (yesorno == 'y' || yesorno == 'Y')
    {
        clear_screen();
        exit(0);
    }
    else if ((yesorno == 'n' || yesorno == 'N'))
    {
        while ((yesorno = getchar()) != EOF && yesorno != '\n')
            ; // 清空缓冲区
        return;
    }
}

void drawTheGameBox()
{
    number();
    color(14);
    gotoxy(19, 8);
    printf("游戏制作者：Billsheng  当前分数：%-6d  最高分：%-6d", score, best);
    gotoxy(19, 9);
    printf("------------------------------------------------------");
    gotoxy(19, 11);
    printf("┌────────────┬────────────┬────────────┬────────────┐");
    gotoxy(19, 12);
    printf("│            │            │            │            │");
    gotoxy(19, 13);
    printf("├────────────┼────────────┼────────────┼────────────┤");
    gotoxy(19, 14);
    printf("│            │            │            │            │");
    gotoxy(19, 15);
    printf("├────────────┼────────────┼────────────┼────────────┤");
    gotoxy(19, 16);
    printf("│            │            │            │            │");
    gotoxy(19, 17);
    printf("├────────────┼────────────┼────────────┼────────────┤");
    gotoxy(19, 18);
    printf("│            │            │            │            │");
    gotoxy(19, 19);
    printf("└────────────┴────────────┴────────────┴────────────┘");
    int i; 
    int j;
    int k;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (board[i][j] != 0)
            {
                if (board[i][j] == 2048 && flag == 1)
                    game_win = 1;
                for (k = 1; k < 16; k++)
                {
                    if (board[i][j] == pow(2, k))
                    {
                        zimoxu = k - 1;
                        break;
                    }
                    else if (board[i][j] >= pow(2, 15))
                    {
                        zimoxu = 14;
                        break;
                    }
                }
                gotoxy(lieweixu[j], hangweixu[i]);
                color(zimo[zimoxu]);
                printf("%4d", board[i][j]);
                color(0);
            }
        }
    }
}

void Gameplay()
{
    Replay();
    while (1)
    {
        add_num_flag = 0;
        game_over = 0;
        cmd = _getch(); /* 接收标准输入流字符命令 */
        switch (cmd)
        {
        case 'a':
        case 'A':
        case 75:
            move_left();
            break;
        case 's':
        case 'S':
        case 80:
            move_down();
            break;
        case 'w':
        case 'W':
        case 72:
            move_up();
            break;
        case 'd':
        case 'D':
        case 77:
            move_right();
            break;
        case 'q':
        case 'Q':
            color(15);
            return;
        default:
            continue;
        }
        if (score > best)
        {
            best = score;
            FILE *fp = fopen(".\\best_score.txt", "w");
            if (fp)
            {
                fwrite(&best, sizeof(best), 1, fp);
                fclose(fp);
            }
        }
        if (add_num_flag)
            add_rand_num();
        clear_screen();
        drawTheGameBox();
        if (game_win == 1)
        {
            color(14);
            gotoxy(19, 21);
            printf("--------★★★恭喜你获胜！★★★----------");
            gotoxy(19, 22);
            printf("--------★★★恭喜你获胜！★★★----------");
            gotoxy(19, 23);
            printf("--------★★★恭喜你获胜！★★★----------");
            gotoxy(19, 24);
            printf("-------按任意键继续玩，争取更高分！-------\n");
            game_win = 0;
            flag = 0;
            system("pause");
            system("cls");
            drawTheGameBox();
        }
        if (get_null_count() == 0)
            check_game_over();
        if (game_over)
        {
            color(240);
            gotoxy(19, 21);
            printf("你输了，游戏结束！是否重新开始？(y/n)");
            do
            {
                scanf("%c", &yesorno);
                if (yesorno != 'y' && yesorno != 'Y' && yesorno != 'n' && yesorno != 'N')
                {
                    printf("输入有误，请重新输入：\n");
                }
                while ((temp = getchar()) != EOF && temp != '\n') ; // 清空缓冲区
            } while (yesorno != 'y' && yesorno != 'Y' && yesorno != 'n' && yesorno != 'N');

            if (yesorno == 'y' || yesorno == 'Y')
            {
                clear_screen();
                color(15);
                return;
            }
            else if ((yesorno == 'n' || yesorno == 'N'))
            {
                while ((yesorno = getchar()) != EOF && yesorno != '\n') ;
                clear_screen();
                exit(0);
            }
        }
    }
}

int get_null_count()
{
    int null_num = 0;
    int i;
    int j;
    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 4; ++j)
        {
            board[i][j] == 0 ? ++null_num : 1;
        }
    }
    return null_num;
}

/* 生成随机数 函数定义 */
void add_rand_num()
{
    srand((unsigned int)time(0));
    int location = rand() % get_null_count(); /* 确定在何处空位置生成随机数 */
    int i;
    int j;
    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 4; ++j)
        {
            /* 定位待生成的位置 */
            if (board[i][j] == 0 && location-- == 0)
            {
                board[i][j] = (rand() % 5 ? 2 : 4); /* 生成数字2或4，生成概率为4:1 */
                return;
            }
        }
    }
}

void move_left()
{
	int i,j,k;
    for (i = 0; i < 4; i++) // 逐行查看
    {
        for (j = 1, k = 0; j < 4; j++) // 逐列检查
        {
            if (board[i][j] != 0)
            {
                if (board[i][k] == board[i][j]) // 左右相等，可以合并
                {
                    score += board[i][k++] *= 2;
                    board[i][j] = 0;
                    add_num_flag = 1; // 合并则需要添加随机数
                }
                else if (board[i][k] == 0) // 左侧为0，直接移过去
                {
                    board[i][k] = board[i][j];
                    board[i][j] = 0;
                    add_num_flag = 1; // 合并则需要添加随机数
                }
                else // 左右两侧均不相等，发生碰撞
                {
                    board[i][++k] = board[i][j];
                    if (j != k) // 两个不相邻，则j位置置0
                    {
                        board[i][j] = 0;
                        add_num_flag = 1;
                    }
                }
            }
        }
    }
}

void move_right()
{
	int i,j,k;
    for (i = 0; i < 4; i++) // 逐行查看
    {
        for (j = 2, k = 3; j >= 0; j--) // 逐列检查
        {
            if (board[i][j] != 0)
            {
                if (board[i][k] == board[i][j]) // 左右相等，可以合并
                {
                    score += board[i][k--] *= 2;
                    board[i][j] = 0;
                    add_num_flag = 1; // 合并则需要添加随机数
                }
                else if (board[i][k] == 0) // 右侧为0，直接移过去
                {
                    board[i][k] = board[i][j];
                    board[i][j] = 0;
                    add_num_flag = 1; // 合并则需要添加随机数
                }
                else // 左右两侧均不相等，发生碰撞
                {
                    board[i][--k] = board[i][j];
                    if (j != k) // 两个不相邻，则j位置置0
                    {
                        board[i][j] = 0;
                        add_num_flag = 1;
                    }
                }
            }
        }
    }
}

void move_up()
{
	int i,j,k;
    for (i = 0; i < 4; i++) // 逐列查看
    {
        for (j = 1, k = 0; j < 4; j++) // 逐行检查
        {
            if (board[j][i] != 0)
            {
                if (board[k][i] == board[j][i]) // 上下相等，可以合并
                {
                    score += board[k++][i] *= 2;
                    board[j][i] = 0;
                    add_num_flag = 1; // 合并则需要添加随机数
                }
                else if (board[k][i] == 0) // 上侧为0，直接移过去
                {
                    board[k][i] = board[j][i];
                    board[j][i] = 0;
                    add_num_flag = 1; // 合并则需要添加随机数
                }
                else // 上下两侧均不相等，发生碰撞
                {
                    board[++k][i] = board[j][i];
                    if (j != k) // 两个不相邻，则j位置置0
                    {
                        board[j][i] = 0;
                        add_num_flag = 1;
                    }
                }
            }
        }
    }
}

void move_down()
{
	int i,j,k;
    for (i = 0; i < 4; i++) // 逐列查看
    {
        for (j = 2, k = 3; j >= 0; j--) // 逐行检查
        {
            if (board[j][i] != 0)
            {
                if (board[k][i] == board[j][i]) // 上下相等，可以合并
                {
                    score += board[k--][i] *= 2;
                    board[j][i] = 0;
                    add_num_flag = 1; // 合并则需要添加随机数
                }
                else if (board[k][i] == 0) // 上侧为0，直接移过去
                {
                    board[k][i] = board[j][i];
                    board[j][i] = 0;
                    add_num_flag = 1; // 合并则需要添加随机数
                }
                else // 上下两侧均不相等，发生碰撞
                {
                    board[--k][i] = board[j][i];
                    if (j != k) // 两个不相邻，则j位置置0
                    {
                        board[j][i] = 0;
                        add_num_flag = 1;
                    }
                }
            }
        }
    }
}

void Replay()
{
    game_over = 0;
    score = 0;
    srand((unsigned int)time(0));
    int n = rand() % 16;
    int i,j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            board[i][j] = (n-- ? 0 : 2);
        }
    }
    /* 读取游戏最高分数 */
    FILE *fp = fopen(".\\best_score.txt", "r");
    if (fp)
    {
        fread(&best, sizeof(best), 1, fp);
        fclose(fp);
    }
    else
    {
        fp = fopen(".\\best_score.txt", "w");
        if (fp)
        {
            fwrite(&best, sizeof(best), 1, fp);
            fclose(fp);
        }
    }
    add_rand_num();
    system("cls");
    drawTheGameBox();
}

void check_game_over()
{
	int i,j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (board[i][j] == board[i][j + 1] || board[j][i] == board[j + 1][i])
            {
                game_over = 0;
                return;
            }
        }
    }
    game_over = 1;
}

void clear_screen()
{
    COORD pos = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    CONSOLE_CURSOR_INFO info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
