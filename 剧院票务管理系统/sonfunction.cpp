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
	char *password = (char *)malloc(PASSWORD * 2 * sizeof(char));
	char str[20], c = 0, i = 0;
	do {
		while (i < 49) {
			c = _getch();
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