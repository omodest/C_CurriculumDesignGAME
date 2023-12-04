#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "common.h"
#include "stu.h"

//初始化
void init(){
	STU stu;
	NODE *preNode = NULL, *thisNode = NULL;
	long fileSize;
	char buffer[32], pwdMD5[33];
	int readCount, i;

	// 尝试以读写的形式打开文件(如果文件不存在会创建)，如果打开失败就报错。 
	if( (fp=fopen(FILENAME, "rb+")) == NULL && (fp=fopen(FILENAME, "wb+")) == NULL ){
		pause("Error on open %s file!", FILENAME);
		exit(EXIT_FAILURE);
	}
	// 获取文件中数据大小，用决定后续的操作 
	fileSize = getFileSize(fp);

	if(fileSize == 0){  // 初次使用软件时需要设置密码
		setPwd(PWD_SET);
	}else if(!checkPwd(PWD_CHECK)){  // 再次使用软件时需要确认密码
		exit(EXIT_SUCCESS);
	}

	if(getFileSize(fp)>32){  //如果文件中有数据，就构建链表
		//先将数据解密并保存到临时文件
		fpTemp = tmpfile();
		fseek(fp, 32, SEEK_SET);
		while( (readCount=fread(buffer, 1, pwdLen, fp)) > 0 ){
			for(i=0; i<readCount; i++){
				buffer[i] ^= pwdCurrent[i];
			}
			fwrite(buffer, 1, readCount, fpTemp);
		}
		fflush(fpTemp);

		//再通过临时文件中的数据构建链表
		fseek(fpTemp, 0, SEEK_SET);
		while(fread(&stu, 1, sizeof(STU), fpTemp)){
			thisNode = (NODE*)malloc(sizeof(NODE));
			thisNode->data = stu;
			thisNode->next = NULL;
			if(preNode==NULL){  //链表第一个节点
				header.link = thisNode;
			}else{  //不是第一个节点
				preNode->next = thisNode;
			}
			preNode = thisNode;
			header.num++;
		}
		fclose(fpTemp);
	}else{
		header.num = 0;
		header.link = NULL;
	}
}

//设置或修改密码
void setPwd(int flag){
	char pwdOld[PWD_LEN+1], pwdNew1[PWD_LEN+1], pwdNew2[PWD_LEN+1], pwdNewMD5[33];

	if(flag == PWD_SET){
		printf("为了保证数据安全，首次使用本软件请设置密码！\n");
	}else if(flag==PWD_ALTER && !checkPwd(PWD_ALTER)){  //校验原有密码失败
		exit(EXIT_SUCCESS);
	}

	do{
		if(flag == PWD_SET){
			printf("请输入密码：");
			getpwd(pwdNew1, PWD_LEN);
			printf("请确认密码：");
			getpwd(pwdNew2, PWD_LEN);
		}else if(flag == PWD_ALTER){
			printf("请输入新密码：");
			getpwd(pwdNew1, PWD_LEN);
			printf("请确认新密码：");
			getpwd(pwdNew2, PWD_LEN);
		}

		if(strcmp(pwdNew1, pwdNew2) == 0){
			MD5((unsigned char*)pwdNew1, (unsigned char*)pwdNewMD5);
			fseek(fp, 0, SEEK_SET);
			fwrite(pwdNewMD5, 32, 1, fp);
			if(flag == PWD_SET){
				pause("提示：密码设置成功！按任意键进入软件...");
				strcpy(pwdCurrent, pwdNew1);
				pwdLen = strlen(pwdCurrent);
			}else if(flag == PWD_ALTER){
				pause("提示：密码修改成功！按任意返回...");
				strcpy(pwdCurrent, pwdNew1);
				pwdLen = strlen(pwdCurrent);
				updateFile();
			}
			break;
		}else{
			pause("两次输入密码不一致，请重新输入...");
		}
	}while(1);
}

int checkPwd(int flag){
	char pwd[PWD_LEN+1], pwdFile[33] = {0}, pwdMD5[33];
	int i /*循环控制变量*/, n /*密码错误次数*/;

	for(i=0; i<PWD_ERROR_TIMES; i++){
		if(flag == PWD_CHECK){
			printf("请输入密码：");
		}else if(flag == PWD_ALTER){
			printf("请输入旧密码：");
		}
		getpwd(pwd, PWD_LEN);
		MD5((unsigned char*)pwd, (unsigned char*)pwdMD5);
		fseek(fp, 0, SEEK_SET);
		fread(pwdFile, 32, 1, fp);  //读取文件中的密码
		if(strcmp(pwdFile, pwdMD5)==0){
			strcpy(pwdCurrent, pwd);
			pwdLen = strlen(pwdCurrent);
			break;
		}else{
			n = PWD_ERROR_TIMES - i - 1;
			if(n == 0){
				pause("提示：密码错误次数过多，程序即将退出！按任意键继续...");
				return 0;
			}else{
				pause("提示：密码输入错误，您还有%d次机会！按任意键重新输入...", n);
			}
		}
	}

	return 1;
}
