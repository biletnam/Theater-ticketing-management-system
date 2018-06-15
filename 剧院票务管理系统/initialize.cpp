#include"stdafx.h"
#include"statements.h"

void import_all() {//导入所有信息
	import_key();
	import_account();
	import_program();
	import_studio_and_seat();
//	import_plan_and_ticket();
}

void initialize() {//全部初始化
	initialize_window();
	initialize_linklist();
	initialize_present();
	import_all();

}

void initialize_present() {//初始化当前账户
	PRESENT.UID[0] = '\0';
	PRESENT.username[0] = PRESENT.password[0] = '\0';
	PRESENT.user_type = USER_frozen;
}

void initialize_window() {//初始化窗口大小//与字体大小
	system("mode 88, 25");
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD font = { 12,24 };
	//GetConsoleScreenBufferInfo;
}