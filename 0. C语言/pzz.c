#include <stdio.h>
#include <stdlib.h>
// �����ָ�� 
void pArray(){
	int a[10] = {1,2,3,4,5,6,7,8,9,10};
	int *p = a; // �������׵�ֵַ��ָ�� 
	printf("%d\n",*(a+6)); // ����a+6�ȼ�p+6,�������7  
	printf("%d\n",p[6]); //   p��a�����������ֵַ���ԣ�����ʹ��p[6]��ʹ��a[6]�ǵȼ۵ģ����Ϊ7 
}
// �ַ�ָ��
void pChararray(){
	// str�Ƕ�ά���飬Ҳ���Կ����ɶ�άָ�룻
	// ָ��strpָ����һ��ָ�룬����strp��ָ�����飬����strpҲ�Ƕ�ά���顣 
	char str[4][12] = {"aa", "bbb", "cccc", "d"}, *strp[4];
	int i;
	for (i = 0; i < 4; i++)
	    strp[i] = str[i];
	// str��strp���Ƕ���ָ�룬������Ҫʹ��*ȡһ�ε�ַ����ʹ���������ܻ�ȡһάָ�룬Ҳ�����ַ����� 
	printf("%s %s %s",str[0],* strp,strp[3]);
} 
