#include"stdafx.h"
#include"statements.h"

void process_all() {//登录过程
	show_main();
	int choice = choice_judge(1);
	switch (choice) {
	case 1:process_sign(); break;
	case 2:break;
	case 3:show_bye(); exit(0);
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
	int choice;
	while (true) {
		show_admin();
		choice = choice_judge(7);
		switch (choice) {
		case 0:break;
		case 1:process_acount(); break;
		}if (choice == 0)break;
	}
}

void process_acount() {//账户管理过程        //在这里调用你写的链表操作
	int choice; //char *str;
	while (true) {
		show_account();
		choice = choice_judge(5);
		switch (choice) {
		case 0:break;
		case 1:break;
		}
		if (choice == 0)break;
	}
}

///////////////////////////////////////剧院经理

void process_manager() {//剧院经理过程
	int choice;
	while (true) {
		show_manager();
		choice = choice_judge(2);
		switch (choice) {
		case 0:break;
		case 1:process_program(); break;
		case 2: process_studio(); break;
		case 3:break;
		case 4:break;
		}if (choice == 0) {
			catch_cursor(); printf("\n是否退出登录?(0/1):");
			choice = get_num(0, 1, 1, 1); if (choice == 1){go_on(); break;} go_on();
		}
	}
}

void process_program() {//剧目查询及管理过程
	int choice; char *str;
	while (true) {
		show_program();
		choice = choice_judge(3);
		if (choice != 0)catch_cursor();
		switch (choice) {
		case 0:break;
		case 1:printf("\n请输入要查询的影片ID或名称:\n"); rewind(stdin); print_program(search_program(str = get_string(1, 30, 0), 1), 1); free(str); go_on(); break;
		case 2:printf("\n请输入要修改的影片ID或名称:\n"); rewind(stdin); modify_program(search_program(str = get_string(1, 30, 0), 1)); free(str); go_on(); break;
		case 3:add_program(); break;
		case 4:printf("\n请输入要删除的影片ID或名称:\n"); rewind(stdin); kill_program(search_program(str = get_string(1, 30, 0), 1)); free(str); go_on(); break;
		case 5:hide_cursor(); program_viewer(); break;
		}if (choice == 0)break;
	}
}

void process_studio() {//影厅查询及管理过程
	int choice; char *str = NULL;
	while (true) {
		show_studio();
		choice = choice_judge(4); 
		if(choice != 0)catch_cursor();
		switch (choice){
		case 0:break;
		case 1:printf("\n请输入要查询的放映厅ID或名称：\n"); rewind(stdin); print_studio(search_studio(str = get_string(4, 6, 0), 1)); free(str); go_on(); break;
		case 2: go_on(); break;
		case 3:add_studio(); go_on(); break;
		case 4:printf("\n请输入要删除的放映厅ID或名称：\n"); kill_studio(search_studio(str = get_string(4, 6, 0), 1)); free(str); go_on(); break;
		case 5:hide_cursor(); studio_viewer(); break;
		}if (choice == 0)break;
	}
}

///////////////////////////////////////////售票员

void process_conducter() {

}

void process_customer() {
	show_customer();
}

