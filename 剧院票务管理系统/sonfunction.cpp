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
			printf("�����Ӵ\n");
			go_on();
		}
	}
	else {//�û���������
		system("cls");
		set_position(25, 10);
		SetColor(12, 0);
		printf("û������˺�Ӵ\n");
		go_on();
	}
	return flag;//flag==0  ��ʾ��¼ʧ�ܣ��������Ͳμ�user_types
}

char *username_get(int judge) {//�û����Ļ�ȡ    judge!=0ʱ���������� 
	char *str=(char *)malloc(NAME*5);
	exam_mallocX(str);
	str[0] = '\0';
	scanf("%s", str);
	if(judge&&str)//str���ھ������
	while (strlen(str) > 14 || strlen(str) < 4) {
		print_examinput();
		scanf("%s", str);
	}
	return str;
}

char *password_get(int judge) {//��������Ļ�ȡ        judge!=0ʱ����������
	char *password = (char *)malloc(PASSWORD * 4 * sizeof(char));
	char str[50], c = 0, i = 0;
	do {
		while (i < 49) {
			c = getch();
			getch();//΢����²���
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

char *get_string(int down,int up ,int judge) {//�ַ�����ȡ����麯��    ����[down,up]   �ַ����ֽ�������
	char *str = (char *)malloc(sizeof(char)*100);// judge ����   �Ƿ������ּ�顢���ּ��  
	SetColor(14, 0);
	scanf("%s", str);
	SetColor(7, 0);
	unsigned int flag = 1, i;
	do {
		if (judge) {//���м����
			if (judge == 1) {
				for (i = 0; i < strlen(str); i++) {
					if (isdigit(str[i]) == 0) {//ȫΪ����
						flag = 0; break;
					}
				}
			}else if (judge == 2) {
				for (i = 0; i < strlen(str); i++) {
					if (0<=str[i]&&str[i]<=255) {//���ּ��
						flag = 0; break;
					}
				}
			}
		}
		while (flag == 0 || ((int)strlen(str) < down || (int)strlen(str) > up)) {
			print_examinput();
			SetColor(14, 0);
			scanf("%s", str);
			SetColor(7, 0);
		}
	} while ((flag == 0) && (flag = 1));
	return str;
}

int get_num(int down, int up, int ndown, int nup) {//��ȡ����    ���������   ��Χ[down,up]   λ��n[ndown,nup]
	int num,flag=1;
	do {
		SetColor(14, 0);
		scanf("%d", &num);
		SetColor(7, 0);
		char str[25];
		sprintf(str, "%d", num);
		if (num<down || num>up || (strlen(str) > nup||strlen(str) < ndown)) {//����С��λ��
			print_examinput();
			flag = 0;
		}
	} while (flag == 0 && (flag = 1));
	return num;
}

date_status get_date() {//���ڵĻ�����ж�
	date_status date = {0,0,0};
	int flag = 1,y,m,d;
	do {
		SetColor(14, 0);
		scanf("%d-%d-%d", &y, &m, &d);
		SetColor(7, 0);
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

time_status get_time() {//ʱ��Ļ�ü��ж�
	time_status time = {0,0};
	int h, m,flag=1;
	do {
		SetColor(14,0);
		scanf("%d:%d", &h, &m);
		SetColor(7, 0);
		if (h < 0 || h>23 || m < 0 || m>59) {
			flag = 0;
			print_examinput();
		}
	} while (flag == 0 && (flag = 1));
	time.hour = h, time.minute = m;
	return time;
}

data_program get_program_infomation() {//��ȡ��Ŀ��Ҫ��Ϣ  �����г�ʼ��
	catch_cursor();
	data_program tem = { 0 };
	strcpy(tem.area, "����");
	strcpy(tem.performer[0], "����");
	strcpy(tem.performer[1], "����");
	strcpy(tem.language, "����");
	strcpy(tem.label, "����");
	tem.program_rating = (program_ratings)1;
	char *str; int flag = 1, choice;
	printf("\n1.��Ӱ   2.���   3.���ֻ�\n");
	printf("��ѡ���Ŀ����:");
	choice = get_num(1, 3, 1, 1);
	tem.program_type = (program_types)choice;
	printf("�������Ŀ���(6λ����):");
	str = get_string(6, 6, 1);
	Program *p;//ID����
	do {
		p = search_program(str, 0);
		if (p) {
			free(str);
			printf("�ñ���ѱ�ʹ�ã��Ƽ����%d\n����������:",atoi(list.program_tail->element.program_ID)+1);
			str = get_string(6, 6, 1);
		}
	} while (p != NULL);
	strcpy(tem.program_ID, str);
	free(str);
	printf("�������Ŀ����(15����������):");
	str = get_string(1, 30, 0);
	strcpy(tem.program_name, str);
	free(str);
	tem.program_rating == 3 ? printf("������ָ������(7����������):") : printf("�����뵼������(7����������):");
	str = get_string(1, 14, 0);
	strcpy(tem.director, str);
	free(str);
	printf("��������ӳ�������������(year-month-day):\n");
	do {
		tem.start_date = get_date();
		tem.end_date = get_date();
		//char date1[15], date2[15];
		//sprintf(date1, "%d-%d-%d", tem.start_date.year, tem.start_date.month, tem.start_date.day);
		//sprintf(date2, "%d-%d-%d", tem.end_date.year, tem.end_date.month, tem.end_date.day);
		if (tem.start_date.year>tem.end_date.year||(tem.start_date.year==tem.end_date.year&&\
			tem.start_date.month>tem.end_date.month)||(tem.start_date.year == tem.end_date.year\
			&&tem.start_date.month==tem.end_date.month&&tem.start_date.day>tem.end_date.day)) {
			flag = 0;
			print_examinput();
		}
	} while (flag == 0 && (flag = 1));
	printf("�����þ�Ŀʱ��(1~600)(min):");
	choice = get_num(1,600,1,3);
	tem.duration = choice;
	printf("������Ʊ��(5~100)(Ԫ):");
	choice = get_num(5, 100, 1, 3);
	tem.price = choice;
	printf("������ӰƬ����(2������):");
	str = get_string(4, 4, 2);
	printf("������ӰƬ��ӳ�ɱ�(��Ԫ):");
	choice = get_num(1, 100, 1, 2);
	tem.cost = choice;
	printf("������Ϣ����ΪĬ��ֵ\n������Ҫ��ǵ��޸�\n");
	return tem;
}

//void program_viewer() {//��Ŀ�����
//	Program *p=list.program_head->next;
//	print_program(p);
//	int choice;
//	while (choice = turn_page()) {
//		if (choice == -1) {
//			if (p != list.program_head->next)
//				p = p->pre;
//		}
//		else if (choice == 1) {
//			if (p != list.program_tail)
//				p = p->next;
//		}
//		print_program(p);
//		if (p == list.program_head->next)
//			printf("\n		�Ѿ��ǵ�һҳ��");
//		else if (p == list.program_tail)
//			printf("\n		�Ѿ������һҳ��");
//	}
//}

void program_viewer() {//��Ŀ�����
	Program *p1 = list.program_head->next;
	Program *p2=NULL;
	int choice, cnt = 1, pages = (list.program_head->element.cost + 1) / 2;
	print_program(p1, 1); printf("				��ǰ��%dҳ����%dҳ", cnt, pages);
	if (p1) {
		p2 = p1->next;
		print_program(p2,0);
	}
	while (choice=turn_page()) {
		if (choice == 1 || choice == 2) {
			if(p1!=list.program_tail&&p2!=list.program_tail)
			if (p2) {
				p1 = p2->next;
				if (p1) {
					p2 = p1->next; cnt++;
				}
				//else {//���ظ����
				//	p2 = NULL;
				//}
			}
			/*else {
				p1 = NULL;
			}*/
			print_program(p1,1); printf("				��ǰ��%dҳ����%dҳ", cnt, pages); print_program(p2,0);
		}
		else if (choice == -1 || choice == -2) {
			if(p1!=list.program_head&&p2!=list.program_head)
				if (p1&&p1->pre!=list.program_head) {
					p2 = p1->pre;
					if (p2&&p2->pre!=list.program_head) {
						p1 = p2->pre; cnt--;
				}
			//	else {//���ظ����
			//		p2 = NULL;
			//	}
			}
			//else {
			//	p1 = NULL;
			//}
			if (p1&&p2) {
				if (p1 != list.program_head)print_program(p1, 1); printf("				��ǰ��%dҳ����%dҳ",cnt,pages); if (p2 != list.program_head)print_program(p2, 0);
			}
			/*else {
				if (p1 != list.program_head)print_program(p1, 1); if (p2 != list.program_head) print_program(p2, 0);
			}*/
		}else {
			print_re();
		}
		/*if (choice==1&&(p1 == list.program_tail || p2 == list.program_tail)) {
			printf("�Ѿ������һҳ��\n");
		}
		else if (choice == -1 && (p1 == list.program_head->next || p2 == list.program_head->next)) {
			printf("�Ѿ��ǵ�һҳ��\n");
		}*/
	}
}

void studio_viewer() {//��ӳ���鿴��
	int choice, cnt = 1, pages = list.studio_head->element.seatx;
	Studio *p = list.studio_head->next;
	if (p) { print_studio(p); printf("			��ǰ��%d����ӳ������%d��", cnt, pages); }
	while (choice=turn_page()) {
		if (choice == 1 || choice == 2) {
			if (p->next) { p = p->next; cnt++; }
			if (p) print_studio(p);
			printf("			��ǰ��%d����ӳ������%d��", cnt, pages);
		}
		else if (choice == -1 || choice == -2) {
			if (p != list.studio_head->next) { p = p->pre; cnt--; }
			print_studio(p);
			printf("			��ǰ��%d����ӳ������%d��", cnt, pages);
		}
	}
}

void seat_changer(Studio *p) {//���ӻ���λ�޸���
	system("cls");
	if(p==NULL){ return;}
	Seat *k = p->element.seat_head->next;
	if (k == NULL) { printf("�����ӳ��û����λӴ\n"); go_on(); return; }
	int i, j;
	for (i=1 ; i <=p->element.seatx ; i++) {
		for (j=1 ; j <= p->element.seaty; j++) {
			switch (k->seat_condition)
			{
			case 0:printf("  "); break;
			case 1:printf("��");  break;
			case 9:printf("��"); break;
			}k = k->next;
		}printf("\n");
	}
	if (select_seat(p)) {
		save_studio_and_seat();
	}
	else {
		printf("�޸���ȡ��\n");
	}
}

void account_appeal() {//�˺����߹���

}