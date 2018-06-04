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
	printf("按任意键继续\n");
	rewind(stdin);
	getch();
	getch();
}

void exam_mallocX(void *p) {//malloc报错
	if (p == NULL) {
		printf("不能分配更多内存了\n");
		exit(1);
	}
}

int enquiry(int i) {//判断是否进行本次操作   i==1   enquiry   i==2 warnning
	if (i == 1)
		printf("是否确认本次操作?(0/1):");
	else if (i == 2)
		printf("该操作不可恢复，是否继续?(0/1):");
	else
		print_re();
	rewind(stdin);
	int judge = 0;
	judge = get_num(0,1,1,1);
	return judge;
}

void print_ok() {//提示操作成功
	printf("操作成功了的说!\n");
	rewind(stdin);
}


//弃用

//void print_label(int i) {//打印标签列表     i  = 1 电影       2 歌剧        3音乐会
//	if (i == 1)
//	printf("喜剧 动作 惊悚 爱情 悬疑 恐怖\n\
//纪录 科幻 艺术 青春 耽美 动画\n");
//	else if (i == 2) 
//	printf("请选择标签:");
//	rewind(stdin);
//}
