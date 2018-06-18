// 剧院票务管理系统.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"statements.h"
List list; 
data_account PRESENT;//当前用户
struct tm *now;
int main(){
	PlaySound(_T("C:\\Users\\HP\\Desktop.\\银 河 骑 士 李 老 板 - 嘉 禾 天 橙 国 际 大 影 院.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NOWAIT);
	//show_welcome();
	initialize();
	//print_instruction(1);
	process_all();
	//process_plan();
    return 0;
}

