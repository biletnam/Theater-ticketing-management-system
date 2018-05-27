#include"stdafx.h"
#include"statements.h"

void print_re() {//请求bug反馈
	printf("其实输出这句话是不可能的\n");
	printf("出现错误请联系开发者qvq  \nQQ740721665或863139668"); rewind(stdin);
}

void print_examinput() {//非法输入报错
	printf("输入不符合要求，请重新输入\n");
	rewind(stdin);
}

void go_on() {//按任意键继续
	rewind(stdin);
	getch();
}

void print_mallocX() {//malloc报错
	printf("不能分配更多内存了\n");
}