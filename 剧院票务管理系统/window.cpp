#include "stdafx.h"
#include "statements.h"


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
			if (event.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE && event.Event.KeyEvent.bKeyDown == (BOOL)true ) //����ESC  
			{
				if (i == 1) {//������ESCֱ���˳�
					show_bye();
					system("cls");
					system("color ff");
					system("taskkill /im cmd.exe /T /F");
				}
				else {
					return 0;//��Ϊ������һ��
				}
			}
			if (event.Event.KeyEvent.uChar.AsciiChar ==13 && event.Event.KeyEvent.bKeyDown == (BOOL)true) //���»س�  
			{
				SetColor(7, 0);
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
		i == 0 ? i = 5 : i = i;//��������
		i > 5 ? i = 1 : i = i;
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 6); printf("��Ŀ��ѯ������");
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 8); printf("Ӱ����ѯ������");
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 10); printf("�ݳ���ѯ������");
		i == 4 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 12); printf("Ʊ���ѯ������");
		i == 5?SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 14); printf("�ҵ��˺ż�����");
	}
	else if (order >= 3 && order <= 10) {
		char obj[5];
		switch (order) {
		case 3:strcpy(obj, "��Ŀ"); break;
		case 4:strcpy(obj, "Ӱ��"); break;
		case 5:strcpy(obj, "�û�"); break;
		case 6:strcpy(obj, ""); break;
		default:
			print_re(); break;
		}
		i == 0 ? i = 5 : i = i;
		i > 5 ? i = 1 : i = i;
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 6); printf("��ѯ%s��Ϣ",obj);
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 8); printf("�޸�%s��Ϣ",obj);
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 10); printf("����%s��Ϣ",obj);
		i == 4 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 12); printf("ɾ��%s��Ϣ",obj);
		i == 5 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 14); printf("�������%s",obj);
	}
	else if (order == 11) {
		i == 0 ? i = 2 : i = i;
		i > 2 ? i = 1: i = i;
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 6); printf("ϵͳ�û�����");
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 8); printf("��¼��¼��ѯ");
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 10); printf("�����ҵ���Ϣ");
	}
	else {
		print_re();
	}
	return i;
}

void select_seat(Studio *p) {//�б�λ��  �� -1   �� -2   �� 1    �� 2    ESC 0   �س�3
	set_position(0, 0);
	int choice, i = 0, j = 0;//  i ��ǰ����   j  ��ǰ����
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD position;
	position = info.dwCursorPosition;//����֤COORD�洢������λ��XΪ�ֽ���  YΪ����
	while (choice = turn_page()) {
		if (choice == -1 && i != 0) {
			position.Y--;
		}
		else if (choice == -2 && j != 0) {//�� -1   �� -2   �� 1    �� 2    ESC 0   �س�3
			position.X -= 2;
		}
		else if (choice == 1 && i != p->element.seatx) {
			position.Y++;
		}
		else if (choice == 2 && j != p->element.seaty) {
			position.X += 2;
		}
		else if (choice == 0) {
			return;
		}
		else if (choice == 3) {
			
		}
	}
	//return position;
}

void clear_seat(COORD position,int status) {//COORD  ��ǰλ��   status ��λ״̬
	set_position(position);
	SetColor(7, 12);
	switch (status) {//��λ0   ����1    ��9
	case 0:printf("��"); break;
	case 1:printf("��"); break;
	case 9:printf("  "); break;
	}
}

int turn_page() {//��ҳ��     �� -1   �� -2   �� 1    �� 2    ESC 0   �س�3
	int highlight = 1;
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD event;//���������¼��ṹ��
	DWORD res;//���巵�ؼ�¼
	while (true) {
		ReadConsoleInput(handle, &event, 1, &res);      //��ȡ�����¼�  
		if (event.EventType == KEY_EVENT){      //�����ǰ�¼��Ǽ����¼�  
			if (event.Event.KeyEvent.wVirtualKeyCode == VK_UP && event.Event.KeyEvent.bKeyDown == (BOOL)true) {//���¡�  
				return -1;
			}
			else if (event.Event.KeyEvent.wVirtualKeyCode == VK_LEFT && event.Event.KeyEvent.bKeyDown == (BOOL)true) {
				return -2;
			}
			else if (event.Event.KeyEvent.wVirtualKeyCode == VK_DOWN && event.Event.KeyEvent.bKeyDown == (BOOL)true) {//���¡� 
				return 1;
			}
			else if (event.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT && event.Event.KeyEvent.bKeyDown == (BOOL)true) {//���¡� 
				return 2;
			}
			else if (event.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE && event.Event.KeyEvent.bKeyDown == (BOOL)true) //����ESC  
			{
				return 0;
			}
			else if (event.Event.KeyEvent.uChar.AsciiChar == 13 && event.Event.KeyEvent.bKeyDown == (BOOL)true) {//���»س�  
				return 3;
			}
		}
	}
}

//0-��ɫ, 1-��ɫ,   2-��ɫ,      3-ǳ��ɫ,     4-��ɫ,   5-��ɫ,   6-��ɫ,   7-��ɫ,
//8-��ɫ, 9-����ɫ, 10-����ɫ,   11-��ǳ��ɫ   12-����ɫ 13-����ɫ 14-����ɫ 15-����ɫ*/
void SetColor(short foreColor, short backColor){
	HANDLE winHandle;                  //���
	winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(winHandle, foreColor + backColor * 0x10);     //���ÿ���̨�ı�������
}

POINT get_position() {//�õ���ǰ�������
	POINT point;
	GetCursorPos(&point);
	return point;
}

void set_position(short x, short y){//���ù��λ��
	HANDLE winHandle;                  
	COORD position = { x,y };
	winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(winHandle, position);
}

void set_position(COORD position) {//���ù��λ��
	HANDLE winHandle;
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