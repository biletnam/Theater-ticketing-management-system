#include"stdafx.h"
#include"statements.h"

int sign_judge() {//��½�жϼ���ȡ�˻���Ϣ   return flag   flag��ʾ�˻�����  
	show_sign();
	int cnt=0,flag=0;
	set_position(39, 8);
	char *username = username_get(0);
	set_position(39, 10);
	char *password = password_get(0);
	Account *p = list.account_head->next;
	for (p; p; p = p->next) {
		if (strcmp(username, p->element.username) == 0) {
			break;
		}
	}if (p != NULL) {//�û�������
		if (strcmp(password, p->element.password) == 0) {//������ȷ
			//������ȷ���˻���Ϣд����ǰ�˻���Ϣ
			strcpy(PRESENT.username, username);
			strcpy(PRESENT.password, password);
			PRESENT.user_type = p->element.user_type;
			flag = PRESENT.user_type;
		}
		else {
			system("cls");
			set_position(25, 10);
			SetColor(12, 0);
			printf("�����Ӵ");
			Sleep(1500);
		}
	}
	else {//�û���������
		system("cls");
		set_position(25, 10);
		SetColor(12, 0);
		printf("û������˺�Ӵ");
		Sleep(1500);
	}
	return flag;//flag==0  ��ʾ��¼ʧ�ܣ��������Ͳμ�user_types
}

char *username_get(int judge) {//�û����Ļ�ȡ    judge!=0ʱ���������� 
	char *str=(char *)malloc(NAME*5);
	str[0] = '\0';
	scanf("%s", str);
	if(judge)
	while (strlen(str) > 14 || strlen(str) < 4) {
		print_examinput();
		scanf("%s", str);
	}
	return str;
}

char *password_get(int judge) {//��������Ļ�ȡ        judge!=0ʱ����������
	char *password = (char *)malloc(PASSWORD * 4 * sizeof(char));
	char str[50], c = 0, i = 0;
	do {
		while (i < 49) {
			c = getch();
			getch();//΢����²���
			if (c != 8 && c != '\r') {
				str[i++] = c;
				printf("*");
			}
			else if (c == 8 && i > 0) {
				printf("\b \b");
				i--;
			}
			else if (c == '\r') {
				break;
			}
		}
		str[i] = '\0';//һ�������ȡ
	} while ((strlen(str)<6||strlen(str)>12)&&judge);
	strcpy(password,str);
	return password;
}

char *get_string(int down,int up ,int judge) {//�ַ�����ȡ����麯��    down~up   �ַ����ֽ�������
	char *str = (char *)malloc(sizeof(char)*100);// judge ����   �Ƿ������ּ�顢���ּ��  
	scanf("%s", str);
	unsigned int flag = 1, i;
	do {
		if (judge) {//���м����
			if (judge == 1) {
				for (i = 0; i < strlen(str); i++) {
					if (isdigit(str[i]) == 0) {//ȫΪ����
						flag = 0; break;
					}
				}
			}else if (judge == 2) {
				for (i = 0; i < strlen(str); i++) {
					if (0<=str[i]&&str[i]<=255) {//���ּ��
						flag = 0; break;
					}
				}
			}
		}
		while (flag == 0 || ((int)strlen(str) < down || (int)strlen(str) > up)) {
			print_examinput();
			scanf("%s", str);
		}
	} while ((flag == 0) && (flag = 1));
	return str;
}

date_status get_date() {//���ڵĻ�����ж�
	date_status date = {0,0,0};
	int flag = 1,y,m,d;
	do {
		scanf("%d-%d-%d", &y, &m, &d);
		if (y < 2018 || y>2050) {
			flag = 0;
		}
		if (1 > m || m > 12) {
			flag = 0;
		}
		if (1 > d || d > 31) {
			flag = 0;
		}
		if (m == 2) {
			if (d > 29) {
				flag = 0;
			}
			if ((d == 29) && (y % 4 != 0)) {
				flag = 0;
			}
		}
		if ((m != 2) && (m % 2 == 0 && d > 30)) {
			flag = 0;
		}
		if (flag == 0) {
			print_examinput();
		}
	} while (flag == 0 && (flag = 1));
	date.year = y, date.month = m, date.day = d;
	return date;
}

time_status get_time() {//ʱ��Ļ�ü��ж�
	time_status time = {0,0};
	int h, m,flag=1;
	do {
		scanf("%d:%d", &h, &m);
		if (h < 0 || h>23 || m < 0 || m>59) {
			flag = 0;
			print_examinput();
		}
	} while (flag == 0 && (flag = 1));
	time.hour = h, time.minute = m;
	return time;
}

data_program get_program_infomation() {//��ȡ��Ŀ��Ҫ��Ϣ  �����г�ʼ��
	catch_cursor();
	data_program tem = { 0 };
	strcpy(tem.area, "δ֪");
	strcpy(tem.performer[0], "δ֪");
	strcpy(tem.performer[1], "δ֪");
	strcpy(tem.language, "����");
	strcpy(tem.label, "δ֪");
	tem.program_rating = (program_ratings)1;
	char *str; int flag = 1, choice;
	printf("\n1.��Ӱ   2.���   3.���ֻ�\n");
	printf("��ѡ���Ŀ����:");
	do {
		scanf("%d", &choice);
		if (choice < 1 || choice>3) {
			flag = 0;
			print_examinput();
		}
	} while (flag == 0 && (flag = 1));
	tem.program_type = (program_types)choice;
	printf("�������Ŀ���(6λ����):");
	str = get_string(6, 6, 1);
	Program *p = list.program_head;//ID����
	do {
		p = search_program(str);
		if (p) {
			free(str);
			printf("�ñ���Ѵ���\n����������:");
			str = get_string(6, 6, 1);
		}
	} while (p != NULL);
	strcpy(tem.program_ID, str);
	free(str);
	printf("�������Ŀ����(15����������):");
	str = get_string(1, 30, 2);
	strcpy(tem.program_name, str);
	free(str);
	tem.program_rating == 3 ? printf("������ָ������:") : printf("�����뵼������:");
	str = get_string(1, 14, 0);
	strcpy(tem.director, str);
	free(str);
	printf("��������ӳ�������������(year-month-day):\n");
	do {
		tem.start_date = get_date();
		tem.end_date = get_date();
		char date1[15], date2[15];
		sprintf(date1, "%d-%d-%d", tem.start_date.year, tem.start_date.month, tem.start_date.day);
		sprintf(date2, "%d-%d-%d", tem.end_date.year, tem.end_date.month, tem.end_date.day);
		if (strcmp(date2, date1) <= 0) {
			flag = 0;
			print_examinput();
		}
	} while (flag == 0 && (flag = 1));
	printf("�������Ŀʱ��(min):");
	do {
		scanf("%d", &choice);
		if (choice <= 0) {
			print_examinput();
		}
	} while (choice <= 0);
	tem.duration = choice;
	printf("������Ʊ��(Ԫ):");
	do {
		scanf("%d", &choice);
		if (choice <= 0) {
			print_examinput();
		}
	} while (choice <= 0);
	printf("������Ϣ����ΪĬ��ֵ\n");
	return tem;
}

void account_appeal() {//�˺����߹���

}