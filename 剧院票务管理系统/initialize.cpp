#include"stdafx.h"
#include"statements.h"

void import_all() {//导入所有信息
	import_account();
	import_program();
	import_studio_and_seat();
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
	PRESENT.user_type = USER_unkown;
}

void initialize_window() {//初始化窗口大小
	system("mode 88, 25");
}