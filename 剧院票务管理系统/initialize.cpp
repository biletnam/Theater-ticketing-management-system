#include"stdafx.h"
#include"statements.h"

void import_all() {//����������Ϣ
	import_account();
	import_program();
	import_studio_and_seat();
}

void initialize() {//ȫ����ʼ��
	initialize_window();
	initialize_linklist();
	initialize_present();
	import_all();

}

void initialize_present() {//��ʼ����ǰ�˻�
	PRESENT.UID[0] = '\0';
	PRESENT.username[0] = PRESENT.password[0] = '\0';
	PRESENT.user_type = USER_unkown;
}

void initialize_window() {//��ʼ�����ڴ�С
	system("mode 88, 25");
}