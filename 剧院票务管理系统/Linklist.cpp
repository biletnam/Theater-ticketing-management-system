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
	if (enquiry(1)) {
		p->next = list.program_tail->next;
		p->pre = list.program_tail;
		list.program_tail->next = p;
		list.program_tail = p;
		save_program();
		print_ok();
	}
	else {
		free(p);
		printf("新增已取消\n"); rewind(stdin);
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
		printf("没有这个剧目哦\n");
		for (p = list.program_head->next; p; p = p->next) {
			if (strstr(p->element.program_ID, obj) != NULL || strstr(p->element.program_name, obj) != NULL) {
				if (flag == 0) {
					Sleep(500); printf("嗯  "); printf("也许你想找的是：\n"); Sleep(1000);
					flag = 1;
				}
				printf("%s  %s\n", p->element.program_ID, p->element.program_name);
			}
		}
		if(flag==1)printf("请确认后重新查找\n");
		return NULL;
	}
}

void kill_program(Program *p) {//按照ID或名字删除剧目
	if (p) {
		if (enquiry(2)) {
			p->pre->next = p->next;
			if (p->next) {//p不为最后一个
				p->next->pre = p->pre;
				free(p);
				save_program();
				print_ok();
			}
		}
		else {
			printf("删除已取消\n"); rewind(stdin);
		}
	}
}

void print_program(Program *p , int i) {//输出某个剧目信息    i  控制是否清屏
	if (p) {
		if(i)system("cls");
		char rating[8],type[7],person[5];
		switch (p->element.program_rating) {
		case 1:strcpy(rating, "Child"); break;
		case 2:strcpy(rating, "Teen"); break;
		case 3:strcpy(rating, "Adult"); break;
		default:
			print_re();
		}
		switch (p->element.program_type) {
		case 1:strcpy(type, "电影"); strcpy(person,"导演"); break;
		case 2:strcpy(rating, "歌剧"); strcpy(person, "导演"); break;
		case 3:strcpy(rating, "音乐会"); strcpy(person, "指挥"); break;
		default:
			print_re();
		}
		printf("\n");
		printf("	==================================================================\n");
		printf("	||								||\n");
		printf("	||%s名称:%-15s		%s:%-8s		||\n",type, p->element.program_name,person, p->element.director);
		printf("	||								||\n");
		printf("	||主演:%-14s	%-14s	时长:%dmin		||\n", p->element.performer[0], p->element.performer[1], p->element.duration);
		printf("	||								||\n");
		printf("	||电影标签:%-s                 地区:%-s       票价:%-d		||\n", p->element.label, p->element.area, p->element.price);
		printf("	||								||\n");
		printf("	||放映等级:%-8s		语言:%-10s			||\n", rating, p->element.language);
		printf("	==================================================================\n");
		rewind(stdin);
	}
}

void modify_program(Program *p) {//修改电影信息
	if (p) {
		print_program(p,1);
		printf("请选择你想要更改的\n");
		printf("1.票价 2.放映等级 3.时长 4.地区 \n5.语言 6.电影标签 7.主演 8.导演\n");
		int choice = 0; char *str; rewind(stdin);
		data_program tem=p->element;
		choice = get_num(1, 8, 1, 1);
		switch (choice) {
		case 1:printf("请输入新的票价(5~100):"); choice = get_num(5, 100, 1, 3); tem.price = choice; break;
		case 2:printf("请输入放映等级(1~3):"); choice = get_num(1, 3, 1, 1); tem.program_rating = (program_ratings)choice; break;
		case 3:printf("请输入影片时长(1~600):"); choice = get_num(1, 600, 1, 3); tem.duration = choice; break;
		case 4:printf("请输入影片地区(2个汉字):"); str = get_string(4, 4, 2); strcpy(tem.area, str); free(str); break;
		case 5:printf("请输入影片语言(最多14个字符):"); str = get_string(1, 15, 0); strcpy(tem.language, str); free(str); break;
		case 6:printf("请输入影片标签(2个汉字):"); str = get_string(4, 4, 2); strcpy(tem.label, str); free(str); break;
		case 7:printf("请输入第一位主演姓名(最多7个汉字):"); str = get_string(1, 14, 0); strcpy(tem.performer[0], str); free(str);
			printf("是否继续输入?(0/1):"); rewind(stdin); if (choice = get_num(0, 1, 1, 1)) {
				printf("请输入第二位主演姓名(最多7个汉字):");
				str = get_string(1, 14, 0); strcpy(tem.performer[1], str); free(str);
			}break;
		case 8:printf("请输入导演姓名(最多7个汉字):"); str = get_string(1, 14, 0); strcpy(tem.director, str); free(str); break;
		default:
			break;
		}
		if (enquiry(1)) {
			p->element = tem;
			save_program();
			print_ok();
		}
		else {
			printf("修改已取消\n"); rewind(stdin);
		}
		printf("是否继续修改?(0/1):");
		if (get_num(0, 1, 1, 1)) {
			modify_program(p);
		}
	}
}

/////////////////////////////////////////studio

void add_studio() {//增加放映厅
	Studio *p = (Studio *)malloc(sizeof(Studio));
	printf("\n请输入新的放映厅编号(4~6位数字):\n"); rewind(stdin);
	char *str = get_string(4, 6, 1);
	while (search_studio(str)) {
		printf("该编号已被使用，请重新输入\n"); rewind(stdin);free(str);
		str = get_string(4, 6, 1);
	}
	strcpy(p->element.studio_ID, str); free(str);
	printf("请输入放映厅名称(7个汉字以内):\n"); rewind(stdin);
	str = get_string(1,14,0);
	while (search_studio(str)) {
		printf("该名称已被使用，请重新输入\n"); rewind(stdin); free(str);
		str = get_string(1, 14, 1);
	}
	strcpy(p->element.studio_name, str); free(str);
	printf("请输入该影厅座位的行数(8~15):");
	int choice = get_num(8, 15, 1, 2);
	p->element.seatx=choice;
	printf("请输入该影厅座位的列数(10~40):");
	choice = get_num(10, 40, 2, 2);
	p->element.seaty = choice;
	if (enquiry(1)) {
		p->next = list.studio_tail->next;
		list.studio_tail->next = p;
		//save_studio_and_seat();
		//import_studio_and_seat();
		printf("所有座位已置为可用状态\n如有需要请记得修改\n");
		print_ok();
	}
	else {
		import_studio_and_seat();
	}
}

Studio *search_studio(char *obj) {//按ID或名称查找放映厅    模糊查询
	Studio *p=list.studio_head->next;
	int flag = 0;
	for (p; p; p = p->next) {
		if (strcmp(p->element.studio_ID, obj) == 0 || strcmp(p->element.studio_name, obj) == 0) {
			flag = 1; break;
		}
	}
	if (flag) {
		return p;
	}
	else {
		printf("该放映厅不存在哦");
		for (p = list.studio_head->next; p; p = p->next) {
			if (strstr(p->element.studio_ID, obj) != NULL || strstr(p->element.studio_name, obj) != NULL) {
				if (flag == 0) {
					Sleep(500); printf("嗯  "); Sleep(1000); printf("也许你要找的是\n"); rewind(stdin); flag = 1;
				}printf("%s    %s\n",p->element.studio_ID,p->element.studio_name);
			}
		}
		return NULL;
	}
}

void kill_studio(Studio *p) {//删除指定放映厅
	if (p) {
		if(enquiry(2)){
			p->pre->next = p->next;
			if (p->next)
				p->next->pre = p->pre;
			free(p);
			//save_studio_and_seat();
		}
		else {
			printf("删除已取消\n"); rewind(stdin);
		}
	}
}

void print_studio(Studio *p) {//打印放映厅及座位信息
	if (p) {
		int i, j;
		system("cls");
		Seat *k = search_seat(atoi(p->element.studio_ID));
		printf("\n\n");
		printf("	==================================================================\n");
		printf("			放映厅编号：%s	名称：%s\n\n",p->element.studio_ID,p->element.studio_name);
		printf("			○表示可用座位  ●表示损坏座位\n\n");
		printf("				╭——————————╮\n");
		printf("					↑荧幕\n\n");
		for (i = 1; i <= p->element.seatx; i++) {
			printf("			");
			for (j = 1; j <= p->element.seaty; j++) {
				switch (k->seat_condition) {
				case 0:printf("  "); break;
				case 1:printf("○"); break;
				case 9:printf("●"); break;
				default:
					print_re(); break;
				}
				k = k->next;
			}printf("\n");
		}
	}
}


////////////////////////////////////////seat

void insert_seat(Studio *H) {//插入座位到特定链表位置及放映厅位置

}

Seat *search_seat(int obj) {//根据放映厅编号查找座位
	int flag = 0;
	Seat *p = list.seat_head->next;
	for (p; p; p = p->next) {
		if (p->stduio_ID == obj) {
			flag = 1;
			return p;
		}
	}
	printf("");
	return NULL;
}