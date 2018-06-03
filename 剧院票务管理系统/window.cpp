#include "stdafx.h"
#include "statements.h"


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
			if (event.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE && event.Event.KeyEvent.bKeyDown == (BOOL)true ) //按下ESC  
			{
				if (i == 1) {//主界面ESC直接退出
					show_bye();
					system("cls");
					system("color ff");
					system("taskkill /im cmd.exe /T /F");
				}
				else {
					return 0;//最为返回上一层
				}
			}
			if (event.Event.KeyEvent.uChar.AsciiChar ==13 && event.Event.KeyEvent.bKeyDown == (BOOL)true) //按下回车  
			{
				SetColor(7, 0);
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
		i == 0 ? i = 4 : i = i;//高亮控制
		i > 4 ? i = 1 : i = i;
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 6); printf("剧目查询及管理");
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 8); printf("影厅查询及管理");
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 10); printf("计划查询及管理");
		i == 4 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 12); printf("票务查询及管理");
	}
	else if (order >= 3 && order <= 6) {
		char obj[5];
		switch (order) {
		case 3:strcpy(obj, "剧目"); break;
		case 4:strcpy(obj, "影厅"); break;
		case 5:strcpy(obj, "用户"); break;
		case 6:strcpy(obj, ""); break;
		default:
			print_re(); break;
		}
		i == 0 ? i = 5 : i = i;
		i > 5 ? i = 1 : i = i;
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 6); printf("查询%s信息",obj);
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 8); printf("修改%s信息",obj);
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 10); printf("新增%s信息",obj);
		i == 4 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 12); printf("删除%s信息",obj);
		i == 5 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 14); printf("浏览%s信息",obj);
	}
	else if (order == 7) {
		i == 0 ? i = 2 : i = i;
		i > 2 ? i = 1: i = i;
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 6); printf("系统用户管理");
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 8); printf("登录记录查询");
	}
	else {
		print_re();
	}
	return i;
}

int turn_page() {//翻页器
	int highlight = 1;
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD event;//定义输入事件结构体
	DWORD res;//定义返回记录
	while (true) {
		ReadConsoleInput(handle, &event, 1, &res);      //读取输入事件  
		if (event.EventType == KEY_EVENT)      //如果当前事件是键盘事件  
		{
			if ((event.Event.KeyEvent.wVirtualKeyCode == VK_UP || event.Event.KeyEvent.wVirtualKeyCode == VK_LEFT) && event.Event.KeyEvent.bKeyDown == (BOOL)true) //按下↑  
			{
				return -1;
			}
			if ((event.Event.KeyEvent.wVirtualKeyCode == VK_DOWN || event.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT) && event.Event.KeyEvent.bKeyDown == (BOOL)true) //按下↓ 
			{
				return 1;
			}
			if (event.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE && event.Event.KeyEvent.bKeyDown == (BOOL)true) //按下ESC  
			{
				return 0;
			}
		}
	}
}

//0-黑色, 1-蓝色,   2-绿色,      3-浅绿色,     4-红色,   5-紫色,   6-黄色,   7-白色,
//8-灰色, 9-淡蓝色, 10-淡绿色,   11-淡浅绿色   12-淡红色 13-淡紫色 14-淡黄色 15-亮白色*/
void SetColor(short foreColor, short backColor){
	HANDLE winHandle;                  //句柄
	winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(winHandle, foreColor + backColor * 0x10);     //设置控制台文本的属性
}

int get_positionx() {//得到当前光标x坐标
	POINT point;
	GetCursorPos(&point);
	return (int)point.x;
}

int get_positiony() {//得到当前光标y坐标
	POINT point;
	GetCursorPos(&point);
	return (int)point.y;
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