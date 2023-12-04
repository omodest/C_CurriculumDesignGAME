#include <stdio.h>
#include <stdlib.h>
// 运算符重载
//对已有的运算符重新进行定义，赋予其另一种功能，简化操作 让已有的运算符 适应不同的数据类型。
// 自增运算符 
void operator1(){
	int i;
	scanf("%d",&i);
	if(i-- < 5) // 先比较，然后再自减 
		printf("%d",i);
	else 
		printf("%d",i++); // 先输出然后再自增。 
} 
// 逻辑或 
void operator2(){
	int x = 12, y = 15, z ;
	z = x || (y-=x); // 逻辑或：当左边是true时，整个表达式一定为1，也就不会往右边执行，所以y的值不变。 
	printf("%d %d",z,y); 
} 
// 运算符 
void operator3(){
	int a = 12;
    a += a -= a*a; 
    printf("%d",a); // 264
} 
// 逗号运算符 
void operator4(){
	int a = 5, b;
	b = a > 3 && 0, a++; // 逗号运算符号优先级最低，所以先赋值0给b 
	printf("%d",b); 
} 

