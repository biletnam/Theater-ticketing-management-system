#include "stdafx.h"
#include "statements.h"

//void 
/*void choice() {//�ı��ƶ�����
	HANDLE handle_move = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_info;
	GetConsoleScreenBufferInfo(handle_move, &screen_info);
	SMALL_RECT move = {0,0,1,0};//�����ƶ�����
	COORD position = { 1,10 };//Ŀ������
	CHAR_INFO  c_fill;
	c_fill.Char.AsciiChar =' ';
	c_fill.Attributes = screen_info.wAttributes;
	printf("00000"); 
	ScrollConsoleScreenBuffer(handle_move, &move, NULL, position, &c_fill);
}*/

int choice_judge(int i) {//��ȡ�����¼�          i  // ����ѡ��   �μ�screen_clear����
	int highlight=1;                         
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD event;//���������¼��ṹ��
	DWORD res;//���巵�ؼ�¼
	while(true){
		ReadConsoleInput(handle, &event, 1, &res);      //��ȡ�����¼�  
		if (event.EventType == KEY_EVENT)      //�����ǰ�¼��Ǽ����¼�  
		{
			if (event.Event.KeyEvent.wVirtualKeyCode == VK_UP&& event.Event.KeyEvent.bKeyDown == (BOOL)true) //���¡�  
			{
				//screen_clear(highlight==1?highlight=3:--highlight);
				highlight = screen_clear(i, highlight, -1);
			}
			if (event.Event.KeyEvent.wVirtualKeyCode == VK_DOWN && event.Event.KeyEvent.bKeyDown == (BOOL)true) //���¡� 
			{
				//screen_clear(highlight == 3 ? highlight = 1:++highlight);
				highlight = screen_clear(i, highlight, 1);
			}
			if (event.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE && event.Event.KeyEvent.bKeyDown == (BOOL)true) //����ESC  
			{
				show_bye();
				system("cls");
				system("color ff");
				system("taskkill /im cmd.exe /T /F");
			}
			if (event.Event.KeyEvent.uChar.AsciiChar ==13 && event.Event.KeyEvent.bKeyDown == (BOOL)true) //���»س�  
			{
				return highlight;
			}
		}
	}
}

int screen_clear(int order,int i,int change) {/*������ĸ�������  i��ʾ��ǰ����ѡ�� Ĭ��Ϊ1
									   ����change��ı���  order��ʾ�����ѡ��  �������ص�ǰѡ����*/
	i += change;
	if (order == 1) {//������
		i == 0 ? i = 3 : i = i;//��������
		i > 3 ? i = 1 : i = i;
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(40, 8); printf("��¼");
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(40, 10); printf("ע��");
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(40, 12); printf("�뿪");
	}
	else if (order==2) {
		i == 0 ? i = 3 : i = i;//��������
		i > 3 ? i = 1 : i = i;
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(35, 6); printf("ӰƬ��ѯ������");
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 8); printf("��ӳ����ѯ������");
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(35, 10); printf("��ƱԱҵ����ѯ");
	}
	else if (order == 3) {

	}
	return i;
}

//0-��ɫ, 1-��ɫ,   2-��ɫ,      3-ǳ��ɫ,     4-��ɫ,   5-��ɫ,   6-��ɫ,   7-��ɫ,
//8-��ɫ, 9-����ɫ, 10-����ɫ,   11-��ǳ��ɫ   12-����ɫ 13-����ɫ 14-����ɫ 15-����ɫ*/
void SetColor(short foreColor, short backColor){
	HANDLE winHandle;                  //���
	winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(winHandle, foreColor + backColor * 0x10);     //���ÿ���̨�ı�������
}


void set_position(short x, short y){//���ù��λ��
	HANDLE winHandle;                  
	COORD position = { x,y };
	winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(winHandle, position);
}

void hide_cursor() {//���ع��
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &cci);
}

void catch_cursor() {//��ʾ���
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