#include"stdafx.h"
#include"statements.h"

void print_re() {//����bug����
	printf("��ʵ�����仰�ǲ����ܵ�\n");
	printf("���ִ�������ϵ������qvq  \nQQ740721665��863139668"); rewind(stdin);
}

void print_examinput() {//�Ƿ����뱨��
	printf("���벻����Ҫ������������\n");
	rewind(stdin);
}

void go_on() {//�����������
	rewind(stdin);
	printf("�����������\n");
	rewind(stdin);
	getch();
	getch();
}

void exam_mallocX(void *p) {//malloc����
	if (p == NULL) {
		printf("���ܷ�������ڴ���\n");
		exit(1);
	}
}

int enquiry(int i) {//�ж��Ƿ���б��β���   i==1   enquiry   i==2 warnning
	if (i == 1)
		printf("�Ƿ�ȷ�ϱ��β���?(0/1):");
	else if (i == 2)
		printf("�ò������ɻָ����Ƿ����?(0/1):");
	else
		print_re();
	rewind(stdin);
	int judge = 0;
	judge = get_num(0,1,1,1);
	return judge;
}

void print_ok() {//��ʾ�����ɹ�
	printf("�����ɹ��˵�˵!\n");
	rewind(stdin);
}


//����

//void print_label(int i) {//��ӡ��ǩ�б�     i  = 1 ��Ӱ       2 ���        3���ֻ�
//	if (i == 1)
//	printf("ϲ�� ���� ��� ���� ���� �ֲ�\n\
//��¼ �ƻ� ���� �ഺ ���� ����\n");
//	else if (i == 2) 
//	printf("��ѡ���ǩ:");
//	rewind(stdin);
//}
