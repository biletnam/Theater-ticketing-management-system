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
	char *password = (char *)malloc(PASSWORD * 4 * sizeof(char));
	char str[50], c = 0, i = 0;
	do {
		while (i < 49) {
			c = getch();
			getch();//微软更新产物
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

char *get_string(int down,int up ,int judge) {//字符串获取及检查函数    down~up   字符串字节数限制
	char *str = (char *)malloc(sizeof(char)*100);// judge 开关   是否开启数字检查、汉字检查  
	scanf("%s", str);
	unsigned int flag = 1, i;
	do {
		if (judge) {//进行检查检查
			if (judge == 1) {
				for (i = 0; i < strlen(str); i++) {
					if (isdigit(str[i]) == 0) {//全为数字
						flag = 0; break;
					}
				}
			}else if (judge == 2) {
				for (i = 0; i < strlen(str); i++) {
					if (0<=str[i]&&str[i]<=255) {//汉字检查
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

date_status get_date() {//日期的获得与判断
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

time_status get_time() {//时间的获得及判断
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

data_program get_program_infomation() {//获取剧目主要信息  并进行初始化
	catch_cursor();
	data_program tem = { 0 };
	strcpy(tem.area, "未知");
	strcpy(tem.performer[0], "未知");
	strcpy(tem.performer[1], "未知");
	strcpy(tem.language, "中文");
	strcpy(tem.label, "未知");
	tem.program_rating = (program_ratings)1;
	char *str; int flag = 1, choice;
	printf("\n1.电影   2.歌剧   3.音乐会\n");
	printf("请选择剧目类型:");
	do {
		scanf("%d", &choice);
		if (choice < 1 || choice>3) {
			flag = 0;
			print_examinput();
		}
	} while (flag == 0 && (flag = 1));
	tem.program_type = (program_types)choice;
	printf("请输入剧目编号(6位数字):");
	str = get_string(6, 6, 1);
	Program *p = list.program_head;//ID查重
	do {
		p = search_program(str);
		if (p) {
			free(str);
			printf("该编号已存在\n请重新输入:");
			str = get_string(6, 6, 1);
		}
	} while (p != NULL);
	strcpy(tem.program_ID, str);
	free(str);
	printf("请输入剧目名称(15个汉字以内):");
	str = get_string(1, 30, 2);
	strcpy(tem.program_name, str);
	free(str);
	tem.program_rating == 3 ? printf("请输入指挥姓名:") : printf("请输入导演姓名:");
	str = get_string(1, 14, 0);
	strcpy(tem.director, str);
	free(str);
	printf("请输入上映日期与结束日期(year-month-day):\n");
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
	printf("请输入剧目时长(min):");
	do {
		scanf("%d", &choice);
		if (choice <= 0) {
			print_examinput();
		}
	} while (choice <= 0);
	tem.duration = choice;
	printf("请输入票价(元):");
	do {
		scanf("%d", &choice);
		if (choice <= 0) {
			print_examinput();
		}
	} while (choice <= 0);
	printf("具体信息已置为默认值\n");
	return tem;
}

void account_appeal() {//账号申诉过程

}