#include <stdio.h>
#include <stdlib.h>
// ���������
//�����е���������½��ж��壬��������һ�ֹ��ܣ��򻯲��� �����е������ ��Ӧ��ͬ���������͡�
// ��������� 
void operator1(){
	int i;
	scanf("%d",&i);
	if(i-- < 5) // �ȱȽϣ�Ȼ�����Լ� 
		printf("%d",i);
	else 
		printf("%d",i++); // �����Ȼ���������� 
} 
// �߼��� 
void operator2(){
	int x = 12, y = 15, z ;
	z = x || (y-=x); // �߼��򣺵������trueʱ���������ʽһ��Ϊ1��Ҳ�Ͳ������ұ�ִ�У�����y��ֵ���䡣 
	printf("%d %d",z,y); 
} 
// ����� 
void operator3(){
	int a = 12;
    a += a -= a*a; 
    printf("%d",a); // 264
} 
// ��������� 
void operator4(){
	int a = 5, b;
	b = a > 3 && 0, a++; // ��������������ȼ���ͣ������ȸ�ֵ0��b 
	printf("%d",b); 
} 

