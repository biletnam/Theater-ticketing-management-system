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

int enquiry() {//判断是否进行本次操作
	printf("是否确认本次操作？(0/1)\n");
	rewind(stdin);
	int judge = 0;
	do {
		scanf("%d", &judge);
		if (judge != 0 && judge != 1) {
			print_examinput();
		}
	} while (judge != 0 && judge != 1);
	return judge;
}

void print_ok() {//提示操作成功
	printf("操作成功了的说!\n");
	rewind(stdin);
}


