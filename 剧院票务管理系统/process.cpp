#include"stdafx.h"
#include"statements.h"

void process_all() {//��¼����
	show_main();
	int choice=choice_judge(1),exam=0;
	switch (choice) {
	case 1:if (exam == 0) { process_sign(); exam = 1; }
	case 2:if(exam==0){}
	case 3:if (exam == 0) { show_bye(); exit(0); exam = 3; }
	default:
		process_all();
		break;
	}
}

//USER_admin = 1,
//USER_manager = 2,
//USER_conductor = 3,
//USER_customer = 4,
//USER_unkown = 5,

void process_sign() {//��¼����
	int re = 0, cnt = 0;
	re = sign_judge();
	while ((re <= 0 || re > 4) && cnt < 3) {
		cnt++;
		re = sign_judge();
	}
	switch (re) {
	case 0:account_appeal();//�˺�����
	case 1:process_admin(); break;
	case 2:process_manager(); break;
	case 3:process_conducter(); break;
	case 4:process_customer(); break;
	default:
			print_re(); go_on(); exit(1);
		break;
	}
}

void process_admin() {//����Ա����

}

///////////////////////////////////////��Ժ����

void process_manager() {//��Ժ�������
	show_manager();
	int choice = choice_judge(2),exam=0;
	switch (choice) {
	case 1:process_program(); exam = 1;
	case 2:
	default:
		break;
	}
}

void process_program() {//��Ŀ��ѯ���������
	show_program();
	int choice = choice_judge(3);
	switch (choice) {
	case 1:
	case 2:add_program();
	}
}

///////////////////////////////////////////��ƱԱ

void process_conducter() {

}

void process_customer() {
	show_customer();
}

