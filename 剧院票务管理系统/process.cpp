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
	show_admin();
	int choice = choice_judge(7), exam = 0;
	switch (choice) {
	case 0:break;
	case 1:process_acount(); exam = 1;
	default:
		process_admin(); break;
	}
}

void process_acount() {//�˻��������        //�����������д���������
	show_account();
	int choice = choice_judge(5), exam = 0;
	switch (choice) {
	case 0:break;
	case 1:
	default:
		process_acount(); break;
	}
}

///////////////////////////////////////��Ժ����

void process_manager() {//��Ժ�������
	show_manager();
	int choice = choice_judge(2),exam=0;
	switch (choice) {
	case 0:break;
	case 1:process_program(); exam = 1;
	case 2:if (exam == 0) { process_studio(); exam = 2; }
	case 3:if(exam==0){}
	case 4:if(exam==0){}
	default:
		process_manager(); break;
	}
}

void process_program() {//��Ŀ��ѯ���������
	show_program();
	int choice = choice_judge(3),exam=0;
	switch (catch_cursor(),choice) {
	case 0:break;
	case 1:printf("\n������Ҫ��ѯ��ӰƬID������:\n"); rewind(stdin); print_program(search_program(get_string(1, 30, 0)),1); exam = 1; go_on();
	case 2:if (exam == 0) { printf("\n������Ҫ�޸ĵ�ӰƬID������:\n"); rewind(stdin); modify_program(search_program(get_string(1, 30, 0))); exam = 2; go_on();}
	case 3:if (exam == 0) { add_program(); exam = 3; }
	case 4:if (exam == 0) { printf("\n������Ҫɾ����ӰƬID������:\n"); rewind(stdin); kill_program(search_program(get_string(1,30,0))); exam = 4; go_on();}
	case 5:if (exam == 0) { hide_cursor(); program_viewer(); exam = 5; }
	default:
		process_program(); break;
	}
}

void process_studio() {//Ӱ����ѯ���������
	show_studio();
	int choice = choice_judge(4),exam=0;
	switch (catch_cursor(),choice)
	{
	case 0:break;
	case 1:printf("\n�����������ѯ�ķ�ӳ��ID�����ƣ�\n"); rewind(stdin); print_studio(search_studio(get_string(4, 6, 0))), go_on();
	case 2:if (exam == 0) { exam = 2; go_on(); }
	case 3:if (exam == 0) { add_studio();; exam = 3; }
	case 4:if(exam == 0){}
	default:
		process_studio(); break;
	}
}

///////////////////////////////////////////��ƱԱ

void process_conducter() {

}

void process_customer() {
	show_customer();
}

