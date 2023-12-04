#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <stdarg.h>
#include <ctype.h>
#include "tools.h"

//��ȡ�ļ���С
long getFileSize(FILE *fp){
	long fsize; 
	fpos_t fpos;  // ������ȡ��ǰλ��
	fgetpos(fp, &fpos);  //��ȡ��ǰλ��
	fseek(fp, 0, SEEK_END); // ���ļ�ָ���ƶ����ļ�ĩβ
	fsize = ftell(fp); // ftell() �������ص�ǰ�ļ�ָ���λ�ã����ļ��Ĵ�С 
	fsetpos(fp,&fpos);  //�ָ�֮ǰ��λ��

	return fsize;
}
// ���ܸ�ʽ���ַ����Ϳɱ�����б�����ʽ�������Ϣ���������̨��Ȼ����ͣ�����ִ�У�
// ֱ���û����������
void pause(const char *str, ...){ // *str �ɱ��βΣ���ȡ��Ϣ�ַ��� 
	va_list vl; // �洢�ɱ�����б�
	char buf[500] = {0};
	va_start(vl, str); // ��ʼ�� vl������ָ��ɱ�����б����ʼλ�� 
	// // ����ʽ���ַ��� str �Ϳɱ�����б��е�ֵ����ָ���ĸ�ʽд���ַ����� buf ��
	// ȷ����������ַ�������500 
	vsnprintf(buf, 500, str, vl); 
	va_end(vl); // �����ɱ�����Ļ�ȡ 
	printf(buf);
	getch(); // ���û������������������ͣ�����ִ��
	printf("\n");
}
/* pwd����������ڴ���׵�ַ,pwdlen�������󳤶�*/
void getpwd(char *pwd, int pwdlen){
    char ch = 0; // ��ȡ�û������ַ� 
    int i = 0; // ���������ַ����� 
    while(i<pwdlen){ // pwdlen��������󳤶�(20)������ﵽ��󳤶�ѭ������ 
        ch = getch();

        if(ch == '\r'){  //�س���������
            printf("\n");
            break;
        }
       
        if(ch=='\b' && i>0){  // ����ɾ����
            i--;
            printf("\b \b");
        }else if(isprint(ch)){  // isprint�������ɴ�ӡ�ַ�
            pwd[i] = ch;
            printf("*"); // ����̨������ʾ���� 
            i++;
        }
    }
    pwd[i] = 0; // '\0' ��ʾ�ַ������� 
}

