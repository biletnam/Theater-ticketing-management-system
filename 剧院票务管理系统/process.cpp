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
		process_all();
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
	case 0:account_appeal();//账号申诉
	case 1:process_admin(); break;
	case 2:process_manager(); break;
	case 3:process_conducter(); break;
	case 4:process_customer(); break;
	default:
			print_re(); go_on(); exit(1);
		break;
	}
}

void process_admin() {//管理员过程
	show_admin();
	int choice = choice_judge(7), exam = 0;
	switch (choice) {
	case 0:break;
	case 1:process_acount(); exam = 1;
	default:
		process_admin(); break;
	}
}

void process_acount() {//账户管理过程        //在这里调用你写的链表操作
	show_account();
	int choice = choice_judge(5), exam = 0;
	switch (choice) {
	case 0:break;
	case 1:
	default:
		process_acount(); break;
	}
}

///////////////////////////////////////剧院经理

void process_manager() {//剧院经理过程
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

void process_program() {//剧目查询及管理过程
	show_program();
	int choice = choice_judge(3),exam=0;
	switch (catch_cursor(),choice) {
	case 0:break;
	case 1:printf("\n请输入要查询的影片ID或名称:\n"); rewind(stdin); print_program(search_program(get_string(1, 30, 0)),1); exam = 1; go_on();
	case 2:if (exam == 0) { printf("\n请输入要修改的影片ID或名称:\n"); rewind(stdin); modify_program(search_program(get_string(1, 30, 0))); exam = 2; go_on();}
	case 3:if (exam == 0) { add_program(); exam = 3; }
	case 4:if (exam == 0) { printf("\n请输入要删除的影片ID或名称:\n"); rewind(stdin); kill_program(search_program(get_string(1,30,0))); exam = 4; go_on();}
	case 5:if (exam == 0) { hide_cursor(); program_viewer(); exam = 5; }
	default:
		process_program(); break;
	}
}

void process_studio() {//影厅查询及管理过程
	show_studio();
	int choice = choice_judge(4),exam=0;
	switch (catch_cursor(),choice)
	{
	case 0:break;
	case 1:printf("\n请输入你想查询的放映厅ID或名称：\n"); rewind(stdin); print_studio(search_studio(get_string(4, 6, 0))), go_on();
	case 2:if (exam == 0) { exam = 2; go_on(); }
	case 3:if (exam == 0) { add_studio();; exam = 3; }
	case 4:if(exam == 0){}
	default:
		process_studio(); break;
	}
}

///////////////////////////////////////////售票员

void process_conducter() {

}

void process_customer() {
	show_customer();
}

