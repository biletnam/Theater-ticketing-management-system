#include"stdafx.h"
#include"statements.h"

int sign_judge() {//登陆判断及获取账户信息   return flag   flag表示账户类型  
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
	}if (p != NULL) {//用户名存在
		if (strcmp(password, p->element.password) == 0) {//密码正确
			//密码正确将账户信息写至当前账户信息
			strcpy(PRESENT.username, username);
			strcpy(PRESENT.password, password);
			PRESENT.user_type = p->element.user_type;
			flag = PRESENT.user_type;
		}
		else {
			system("cls");
			set_position(25, 10);
			SetColor(12, 0);
			printf("口令不对哟");
			Sleep(1500);
		}
	}
	else {//用户名不存在
		system("cls");
		set_position(25, 10);
		SetColor(12, 0);
		printf("没有这个账号哟");
		Sleep(1500);
	}
	return flag;//flag==0  表示登录失败，其他类型参见user_types
}

char *username_get(int judge) {//用户名的获取    judge!=0时进行输入检查 
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

char *password_get(int judge) {//密码输入的获取        judge!=0时进行输入检查
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
		str[i] = '\0';//一次密码获取
	} while ((strlen(str)<6||strlen(str)>12)&&judge);
	strcpy(password,str);
	return password;
}