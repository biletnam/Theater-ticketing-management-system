#include"stdafx.h"
#include"statements.h"

void initialize_linklist() {//初始化链表
	list.account_head = (Account *)malloc(sizeof(Account));
	list.program_head = (Program *)malloc(sizeof(Program));
	list.studio_head = (Studio *)malloc(sizeof(Studio));
	list.plan_head = (Plan *)malloc(sizeof(Plan));
	list.seat_head = (Seat *)malloc(sizeof(Seat));
	list.ticket_head = (Ticket *)malloc(sizeof(Ticket));
	list.record_head = (Record *)malloc(sizeof(Record));
	list.account_head->next = list.account_head->pre = NULL;
	list.program_head->next = list.program_head->pre =  NULL;
	list.studio_head->next =list.studio_head->pre = NULL;
	list.plan_head->next = list.plan_head->pre = NULL;
	list.seat_head->next = list.seat_head->pre = NULL;
	list.ticket_head->next = list.ticket_head->pre = NULL;
	list.record_head->next = list.record_head->pre = NULL;
	list.account_tail = list.account_head;
	list.program_tail = list.program_head;
	list.studio_tail = list.studio_head;
	list.plan_tail = list.plan_head;
	list.seat_tail = list.seat_head;
	list.ticket_tail = list.ticket_head;
	list.record_tail = list.record_head;
}

////////////////////////////////////////program

void add_program() {//增加剧目
	Program *p = (Program *)malloc(sizeof(Program));
	p->element = get_program_infomation();//剧目信息获取
	if (enquiry()) {
		p->next = list.program_tail->next;
		p->pre = list.program_tail;
		list.program_tail->next = p;
		list.program_tail = p;
		save_program();
		print_ok();
	}
	else {
		free(p);
	}
}

Program *search_program(char *obj) {//按ID或名字查找剧目
	int flag = 0;
	Program *p = list.program_head->next;
	for (p; p; p = p->next) {
		if (strcmp(p->element.program_ID, obj) == 0 || strcmp(p->element.program_name, obj) == 0) {
			flag = 1;//找到
			break;
		}
	}
	if (flag)
		return p;
	else {//////////模糊查询
		return NULL;
	}
}

void kill_program(Program *p) {//按照ID或名字删除剧目
	if (p) {
		p->pre->next = p->next;
		if (p->next) {//p不为最后一个
			p->next->pre = p->pre;
			print_ok();
		}
	}
	else {
		printf("没有这个剧目的说\n");
	}
}

void print_program(Program *p) {//按ID/名称输出某个影片信息
	int flag=0;
	if (p) {
		show_program_information(p);
	}
	else{
		printf("没有这部影片哦\n");
		rewind(stdin);
	}
}

void modify_program(Program *p) {//修改电影信息
	show_program_information(p);
	go_on();
	printf("\n请选择你想要更改的\n");
	printf("1.票价 2.放映等级 3.时长 4.地区 5.语言 \n6.电影标签 7.主演 8.导演");
	int choice = 0, flag = 1; rewind(stdin);
	choice = get_num(1,8,1,1);
		switch (choice){
		case 1:printf("请输入新的票价:\n"); rewind(stdin); scanf("%d", &choice); p->element.price = choice; break;
		case 2:printf("请输入新的放映等级");
			default:
				print_examinput();flag = 0;
				break;
		}
}

/////////////////////////////////////studio


