#include"stdafx.h"
#include"statements.h"

void import_account() {//读入账号信息
	FILE *fp = fopen(".\\account.txt","r");
	if (fp == NULL) {
		print_re();
		exit(1);
	}
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
		p->element = tem;//每成功读取一组数据做一个结点，连接到链表上
		p->next = list.account_tail->next;
		p->pre = list.account_tail;
		list.account_tail->next = p;
		list.account_tail = p;
	}
	fclose(fp);
}

void import_program() {//从文件读入剧目信息存储为链表
	FILE *fp = fopen(".\\program.txt", "r");
	if (fp == NULL) {
		print_re();
		exit(1);
	}
	data_program tem = {0};
	int type,rating;
	while (fscanf(fp, "%d %s %d %d %s %s %s",&tem.program_ID, tem.program_name, &type, &rating, tem.director, tem.performer[0], tem.performer[1])==7&&\
		fscanf(fp,"%d-%d-%d %d-%d-%d", &tem.start_date.year, &tem.start_date.month, &tem.start_date.day, &tem.end_date.year, &tem.end_date.month, &tem.end_date.day)== 6\
		&&fscanf(fp,"%d %s %s %s %d %d", &tem.duration, tem.label, tem.area, tem.language, &tem.price, &tem.cost)==6){
		tem.program_type = (program_types)type,tem.program_rating=(program_ratings)rating;
		Program *p = (Program *)malloc(sizeof(Program));
		if (p == NULL) {
			print_mallocX();
			go_on();
			exit(1);
		}
		p->element = tem;
		p->next = list.program_tail->next;
		p->pre = list.program_tail;
		list.program_tail->next = p;
		list.program_tail = p;
	}
	fclose(fp);
}

void import_studio_and_seat() {//导入放映厅及座位信息
	FILE *fp = fopen(".\\studio.txt", "r");
	if (fp == NULL) {
		print_re();
			exit(1);
	}
	data_studio tem;
	int i, j,t,cnt=1;//cnt用来计算seat_ID
	while (fscanf(fp, "%d %s %d %d", &tem.studio_ID, tem.studio_name, &tem.seatx,&tem.seaty) != EOF) {
		Studio *p = (Studio *)malloc(sizeof(Studio));
		if (p == NULL) {
			print_mallocX();
			exit(1);
		}
		p->element = tem;
		p->next = list.studio_tail->next;
		p->pre = list.studio_tail;
		list.studio_tail->next = p;
		list.studio_tail = p;
		//座位的读取与处理
		for (i = 1; i <= p->element.seatx; i++) {
			for (j = 1; j <= p->element.seaty; j++) {
				Seat *k = (Seat *)malloc(sizeof(Seat));
				if (k == NULL) {
					print_mallocX();
					exit(1);
				}
				k->seatx = i, k->seaty = j,k->seat_ID=cnt++,k->stduio_ID=p->element.studio_ID;
				fscanf(fp, "%d", &t);
				k->seat_condition = (seat_conditions)t;
				k->next = list.seat_tail->next;
				k->pre = list.seat_tail;
				list.seat_tail->next = k;
				list.seat_tail = k;
			}
		}
	}
}