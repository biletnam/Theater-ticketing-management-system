#include"stdafx.h"
#include"statements.h"
///////////////////////////////////////////import

void import_key() {//导入主键信息到链表
	FILE *fp = fopen("key.txt", "r");
	if (fp == NULL) {
		print_re();
		exit(1);
	}
	long key;int type;
	while (fscanf(fp, "%ld %d", &key, &type) != EOF) {
		Key *p = (Key *)malloc(sizeof(Key));
		p->next = list.key_tail->next;
		p->pre = list.key_tail;
		p->key = key; p->type = type;
		list.key_tail->next = p;
		list.key_tail = p;
	}
	fclose(fp);
}

void import_account() {//导入账号信息到链表
	int cnt = 0;
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
		cnt++;//计数
	}
	list.account_head->element.contributions = cnt;
	fclose(fp);
}

void import_program() {//导入剧目信息到链表
	FILE *fp = fopen(".\\program.txt", "r");
	if (fp == NULL) {
		print_re();
		exit(1);
	}
	data_program tem = {0};
	int type, rating, cnt = 0;
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
		cnt++;
	}
	list.program_head->element.cost = cnt;//头结点计数
	fclose(fp);
}

void import_studio_and_seat() {//导入放映厅及座位信息到链表
	FILE *fp = fopen(".\\studio.txt", "r");
	if (fp == NULL) {
		print_re();exit(1);
	}
	data_studio tem;
	int i, j, t, ID;
	list.studio_head->element.seatx = 0;
	while (fscanf(fp, "%s %s %d %d %d", tem.studio_ID, tem.studio_name, &tem.seatx,&tem.seaty,&tem.seatsum) != EOF) {
		Studio *p = (Studio *)malloc(sizeof(Studio)); int cnt = 0;
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
		list.studio_head->element.seatx++;//计数
		//座位的读取与处理
		ID = atoi(p->element.studio_ID);
		for (i = 1; i <= p->element.seatx; i++) {
			for (j = 1; j <= p->element.seaty; j++) {
				Seat *k = (Seat *)malloc(sizeof(Seat));
				exam_mallocX(k);
				k->seatx = i, k->seaty = j,k->stduio_ID=ID;
				fscanf(fp, "%d", &t); if (t == 1)cnt++;
				k->seat_condition = (seat_conditions)t;
				k->next = p->element.seat_tail->next;
				k->pre = p->element.seat_tail;
				p->element.seat_tail->next = k;
				p->element.seat_tail = k;
			}
		}if (p->element.seatsum != cnt) { printf("座位文件校验错误\n"); print_re(); }
	}
	fclose(fp);
}

void import_plan_and_ticket() {//导入演出计划信息到链表
	FILE *fp = fopen(".\\plan.txt", "r");
	if (fp == NULL) {
		print_re();exit(1);
	}
	data_plan tem; int i;
	while (fscanf(fp, "%ld %d %d %d-%d-%d %d:%d %d",&tem.plan_ID,&tem.program_ID,&tem.studio_ID,\
&tem.date.year,&tem.date.month,&tem.date.day,&tem.time.hour,&tem.time.minute,&tem.ticketnum) != EOF) {
		Plan *p = (Plan *)malloc(sizeof(Plan)); exam_mallocX(p);
		p->element = tem;
		p->element.ticket_head = (Ticket *)malloc(sizeof(Ticket)); exam_mallocX(p->element.ticket_head);
		p->element.ticket_head->pre = p->element.ticket_head->next = NULL;
		p->element.ticket_tail = p->element.ticket_head;//票的链表初始化
		for (i = 1; i <= p->element.ticketnum; i++) {
			Ticket *k = (Ticket *)malloc(sizeof(Ticket)); exam_mallocX(k); int t;
			fscanf(fp, "%ld %d %d %d %d", &k->ticket_ID,&k->seatx,&k->seaty,&k->price,&t);
			k->ticket_status = (ticket_statuses)t;
			k->next = p->element.ticket_tail->next; k->pre = p->element.ticket_tail;
			p->element.ticket_tail->next = k; p->element.ticket_tail = k;
		}
		p->next = list.plan_tail->next; p->pre = list.plan_tail;
		list.plan_tail->next = p; list.plan_tail = p;
	}
	fclose(fp);
}

//////////////////////////////////////////save

void save_key() {//保存主键信息到文件
	FILE *fp = fopen("key.txt", "w");
	if (fp == NULL) {
		print_re();exit(1);
	}
	Key *p = list.key_head->next;
	for (p; p; p = p->next) {
		fprintf(fp, "%ld %d\n", p->key, p->type);
	}
	fclose(fp);
}

void save_program() {//保存剧目信息到文件
	FILE *fp = fopen(".\\program.txt","w+");
	if (fp == NULL) {
		print_re();exit(1);
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
	int i, j;
	FILE *fp = fopen(".\\studio.txt", "w+");
	if (fp == NULL) {
		print_re();
		exit(1);
	}
	Studio *p = list.studio_head->next;
	Seat *k = NULL;
	for (p; p; p = p->next) {
		fprintf(fp, "%s %s %d %d %d\n", p->element.studio_ID, p->element.studio_name, p->element.seatx, p->element.seaty,p->element.seatsum);
		k = p->element.seat_head->next;
		for (i = 1; i <= p->element.seatx; i++) {
			for (j = 1; j <= p->element.seaty; j++) {
				/*if (k->seatx > p->element.seatx || k->seaty > p->element.seaty) {
					j--,k = k->next; continue; }*/
				fprintf(fp, "%d ", k->seat_condition);
				k = k->next;
			}fprintf(fp, "\n");
		}
	}
	fclose(fp);
}

void save_plan_and_ticket() {//保存演出计划及票
	FILE *fp = fopen("plan.txt", "w");
	if (fp == NULL) {
		print_re(); exit(1);
	}
	Plan *p = list.plan_head->next;
	for (p; p; p = p->next) {
		fprintf(fp, "%ld %d %d %d-%d-%d %d:%d %d\n",p->element.plan_ID,p->element.program_ID,p->element.studio_ID,\
p->element.date.year, p->element.date.month, p->element.date.day,p->element.time.hour,p->element.time.minute,p->element.ticketnum);
		Ticket *k = p->element.ticket_head->next;
		for (int i = 1; i <= p->element.ticketnum; i++) {
			fprintf(fp, "%ld %d %d %d %d     ", k->ticket_ID, k->seatx, k->seaty, k->price, k->ticket_status);
			k = k->next;
			if (i % 5 == 0) { fprintf(fp, "\n"); }
		}
	}
	fprintf(fp, "\n");
	fclose(fp);
}