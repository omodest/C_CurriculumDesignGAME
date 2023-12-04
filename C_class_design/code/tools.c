#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <stdarg.h>
#include <ctype.h>
#include "tools.h"

//获取文件大小
long getFileSize(FILE *fp){
	long fsize; 
	fpos_t fpos;  // 用来获取当前位置
	fgetpos(fp, &fpos);  //获取当前位置
	fseek(fp, 0, SEEK_END); // 将文件指针移动到文件末尾
	fsize = ftell(fp); // ftell() 函数返回当前文件指针的位置，即文件的大小 
	fsetpos(fp,&fpos);  //恢复之前的位置

	return fsize;
}
// 接受格式化字符串和可变参数列表，将格式化后的消息输出到控制台，然后暂停程序的执行，
// 直到用户按下任意键
void pause(const char *str, ...){ // *str 可变形参，获取消息字符串 
	va_list vl; // 存储可变参数列表
	char buf[500] = {0};
	va_start(vl, str); // 初始化 vl，将其指向可变参数列表的起始位置 
	// // 将格式化字符串 str 和可变参数列表中的值按照指定的格式写入字符数组 buf 中
	// 确保不会溢出字符串长度500 
	vsnprintf(buf, 500, str, vl); 
	va_end(vl); // 结束可变参数的获取 
	printf(buf);
	getch(); // 待用户按下任意键，用于暂停程序的执行
	printf("\n");
}
/* pwd保存密码的内存的首地址,pwdlen密码的最大长度*/
void getpwd(char *pwd, int pwdlen){
    char ch = 0; // 获取用户输入字符 
    int i = 0; // 计算输入字符数量 
    while(i<pwdlen){ // pwdlen是密码最大长度(20)，密码达到最大长度循环结束 
        ch = getch();

        if(ch == '\r'){  //回车结束输入
            printf("\n");
            break;
        }
       
        if(ch=='\b' && i>0){  // 按下删除键
            i--;
            printf("\b \b");
        }else if(isprint(ch)){  // isprint检查输入可打印字符
            pwd[i] = ch;
            printf("*"); // 控制台密文显示密码 
            i++;
        }
    }
    pwd[i] = 0; // '\0' 表示字符串结束 
}

