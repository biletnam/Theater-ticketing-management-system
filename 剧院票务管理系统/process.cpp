#include"stdafx.h"
#include"statements.h"

void process_all() {//登录过程
	show_main();
	int choice=choice_judge(1),exam=0;
	switch (choice) {
	case 1:if (exam == 0) { process_sign(); exam = 1; }
	case 2:if(exam==0){}
	case 3:if (exam == 0) { show_bye(); exit(0); exam = 3; }
	default:
		if(exam==0)print_re();
		break;
	}
}

//USER_admin = 1,
//USER_manager = 2,
//USER_conductor = 3,
//USER_customer = 4,
//USER_unkown = 5,

void process_sign() {//登录过程
	int re = 0, cnt = 0;
	re = sign_judge();
	while ((re <= 0 || re > 4) && cnt < 3) {
		cnt++;
		re = sign_judge();
	}
	switch (re) {
	case 0:process_accountAppeal();//账号申诉
	case 1:process_admin(); break;
	case 2:process_manager(); break;
	case 3:process_conducter(); break;
	case 4:process_customer(); break;
	default:
			print_re(); go_on(); exit(1);
		break;
	}
}

void process_admin() {

}

void process_manager() {//管理员过程
	show_manager();
	int choice = choice_judge(2);
	switch (choice) {
	case 1:
	case 2:
	}
}

void process_conducter() {

}

void process_customer() {
	show_customer();
}

void process_accountAppeal() {

}