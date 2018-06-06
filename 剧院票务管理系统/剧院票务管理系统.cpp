// 剧院票务管理系统.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"statements.h"
List list; 
data_account PRESENT;//当前用户
int main()
{
	initialize();
	//show_welcome();
	//seat_changer(list.studio_head->next);
	//print_studio(list.studio_head->next); go_on();
	print_instruction(1);
	process_all();
    return 0;
}

