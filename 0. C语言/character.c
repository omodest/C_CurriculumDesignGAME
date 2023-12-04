#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 字符串函数 
void cha1(){
	char a[7]="abcde";
	char b[4]="ABC";
	strcpy (a,b); 
	// 将b的值赋给a，a[0] = A,a[i] = B,a[2] = C ,a[3] = \0
	// a[4]和a[5]这两个地址没有做修改，所以依然是e和d 
	printf("%c",a[4]);	
}
