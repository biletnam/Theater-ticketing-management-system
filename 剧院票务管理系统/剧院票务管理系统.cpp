// ��ԺƱ�����ϵͳ.cpp: �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include"statements.h"
List list; 
data_account PRESENT;//��ǰ�û�
struct tm *now;
int main(){
	PlaySound(_T("C:\\Users\\HP\\Desktop.\\�� �� �� ʿ �� �� �� - �� �� �� �� �� �� �� Ӱ Ժ.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NOWAIT);
	//show_welcome();
	initialize();
	//print_instruction(1);
	process_all();
	//process_plan();
    return 0;
}

