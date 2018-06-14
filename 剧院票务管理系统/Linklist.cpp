#include"stdafx.h"
#include"statements.h"

void initialize_linklist() {//��ʼ������
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

long get_newkey(int judge) {//����judge��Ӧ��������ֵ
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

void add_program() {//���Ӿ�Ŀ
	Program *p = (Program *)malloc(sizeof(Program));
	exam_mallocX(p);
	p->element = get_program_infomation();//��Ŀ��Ϣ��ȡ
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
		printf("������ȡ��\n"); rewind(stdin);
	}
}

Program *search_program(char *obj,int judge) {//��ID�����ֲ��Ҿ�Ŀ  judge �����Ƿ�������Ʒ���
	int flag = 0;
	Program *p = list.program_head->next;
	for (p; p; p = p->next) {
		if (strcmp(p->element.program_ID, obj) == 0 || strcmp(p->element.program_name, obj) == 0) {
			flag = 1;//�ҵ�
			break;
		}
	}
	if (flag)
		return p;
	if (judge&&flag == 0) {
		printf("û�������ĿŶ\n");
		for (p = list.program_head->next; p; p = p->next) {
			if (strstr(p->element.program_ID, obj) != NULL || strstr(p->element.program_name, obj) != NULL) {
				if (flag == 0) {
					Sleep(500); printf("��  "); printf("Ҳ�������ҵ��ǣ�\n"); Sleep(1000);
					flag = 1;
				}
				printf("%s  %s\n", p->element.program_ID, p->element.program_name);
			}
		}
		if(flag==1)printf("��ȷ�Ϻ����²���\n");
	}return NULL;
}

void kill_program(Program *p) {//����ID������ɾ����Ŀ
	if (p) {
		if (enquiry(2)) {
			p->pre->next = p->next;
			if (p->next) {//p��Ϊ���һ��
				p->next->pre = p->pre;
				free(p);
				save_program();
				list.program_head->element.cost -= 1;
				print_ok();
			}
		}
		else {
			printf("ɾ����ȡ��\n"); rewind(stdin);
		}
	}
}

void print_program(Program *p , int i) {//���ĳ����Ŀ��Ϣ    i  �����Ƿ�����
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
		case 1:strcpy(type, "��Ӱ"); strcpy(person,"����"); break;
		case 2:strcpy(rating, "���"); strcpy(person, "����"); break;
		case 3:strcpy(rating, "���ֻ�"); strcpy(person, "ָ��"); break;
		default:
			print_re();
		}
		printf("\n");
		printf("	==================================================================\n");
		printf("	||								||\n");
		printf("	||%s����:%-15s		%s:%-8s		||\n",type, p->element.program_name,person, p->element.director);
		printf("	||								||\n");
		printf("	||����:%12s	%-14s	ʱ��:%dmin		||\n", p->element.performer[0], p->element.performer[1], p->element.duration);
		printf("	||								||\n");
		printf("	||��Ӱ��ǩ:%-s                 ����:%-s       Ʊ��:%-d		||\n", p->element.label, p->element.area, p->element.price);
		printf("	||								||\n");
		printf("	||��ӳ�ȼ�:%-8s		����:%-10s			||\n", rating, p->element.language);
		printf("	==================================================================\n");
		rewind(stdin);
	}
}

void modify_program(Program *p) {//�޸ĵ�Ӱ��Ϣ
	if (p) {
		print_program(p,1);
		printf("��ѡ������Ҫ���ĵ�\n");
		printf("1.Ʊ�� 2.��ӳ�ȼ� 3.ʱ�� 4.���� \n5.���� 6.��Ӱ��ǩ 7.���� 8.����\n");
		int choice = 0; char *str; rewind(stdin);
		data_program tem=p->element;
		choice = get_num(1, 8, 1, 1);
		switch (choice) {
		case 1:printf("�������µ�Ʊ��(5~100):"); choice = get_num(5, 100, 1, 3); tem.price = choice; break;
		case 2:printf("�������ӳ�ȼ�(1~3):"); choice = get_num(1, 3, 1, 1); tem.program_rating = (program_ratings)choice; break;
		case 3:printf("������ӰƬʱ��(1~600):"); choice = get_num(1, 600, 1, 3); tem.duration = choice; break;
		case 4:printf("������ӰƬ����(2������):"); str = get_string(4, 4, 2); strcpy(tem.area, str); free(str); break;
		case 5:printf("������ӰƬ����(���14���ַ�):"); str = get_string(1, 15, 0); strcpy(tem.language, str); free(str); break;
		case 6:printf("������ӰƬ��ǩ(2������):"); str = get_string(4, 4, 2); strcpy(tem.label, str); free(str); break;
		case 7:printf("�������һλ��������(���7������):"); str = get_string(1, 14, 0); strcpy(tem.performer[0], str); free(str);
			printf("�Ƿ��������?(0/1):"); rewind(stdin); if (choice = get_num(0, 1, 1, 1)) {
				printf("������ڶ�λ��������(���7������):");
				str = get_string(1, 14, 0); strcpy(tem.performer[1], str); free(str);
			}break;
		case 8:printf("�����뵼������(���7������):"); str = get_string(1, 14, 0); strcpy(tem.director, str); free(str); break;
		default:
			break;
		}
		if (enquiry(1)) {
			p->element = tem;
			save_program();
			print_ok();
		}
		else {
			printf("�޸���ȡ��\n"); rewind(stdin);
		}
		printf("�Ƿ�����޸�?(0/1):");
		if (get_num(0, 1, 1, 1)) {
			modify_program(p);
		}
	}
}

///////////////////////////////////////////studio

void add_studio() {//���ӷ�ӳ��
	Studio *p = (Studio *)malloc(sizeof(Studio));
	exam_mallocX(p);
	printf("\n�������µķ�ӳ�����(4~6λ����):\n"); rewind(stdin);
	char *str = get_string(4, 6, 1);
	while (search_studio(str, 0)) {
		printf("�ñ���ѱ�ʹ�ã�����������\n"); rewind(stdin);free(str);
		str = get_string(4, 6, 1);
	}
	strcpy(p->element.studio_ID, str); free(str);
	printf("�������ӳ������(7����������):\n"); rewind(stdin);
	str = get_string(1,14,0);
	while (search_studio(str, 0)) {
		printf("�������ѱ�ʹ�ã�����������\n"); rewind(stdin); free(str);
		str = get_string(1, 14, 1);
	}
	strcpy(p->element.studio_name, str); free(str);
	printf("�������Ӱ����λ������(5~12):");
	int choice = get_num(5, 12, 1, 2);
	p->element.seatx=choice;
	printf("�������Ӱ����λ������(10~25):");
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
		printf("������λ����Ϊ����״̬\n������Ҫ��ǵ��޸�\n");
		list.studio_head->element.seatx++;
	}
	else {
		free(p);
		printf("��ӳ��������ȡ��\n");
	}
}

Studio *search_studio(char *obj,int judge) {//��ID�����Ʋ��ҷ�ӳ��  judge  �����Ƿ�������Ʒ���
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
		printf("�÷�ӳ��������Ŷ\n");
		for (p = list.studio_head->next; p; p = p->next) {
			if (strstr(p->element.studio_ID, obj) != NULL || strstr(p->element.studio_name, obj) != NULL) {
				if (flag == 0) {
					Sleep(500); printf("��  "); Sleep(1000); printf("Ҳ����Ҫ�ҵ���\n"); rewind(stdin); flag = 1;
				}printf("%s    %s\n",p->element.studio_ID,p->element.studio_name);
			}
		}if (flag)printf("��ȷ�Ϻ����²���\n");
	}
	return NULL;
}

void kill_studio(Studio *p) {//ɾ��ָ����ӳ��
	if (p) {
		if(enquiry(2)){
			p->pre->next = p->next;
			if (p->next)
				p->next->pre = p->pre;
			delete_seat(p);//ɾ���÷�ӳ��������λ
			free(p);
			list.studio_head->element.seatx--;
			save_studio_and_seat();
			print_ok();
		}
		else {
			printf("ɾ����ȡ��\n"); rewind(stdin);
		}
	}
}

void print_studio(Studio *p) {//��ӡ��ӳ������λ��Ϣ
	if (p) {
		int i, j, cnt = 0;//cnt ���������λ��
		system("cls");
		Seat *k = p->element.seat_head->next;
		printf("\n");
		printf("	====================================================================\n");
		printf("			��ӳ����ţ�%s	���ƣ�%s\n\n",p->element.studio_ID,p->element.studio_name);
		printf("			���ʾ������λ  ���ʾ����λ   ��λ %d x %d\n\n",p->element.seatx,p->element.seaty);
		printf("			�q�������������������������������������r\n");
		printf("					��ӫĻ\n\n");
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
				case 1:printf("��"); cnt++; break;
				case 9:printf("��"); break;
				default:
					print_re(); break;
				}
				k = k->next;
			}printf("\n");
		}printf("\n\n			����ӳ������%d�ſ�����λ\n", cnt);
	}
}

void modify_studio(Studio *p) {//�޸�Ӱ����Ϣ����λ���
	if (p) {
		print_studio(p);
		printf("��ѡ��Ҫ�޸ĵģ�\n");
		printf("1.��ӳ������ 2.��λ���� 3.��λ���� 4.��λ����\n");//2.��λ���� 3.��λ����
		int choice = get_num(1, 4, 1, 1); char *str = NULL; data_studio tem=p->element;
		switch (choice) {
		case 1:printf("�������µķ�ӳ������"); str = get_string(1, 14, 0); strcpy(tem.studio_name, str); free(str); break;
		case 2:printf("�������µ�����(5~12)��"); choice = get_num(5, 12, 1, 2); tem.seatx = choice; break;
		case 3:printf("�������µ�����(10~25)��"); choice = get_num(10, 25, 2, 2); tem.seaty = choice; break;
		case 4:print_instruction(1); seat_changer(p); break;
		}if (choice != 4) {
			if (enquiry(1)) {
				if (tem.seatx != p->element.seatx || tem.seaty != p->element.seaty) {//��ʼ����λ
					if(tem.seatx > p->element.seatx || tem.seaty > p->element.seaty)printf("��Ĭ�������л�������λ\n");
					int i, j; Seat *k = p->element.seat_head->next;

					//�������� ����

					//char seat[13][26] = { 0 }; 
					//for (i = 1; i <= p->element.seatx; i++) {
					//	for (j = 1; j <= p->element.seaty; j++) {//¼��ԭ����λ
					//		seat[i][j] = k->seat_condition; k = k->next;
					//	}
					//}
					//delete_seat(p);//ɾ��ԭ����λ
					//int ID = atoi(p->element.studio_ID); Seat *q = NULL;
					//p->element.seat_head = (Seat *)malloc(sizeof(Seat)); exam_mallocX(p->element.seat_head);
					//p->element.seat_tail = p->element.seat_head;
					//p->element.seat_head->pre = p->element.seat_tail->next = NULL;//��ʼ����λ����
					//for (i = 1; i <= tem.seatx; i++) {
					//	for (j = 1; j <= tem.seaty; j++) {
					//		q = (Seat *)malloc(sizeof(Seat));
					//		exam_mallocX(q);
					//		q->seatx = i; q->seaty = j; q->stduio_ID = ID; q->seat_condition = (seat_conditions)seat[i][j];
					//		q->next = p->element.seat_tail->next; q->pre = p->element.seat_tail; 
					//		p->element.seat_tail->next = q; p->element.seat_tail = q;
					//	}
					//}//����ת��Ϊ����
					//tem.seat_head = p->element.seat_head; tem.seat_tail = p->element.seat_tail;

					///////////�����ʵʱ����    �ڴ����
					int tID = atoi(p->element.studio_ID);
					k = p->element.seat_head->next;
					if (tem.seatx > p->element.seatx){//��������
						for (i = p->element.seatx + 1; i <= tem.seatx; i++) {
							for (j = 1; j <= p->element.seaty; j++) {//�����½ڵ�
								if (i > p->element.seatx || j > p->element.seaty) {
									Seat *q = (Seat *)malloc(sizeof(Seat));
									q->seatx = i; q->seaty = j; q->seat_condition = (seat_conditions)0; q->stduio_ID = tID;
									q->next = p->element.seat_tail->next; q->pre = p->element.seat_tail;
									p->element.seat_tail->next = q; p->element.seat_tail = q;
								}
							}
						}
					}
					else if (tem.seaty > p->element.seaty) {//��������
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
					else if (tem.seaty < p->element.seaty) {//��������
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
					else if (tem.seatx < p->element.seatx) {//��������
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
				printf("�޸���ȡ��\n");
			}
		}
	}
}

/////////////////////////////////////////////seat

void initialize_seat(Studio *p) {//Ϊ�·�ӳ����ʼ����λ
	p->element.seat_head = (Seat *)malloc(sizeof(Seat));
	exam_mallocX(p->element.seat_head);
	p->element.seat_head->pre = p->element.seat_head->next = NULL;//�������ʼ��
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

//Seat *search_seat(char *obj) {//���ݷ�ӳ�����������鿴��λ��Ϣ
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

void delete_seat(Studio *k) {//ɾ����ӳ��ʱɾ������λ
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