#include"stdafx.h"
#include"statements.h"

void initialize_linklist() {//初始化链表
	list.account_head = (Account *)malloc(sizeof(Account));
	list.program_head = (Program *)malloc(sizeof(Program));
	list.studio_head = (Studio *)malloc(sizeof(Studio));
	list.plan_head = (Plan *)malloc(sizeof(Plan));
	//list.seat_head = (Seat *)malloc(sizeof(Seat));
	//list.ticket_head = (Ticket *)malloc(sizeof(Ticket));
	//list.record_head = (Record *)malloc(sizeof(Record));
	list.key_head = (Key *)malloc(sizeof(Key));
	list.account_head->next = list.account_head->pre = NULL;
	list.program_head->next = list.program_head->pre =  NULL;
	list.studio_head->next =list.studio_head->pre = NULL;
	list.plan_head->next = list.plan_head->pre = NULL;
	//list.seat_head->next = list.seat_head->pre = NULL;
	//list.ticket_head->next = list.ticket_head->pre = NULL;
	//list.record_head->next = list.record_head->pre = NULL;
	list.key_head->next = list.key_head->pre = NULL;
	list.account_tail = list.account_head;
	list.program_tail = list.program_head;
	list.studio_tail = list.studio_head;
	list.plan_tail = list.plan_head;
	//list.seat_tail = list.seat_head;
	//list.ticket_tail = list.ticket_head;
	//list.record_tail = list.record_head;
	list.key_tail = list.key_head;
}

//////////////////////////////////////////key

long get_newkey(int judge) {//返回judge对应的新主键值
	int flag = 0;
	Key *p = list.key_head->next;
	for (p; p; p = p->next) {
		if (judge == p->type) {
			p->key++; flag = 1; break;
		}
	}
	if (flag == 0) {
		print_re();
	}
	return p->key;
}

//////////////////////////////////////////program

void add_program() {//增加剧目
	Program *p = (Program *)malloc(sizeof(Program));
	exam_mallocX(p);
	p->element = get_program_infomation();//剧目信息获取
	if (enquiry(1)) {
		p->next = list.program_tail->next;
		p->pre = list.program_tail;
		list.program_tail->next = p;
		list.program_tail = p;
		save_program();
		list.program_head->element.cost += 1;
		print_ok();
	}
	else {
		free(p);
		printf("新增已取消\n"); rewind(stdin);
	}
}

Program *search_program(char *obj,int judge) {//按ID或名字查找剧目  judge 控制是否进行相似反馈
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
	if (judge&&flag == 0) {
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
	}return NULL;
}

void kill_program(Program *p) {//按照ID或名字删除剧目
	if (p) {
		if (enquiry(2)) {
			p->pre->next = p->next;
			if (p->next) {//p不为最后一个
				p->next->pre = p->pre;
				free(p);
				save_program();
				list.program_head->element.cost -= 1;
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
		printf("	||主演:%12s	%-14s	时长:%dmin		||\n", p->element.performer[0], p->element.performer[1], p->element.duration);
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

///////////////////////////////////////////studio

void add_studio() {//增加放映厅
	Studio *p = (Studio *)malloc(sizeof(Studio));
	exam_mallocX(p);
	printf("\n请输入新的放映厅编号(4~6位数字):\n"); rewind(stdin);
	char *str = get_string(4, 6, 1);
	while (search_studio(str, 0)) {
		printf("该编号已被使用，请重新输入\n"); rewind(stdin);free(str);
		str = get_string(4, 6, 1);
	}
	strcpy(p->element.studio_ID, str); free(str);
	printf("请输入放映厅名称(7个汉字以内):\n"); rewind(stdin);
	str = get_string(1,14,0);
	while (search_studio(str, 0)) {
		printf("该名称已被使用，请重新输入\n"); rewind(stdin); free(str);
		str = get_string(1, 14, 1);
	}
	strcpy(p->element.studio_name, str); free(str);
	printf("请输入该影厅座位的行数(5~12):");
	int choice = get_num(5, 12, 1, 2);
	p->element.seatx=choice;
	printf("请输入该影厅座位的列数(10~25):");
	choice = get_num(10, 25, 2, 2);
	p->element.seaty = choice;
	if (enquiry(1)) {
		p->next = list.studio_tail->next;
		p->pre = list.studio_tail;
		list.studio_tail->next = p;
		list.studio_tail = p;
		initialize_seat(p);
		save_studio_and_seat();
		print_ok();
		printf("所有座位已置为可用状态\n如有需要请记得修改\n");
		list.studio_head->element.seatx++;
	}
	else {
		free(p);
		printf("放映厅新增已取消\n");
	}
}

Studio *search_studio(char *obj,int judge) {//按ID或名称查找放映厅  judge  控制是否进行相似反馈
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
	if (judge&&flag == 0) {
		printf("该放映厅不存在哦\n");
		for (p = list.studio_head->next; p; p = p->next) {
			if (strstr(p->element.studio_ID, obj) != NULL || strstr(p->element.studio_name, obj) != NULL) {
				if (flag == 0) {
					Sleep(500); printf("嗯  "); Sleep(1000); printf("也许你要找的是\n"); rewind(stdin); flag = 1;
				}printf("%s    %s\n",p->element.studio_ID,p->element.studio_name);
			}
		}if (flag)printf("请确认后重新查找\n");
	}
	return NULL;
}

void kill_studio(Studio *p) {//删除指定放映厅
	if (p) {
		if(enquiry(2)){
			p->pre->next = p->next;
			if (p->next)
				p->next->pre = p->pre;
			delete_seat(p);//删除该放映厅所有座位
			free(p);
			list.studio_head->element.seatx--;
			save_studio_and_seat();
			print_ok();
		}
		else {
			printf("删除已取消\n"); rewind(stdin);
		}
	}
}

void print_studio(Studio *p) {//打印放映厅及座位信息
	if (p) {
		int i, j, cnt = 0;//cnt 计算可用座位数
		system("cls");
		Seat *k = p->element.seat_head->next;
		printf("\n");
		printf("	====================================================================\n");
		printf("			放映厅编号：%s	名称：%s\n\n",p->element.studio_ID,p->element.studio_name);
		printf("			○表示可用座位  ●表示损坏座位   座位 %d x %d\n\n",p->element.seatx,p->element.seaty);
		printf("			╭——————————————————╮\n");
		printf("					↑荧幕\n\n");
		for (i = 1; i <= p->element.seatx; i++) {
			if(p->element.seaty>30)
				printf("		");
			else if(p->element.seaty>21)
				printf("		   ");
			else if(p->element.seaty>15)
				printf("			");
			else if(p->element.seaty<=15)
				printf("			    ");
			for (j = 1; j <= p->element.seaty; j++) {
				switch (k->seat_condition) {
				case 0:printf("  "); break;
				case 1:printf("○"); cnt++; break;
				case 9:printf("●"); break;
				default:
					print_re(); break;
				}
				k = k->next;
			}printf("\n");
		}printf("\n\n			本放映厅共有%d张可用座位\n", cnt);
	}
}

void modify_studio(Studio *p) {//修改影厅信息及座位情况
	if (p) {
		print_studio(p);
		printf("请选择要修改的：\n");
		printf("1.放映厅名称 2.座位行数 3.座位列数 4.座位设置\n");//2.座位行数 3.座位列数
		int choice = get_num(1, 4, 1, 1); char *str = NULL; data_studio tem=p->element;
		switch (choice) {
		case 1:printf("请输入新的放映厅名称"); str = get_string(1, 14, 0); strcpy(tem.studio_name, str); free(str); break;
		case 2:printf("请输入新的行数(5~12)："); choice = get_num(5, 12, 1, 2); tem.seatx = choice; break;
		case 3:printf("请输入新的列数(10~25)："); choice = get_num(10, 25, 2, 2); tem.seaty = choice; break;
		case 4:print_instruction(1); seat_changer(p); break;
		}if (choice != 4) {
			if (enquiry(1)) {
				if (tem.seatx != p->element.seatx || tem.seaty != p->element.seaty) {//初始化座位
					if(tem.seatx > p->element.seatx || tem.seaty > p->element.seaty)printf("已默认新增行或列无座位\n");
					int i, j; Seat *k = p->element.seat_head->next;

					//辣鸡方法 弃用

					//char seat[13][26] = { 0 }; 
					//for (i = 1; i <= p->element.seatx; i++) {
					//	for (j = 1; j <= p->element.seaty; j++) {//录入原有座位
					//		seat[i][j] = k->seat_condition; k = k->next;
					//	}
					//}
					//delete_seat(p);//删除原有座位
					//int ID = atoi(p->element.studio_ID); Seat *q = NULL;
					//p->element.seat_head = (Seat *)malloc(sizeof(Seat)); exam_mallocX(p->element.seat_head);
					//p->element.seat_tail = p->element.seat_head;
					//p->element.seat_head->pre = p->element.seat_tail->next = NULL;//初始化座位链表
					//for (i = 1; i <= tem.seatx; i++) {
					//	for (j = 1; j <= tem.seaty; j++) {
					//		q = (Seat *)malloc(sizeof(Seat));
					//		exam_mallocX(q);
					//		q->seatx = i; q->seaty = j; q->stduio_ID = ID; q->seat_condition = (seat_conditions)seat[i][j];
					//		q->next = p->element.seat_tail->next; q->pre = p->element.seat_tail; 
					//		p->element.seat_tail->next = q; p->element.seat_tail = q;
					//	}
					//}//数组转化为链表
					//tem.seat_head = p->element.seat_head; tem.seat_tail = p->element.seat_tail;

					///////////链表的实时更改    内存管理
					int tID = atoi(p->element.studio_ID);
					k = p->element.seat_head->next;
					if (tem.seatx > p->element.seatx){//增加行数
						for (i = p->element.seatx + 1; i <= tem.seatx; i++) {
							for (j = 1; j <= p->element.seaty; j++) {//插入新节点
								if (i > p->element.seatx || j > p->element.seaty) {
									Seat *q = (Seat *)malloc(sizeof(Seat));
									q->seatx = i; q->seaty = j; q->seat_condition = (seat_conditions)0; q->stduio_ID = tID;
									q->next = p->element.seat_tail->next; q->pre = p->element.seat_tail;
									p->element.seat_tail->next = q; p->element.seat_tail = q;
								}
							}
						}
					}
					else if (tem.seaty > p->element.seaty) {//增加列数
						for (i = 1; i <= p->element.seatx*p->element.seaty; i++) {
							if(i%p->element.seaty==0)
								for (j = p->element.seaty + 1; j <= tem.seaty; j++) {
									Seat *q = (Seat *)malloc(sizeof(Seat));
									q->seatx = (i - 1) / p->element.seaty + 1; q->seaty = j; q->seat_condition = (seat_conditions)0; q->stduio_ID = tID;
									q->next = k->next; q->pre = k;
									k->next = q; k = q;
							}k = k->next;
						}
					}
					else if (tem.seaty < p->element.seaty) {//减少列数
						i = 1;
						while ( k ) {
							if (i%tem.seaty == 0) {
								j = p->element.seaty - tem.seaty;
								k = k->next;
								while (j--) {
									if (k) {
										Seat *dead = k;
										k->pre->next = k->next;
										if (k->next) {
											k->next->pre = k->pre;
										}k = k->next;
										free(dead); i = 1;
									}
								}
							}
							if(k)k = k->next; i++;
						}
					}
					else if (tem.seatx < p->element.seatx) {//减少行数
						for (i = 1, k; i <= tem.seatx*p->element.seaty; i++, k = k->next);
						while (k) {
							Seat *dead = k;
							k->pre->next = k->next;
							if (k->next) {
								k->next->pre = k->pre;
							}
							k = k->next;
							free(dead);
						}
					}
				}
				p->element = tem;
				save_studio_and_seat();
				print_ok();
			}	
			else {
				printf("修改已取消\n");
			}
		}
	}
}

/////////////////////////////////////////////seat

void initialize_seat(Studio *p) {//为新放映厅初始化座位
	p->element.seat_head = (Seat *)malloc(sizeof(Seat));
	exam_mallocX(p->element.seat_head);
	p->element.seat_head->pre = p->element.seat_head->next = NULL;//次链表初始化
	p->element.seat_tail = p->element.seat_head;
	int i, j;
	for (i = 1; i <= p->element.seatx; i++) {
		for (j = 1; j <= p->element.seaty; j++) {
			Seat *k = (Seat *)malloc(sizeof(Seat));
			exam_mallocX(k);
			k->seatx = i, k->seaty = j, k->stduio_ID = atoi(p->element.studio_ID);
			k->seat_condition = (seat_conditions)1;
			k->next = p->element.seat_tail->next;
			k->pre = p->element.seat_tail;
			p->element.seat_tail->next = k;
			p->element.seat_tail = k;
		}
	}
}

//Seat *search_seat(char *obj) {//根据放映厅及行列数查看座位信息
//	int flag = 0;
//	Studio *k = search_studio(obj);
//	if (k) {
//		Seat *p = k->element.seat_head->next;
//		for (p; p; p = p->next) {
//			if (p->stduio_ID == atoi(obj)) {
//				flag = 1;
//				return p;
//			}
//		}
//		printf("");
//		return NULL;
//	}
//}

void delete_seat(Studio *k) {//删除放映厅时删除其座位
	if (k) {
		Seat *dead = k->element.seat_head;
		Seat *p = dead->next;
		while (p) {
			free(dead);
			dead = p;
			p = p->next;
		}free(dead);
	}
}