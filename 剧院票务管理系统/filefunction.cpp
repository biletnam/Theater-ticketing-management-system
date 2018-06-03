#include"stdafx.h"
#include"statements.h"
///////////////////////////////////////////import

void import_account() {//读入账号信息
	FILE *fp = fopen(".\\account.txt","r");
	if (fp == NULL) {
		print_re();
		exit(1);
	}
	int t;
	data_account tem;
	while (fscanf(fp,"%s %s %s %d",tem.UID,tem.username,tem.password,&t)!=EOF) {
		tem.user_type = user_types(t);
		Account *p = (Account *)malloc(sizeof(Account));
		exam_mallocX(p);
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
	while (fscanf(fp, "%s %s %d %d %s %s %s",tem.program_ID, tem.program_name, &type, &rating, tem.director, tem.performer[0], tem.performer[1])==7&&\
		fscanf(fp,"%d-%d-%d %d-%d-%d", &tem.start_date.year, &tem.start_date.month, &tem.start_date.day, &tem.end_date.year, &tem.end_date.month, &tem.end_date.day)== 6\
		&&fscanf(fp,"%d %s %s %s %d %d", &tem.duration, tem.label, tem.area, tem.language, &tem.price, &tem.cost)==6){
		tem.program_type = (program_types)type,tem.program_rating=(program_ratings)rating;
		Program *p = (Program *)malloc(sizeof(Program));
		exam_mallocX(p);
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
	int i, j, t;
	while (fscanf(fp, "%s %s %d %d", tem.studio_ID, tem.studio_name, &tem.seatx,&tem.seaty) != EOF) {
		Studio *p = (Studio *)malloc(sizeof(Studio));
		exam_mallocX(p);
		p->element = tem;
		p->element.seat_head = (Seat *)malloc(sizeof(Seat));
		exam_mallocX(p->element.seat_head);
		p->element.seat_head->pre = p->element.seat_head->next = NULL;//次链表初始化
		p->element.seat_tail = p->element.seat_head;
		p->next = list.studio_tail->next;
		p->pre = list.studio_tail;
		list.studio_tail->next = p;
		list.studio_tail = p;
		//座位的读取与处理
		for (i = 1; i <= p->element.seatx; i++) {
			for (j = 1; j <= p->element.seaty; j++) {
				Seat *k = (Seat *)malloc(sizeof(Seat));
				exam_mallocX(k);
				k->seatx = i, k->seaty = j,k->stduio_ID=atoi(p->element.studio_ID);
				fscanf(fp, "%d", &t);
				k->seat_condition = (seat_conditions)t;
				k->next = p->element.seat_tail->next;
				k->pre = p->element.seat_tail;
				p->element.seat_tail->next = k;
				p->element.seat_tail = k;
			}
		}
	}
}

//////////////////////////////////////////save

void save_program() {//保存剧目信息到文件
	FILE *fp = fopen(".\\program.txt","w+");
	if (fp == NULL) {
		print_re();
		exit(1);
	}
	Program *p = list.program_head->next;
	for (p; p; p = p->next) {
		fprintf(fp, "%s %s %d %d %s %s %s %d-%d-%d \
%d-%d-%d %d %s %s %s %d %d\n", p->element.program_ID\
		,p->element.program_name, p->element.program_type\
		, p->element.program_rating, p->element.director, p->element.performer[0]\
		, p->element.performer[1],p->element.start_date.year, p->element.start_date\
		.month, p->element.start_date.day, p->element.end_date.year, p->element.end_date.\
		month, p->element.end_date.day, p->element.duration, p->element.label, \
		p->element.area, p->element.language, p->element.price, p->element.cost);
	}
	fclose(fp);
}

void save_studio_and_seat() {//保存放映厅及其座位数据
	FILE *fp = fopen(".\\studio.txt", "w+");
	if (fp == NULL) {
		
	}
}