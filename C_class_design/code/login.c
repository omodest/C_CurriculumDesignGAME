#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "common.h"
#include "stu.h"

//��ʼ��
void init(){
	STU stu;
	NODE *preNode = NULL, *thisNode = NULL;
	long fileSize;
	char buffer[32], pwdMD5[33];
	int readCount, i;

	// �����Զ�д����ʽ���ļ�(����ļ������ڻᴴ��)�������ʧ�ܾͱ��� 
	if( (fp=fopen(FILENAME, "rb+")) == NULL && (fp=fopen(FILENAME, "wb+")) == NULL ){
		pause("Error on open %s file!", FILENAME);
		exit(EXIT_FAILURE);
	}
	// ��ȡ�ļ������ݴ�С���þ��������Ĳ��� 
	fileSize = getFileSize(fp);

	if(fileSize == 0){  // ����ʹ�����ʱ��Ҫ��������
		setPwd(PWD_SET);
	}else if(!checkPwd(PWD_CHECK)){  // �ٴ�ʹ�����ʱ��Ҫȷ������
		exit(EXIT_SUCCESS);
	}

	if(getFileSize(fp)>32){  //����ļ��������ݣ��͹�������
		//�Ƚ����ݽ��ܲ����浽��ʱ�ļ�
		fpTemp = tmpfile();
		fseek(fp, 32, SEEK_SET);
		while( (readCount=fread(buffer, 1, pwdLen, fp)) > 0 ){
			for(i=0; i<readCount; i++){
				buffer[i] ^= pwdCurrent[i];
			}
			fwrite(buffer, 1, readCount, fpTemp);
		}
		fflush(fpTemp);

		//��ͨ����ʱ�ļ��е����ݹ�������
		fseek(fpTemp, 0, SEEK_SET);
		while(fread(&stu, 1, sizeof(STU), fpTemp)){
			thisNode = (NODE*)malloc(sizeof(NODE));
			thisNode->data = stu;
			thisNode->next = NULL;
			if(preNode==NULL){  //�����һ���ڵ�
				header.link = thisNode;
			}else{  //���ǵ�һ���ڵ�
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

//���û��޸�����
void setPwd(int flag){
	char pwdOld[PWD_LEN+1], pwdNew1[PWD_LEN+1], pwdNew2[PWD_LEN+1], pwdNewMD5[33];

	if(flag == PWD_SET){
		printf("Ϊ�˱�֤���ݰ�ȫ���״�ʹ�ñ�������������룡\n");
	}else if(flag==PWD_ALTER && !checkPwd(PWD_ALTER)){  //У��ԭ������ʧ��
		exit(EXIT_SUCCESS);
	}

	do{
		if(flag == PWD_SET){
			printf("���������룺");
			getpwd(pwdNew1, PWD_LEN);
			printf("��ȷ�����룺");
			getpwd(pwdNew2, PWD_LEN);
		}else if(flag == PWD_ALTER){
			printf("�����������룺");
			getpwd(pwdNew1, PWD_LEN);
			printf("��ȷ�������룺");
			getpwd(pwdNew2, PWD_LEN);
		}

		if(strcmp(pwdNew1, pwdNew2) == 0){
			MD5((unsigned char*)pwdNew1, (unsigned char*)pwdNewMD5);
			fseek(fp, 0, SEEK_SET);
			fwrite(pwdNewMD5, 32, 1, fp);
			if(flag == PWD_SET){
				pause("��ʾ���������óɹ�����������������...");
				strcpy(pwdCurrent, pwdNew1);
				pwdLen = strlen(pwdCurrent);
			}else if(flag == PWD_ALTER){
				pause("��ʾ�������޸ĳɹ��������ⷵ��...");
				strcpy(pwdCurrent, pwdNew1);
				pwdLen = strlen(pwdCurrent);
				updateFile();
			}
			break;
		}else{
			pause("�����������벻һ�£�����������...");
		}
	}while(1);
}

int checkPwd(int flag){
	char pwd[PWD_LEN+1], pwdFile[33] = {0}, pwdMD5[33];
	int i /*ѭ�����Ʊ���*/, n /*����������*/;

	for(i=0; i<PWD_ERROR_TIMES; i++){
		if(flag == PWD_CHECK){
			printf("���������룺");
		}else if(flag == PWD_ALTER){
			printf("����������룺");
		}
		getpwd(pwd, PWD_LEN);
		MD5((unsigned char*)pwd, (unsigned char*)pwdMD5);
		fseek(fp, 0, SEEK_SET);
		fread(pwdFile, 32, 1, fp);  //��ȡ�ļ��е�����
		if(strcmp(pwdFile, pwdMD5)==0){
			strcpy(pwdCurrent, pwd);
			pwdLen = strlen(pwdCurrent);
			break;
		}else{
			n = PWD_ERROR_TIMES - i - 1;
			if(n == 0){
				pause("��ʾ���������������࣬���򼴽��˳��������������...");
				return 0;
			}else{
				pause("��ʾ�������������������%d�λ��ᣡ���������������...", n);
			}
		}
	}

	return 1;
}
