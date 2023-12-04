#include <stdio.h>
#include <stdlib.h>
// 数组和指针 
void pArray(){
	int a[10] = {1,2,3,4,5,6,7,8,9,10};
	int *p = a; // 将数组首地址值给指针 
	printf("%d\n",*(a+6)); // 这里a+6等价p+6,结果都是7  
	printf("%d\n",p[6]); //   p和a都是是数组地址值所以，这样使用p[6]和使用a[6]是等价的；结果为7 
}
// 字符指针
void pChararray(){
	// str是二维数组，也可以看出成二维指针；
	// 指针strp指针是一级指针，但是strp是指针数组，所以strp也是二维数组。 
	char str[4][12] = {"aa", "bbb", "cccc", "d"}, *strp[4];
	int i;
	for (i = 0; i < 4; i++)
	    strp[i] = str[i];
	// str和strp都是二级指针，所以需要使用*取一次地址或者使用索引就能获取一维指针，也就是字符串。 
	printf("%s %s %s",str[0],* strp,strp[3]);
} 
