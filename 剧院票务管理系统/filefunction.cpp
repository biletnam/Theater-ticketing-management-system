#include"stdafx.h"
#include"statements.h"

void import_account() {//�����˺���Ϣ
	FILE *fp = fopen(".\\account.txt","r");
	if (fp == NULL) {
		print_re();
		exit(1);
	}
	else {
		int t;
		data_account tem;
		while (fscanf(fp,"%d %s %s %d",&tem.UID,tem.username,tem.password,&t)!=EOF) {
			tem.user_type = user_types(t);
			Account *p = (Account *)malloc(sizeof(Account));
			if (p == NULL) {
				print_mallocX();
				go_on();
				exit(1);
			}
			p->element = tem;//ÿ�ɹ���ȡһ��������һ����㣬���ӵ�������
			p->next = list.account_tail->next;//��������
			p->pre = list.account_tail;
			list.account_tail->next = p;
			list.account_tail = p;
		}
	}
	fclose(fp);
}