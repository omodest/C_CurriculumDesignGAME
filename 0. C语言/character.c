#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// �ַ������� 
void cha1(){
	char a[7]="abcde";
	char b[4]="ABC";
	strcpy (a,b); 
	// ��b��ֵ����a��a[0] = A,a[i] = B,a[2] = C ,a[3] = \0
	// a[4]��a[5]��������ַû�����޸ģ�������Ȼ��e��d 
	printf("%c",a[4]);	
}
