#include "stdafx.h"
#include "statements.h"

//void 
/*void choice() {//文本移动函数
	HANDLE handle_move = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_info;
	GetConsoleScreenBufferInfo(handle_move, &screen_info);
	SMALL_RECT move = {0,0,1,0};//定义移动区域
	COORD position = { 1,10 };//目标区域
	CHAR_INFO  c_fill;
	c_fill.Char.AsciiChar =' ';
	c_fill.Attributes = screen_info.wAttributes;
	printf("00000"); 
	ScrollConsoleScreenBuffer(handle_move, &move, NULL, position, &c_fill);
}*/

int choice_judge(int i) {//读取键盘事件          i  // 界面选择   参见screen_clear界面
	int highlight=1;                         
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD event;//定义输入事件结构体
	DWORD res;//定义返回记录
	while(true){
		ReadConsoleInput(handle, &event, 1, &res);      //读取输入事件  
		if (event.EventType == KEY_EVENT)      //如果当前事件是键盘事件  
		{
			if (event.Event.KeyEvent.wVirtualKeyCode == VK_UP&& event.Event.KeyEvent.bKeyDown == (BOOL)true) //按下↑  
			{
				//screen_clear(highlight==1?highlight=3:--highlight);
				highlight = screen_clear(i, highlight, -1);
			}
			if (event.Event.KeyEvent.wVirtualKeyCode == VK_DOWN && event.Event.KeyEvent.bKeyDown == (BOOL)true) //按下↓ 
			{
				//screen_clear(highlight == 3 ? highlight = 1:++highlight);
				highlight = screen_clear(i, highlight, 1);
			}
			if (event.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE && event.Event.KeyEvent.bKeyDown == (BOOL)true) //按下ESC  
			{
				show_bye();
				system("cls");
				system("color ff");
				system("taskkill /im cmd.exe /T /F");
			}
			if (event.Event.KeyEvent.uChar.AsciiChar ==13 && event.Event.KeyEvent.bKeyDown == (BOOL)true) //按下回车  
			{
				return highlight;
			}
		}
	}
}

int screen_clear(int order,int i,int change) {/*主界面的高亮控制  i表示当前高亮选项 默认为1
									   参数change表改变量  order表示界面的选择  函数返回当前选项编号*/
	i += change;
	if (order == 1) {//主界面
		i == 0 ? i = 3 : i = i;//高亮控制
		i > 3 ? i = 1 : i = i;
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(40, 8); printf("登录");
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(40, 10); printf("注册");
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(40, 12); printf("离开");
	}
	else if (order==2) {
		i == 0 ? i = 3 : i = i;//高亮控制
		i > 3 ? i = 1 : i = i;
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(35, 6); printf("影片查询及管理");
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 8); printf("放映厅查询及管理");
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(35, 10); printf("售票员业绩查询");
	}
	else if (order == 3) {

	}
	return i;
}

//0-黑色, 1-蓝色,   2-绿色,      3-浅绿色,     4-红色,   5-紫色,   6-黄色,   7-白色,
//8-灰色, 9-淡蓝色, 10-淡绿色,   11-淡浅绿色   12-淡红色 13-淡紫色 14-淡黄色 15-亮白色*/
void SetColor(short foreColor, short backColor){
	HANDLE winHandle;                  //句柄
	winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(winHandle, foreColor + backColor * 0x10);     //设置控制台文本的属性
}


void set_position(short x, short y){//设置光标位置
	HANDLE winHandle;                  
	COORD position = { x,y };
	winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(winHandle, position);
}

void hide_cursor() {//隐藏光标
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &cci);
}

void catch_cursor() {//显示光标
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = TRUE;
	SetConsoleCursorInfo(hOut, &cci);
}
/*
void Clear(int x, int y, int rowCount)
{
	int i, j;
	for (i = 0; i<rowCount; ++i)
	{
		SetPosition(x, y + i);
		for (j = 0; j<70; ++j)
			printf(" ");
	}
}
*/