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
	getch();
}

void print_mallocX() {//malloc����
	printf("���ܷ�������ڴ���\n");
}

int enquiry() {//�ж��Ƿ���б��β���
	printf("�Ƿ�ȷ�ϱ��β�����(0/1)\n");
	rewind(stdin);
	int judge = 0;
	do {
		scanf("%d", &judge);
		if (judge != 0 && judge != 1) {
			print_examinput();
		}
	} while (judge != 0 && judge != 1);
	return judge;
}

void print_ok() {//��ʾ�����ɹ�
	printf("�����ɹ��˵�˵!\n");
	rewind(stdin);
}


