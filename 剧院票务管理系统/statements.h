#pragma once
//////////////////////////////////////��̬ȫ�ֱ���\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

const int NAME = 15, PASSWORD = 12;


//////////////////////////////////////ö�����Ͷ���\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

typedef enum {//�����Ŀö������
	PROGRAM_movie = 1,//��Ӱ
	PROGRAM_opera = 2,//���
	PROGRAM_concert = 3//���ֻ�
}program_types;

typedef enum {//�����˻�ö������
	USER_admin = 1,
	USER_manager = 2,
	USER_conductor = 3,
	USER_customer = 4,
	USER_unkown = 5,
}user_types;

typedef enum {//�����Ӱ�ּ�ö������
	RATING_child = 1,//��ͯ�ɹۿ�
	RATING_teens = 2,//������ɹۿ�
	RATING_adult = 3//���˿ɹۿ�
}program_ratings;

typedef enum {//������λ���ö������
	SEAT_none = 0,	//��λ
	SEAT_available = 1,//����λ
	SEAT_private=2,//����
	SEAT_unrepaired = 9//�𻵵���λ
}seat_conditions;

typedef enum {
	TICKET_available=0,//����
	TICKET_sold = 1,//����
	TICKET_reserve = 3,//Ԥ��
}ticket_statuses;

//////////////////////////////////////ʵ����������\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

typedef struct em{//��Ŀ������
	int program_ID;//  ��Ŀ���
	char program_name[NAME * 2 + 1];//15����    ��Ŀ����
	program_types type;//��Ŀ����  �μ�enum program_typesö�ٶ���
	program_ratings rating;//��Ŀ�ȼ� �μ�program_ratingsö�ٶ���
	char director[NAME * 2 + 1];//15����     ����
	char start_date[PASSWORD-1]; //��ӳ����   ��ʽ2018-05-12  ��ȷ���볤��Ϊ10
	char end_date[PASSWORD - 1]; //��������   ��ʽ2018-05-12  ��ȷ���볤��Ϊ10
	int duration;//��Ŀʱ��       minute
	char  label[3][5];//��Ŀ��ǩ   ϲ��  ����   ��� �������
	char language[NAME];//����
	int price;//Ʊ��
	int cost;//��ӳ�ɱ�
}data_program;

typedef struct emm {
	int studio_ID;//   ��ӳ�����
	char studio_name[NAME];//�߸�����    ��ӳ������
	int seatx;
	int seaty;//��ӳ����λ ���к���    ��������   �������ö�ά����
}data_studio;

typedef struct emmm {//�ݳ��ƻ�������
	int plan_ID;//�ݳ��ƻ����
	int play_ID;//��Ŀ���
	int studio_ID;//��ӳ�����
	char date[PASSWORD - 1]; //�ݳ�����   ��ʽ2018-05-12  ��ȷ���볤��Ϊ10
	char time[PASSWORD];//��ֹʱ��    20:00-21:30   ��ȷ���볤��11
}data_plan;

typedef struct emmmm {//�˺�������
	int UID;//�˺ű��   �����޸�������һ�����
	char username[NAME];//�û���   4~14���ַ�/2~7������
	char password[PASSWORD+1];//��¼����  6~12
	user_types user_type;//�˺�����     �μ�enum user_typesö�ٶ���
	long long contributions;//       ҵ��\�����
}data_account;


////////////////////////////////////////ʵ�嶨��\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


typedef struct linklist_program {//��Ŀ
	data_program element;
	struct linklist_program *pre,*next;
}Program;

typedef struct linklist_studio {//��ӳ��
	data_studio element;
	struct linklist_studio *pre, *next;
}Studio;

typedef struct linklist_plan {//�ݳ��ƻ�
	data_plan element;
	struct linklist_plan *pre, *next;
}Plan;

typedef struct linklist_account {//�˺�
	data_account element;
	struct linklist_account *pre, *next;
}Account;


typedef struct linklist_seat {
	int seat_ID;//��λ���
	int stduio_ID;//��λ���ڷ�ӳ�����
	int seatx;//��λ������
	int seaty;//��λ������
	seat_conditions seat_condition;//��λ״��   �μ�enum seat_conditions
	struct linklist_seat *pre, *next;
}Seat;

typedef struct linklist_ticket {
	int ticket_ID;//�볡ȯ���
	int plan_ID;//�ݳ��ƻ����
	int seat_ID;//��λ���
	int price;//Ʊ��    ��Ŀ����
	ticket_statuses ticket_status;//Ʊ��״��     �μ�enum tickets_statuses
	struct linklist_ticket *pre, *next;
}Ticket;

typedef struct ctrl {//��������
	Program *program_head,*program_tail;
	Studio *studio_head,*studio_tail;
	Seat *seat_head,*seat_tail;
	Ticket *ticket_head, *ticket_tail;
	Plan *plan_head,*plan_tail;
	Account *account_head,*account_tail;
}List;

////////////////////////////////////////ȫ�ֱ���\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

extern List list;
extern data_account PRESENT;


/////////////////////////////////////////����\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

int choice_judge();//��ȡ�����¼�  �ж�ѡ��
void set_position(short x, short y);//���ù��λ��
void SetColor(short foreColor, short backColor);//����������ɫ
void hide_cursor();//���ع��
void catch_cursor();//��ʾ���

//window.cpp

void show_welcome();//��ӭ����
void show_main();//������

int screen_clear(int order,int i,int change);/*������ĸ�������  i��ʾ��ǰ����ѡ�� Ĭ��Ϊ1
									   ����change��ı���  order��ʾ�����ѡ��  �������ص�ǰѡ����*/

void show_sign();//��¼����
void show_bye();//�ټ�����
void show_customer();//�˿�������

//welcom.cpp

void print_re();
void print_examinput();//�Ƿ����뱨��
void go_on();//�����������
void print_mallocX();//malloc����

//friendly.cpp

void process_all();//�������
void process_sign();//��¼����
void process_admin();//����Ա����
void process_manager();//��Ժ�������
void process_conducter();//��ƱԱ����
void process_customer();//�˿͹���

void process_accountAppeal();//�˺����߹���
//process.cpp

char *username_get(int judge);//�û����Ļ�ȡ
int sign_judge();//��½�ɹ����˻����͵��ж�
char *password_get(int judge);//�û�����Ļ�ȡ

//sonfunction.cpp


void import_account();//�����˺���Ϣ
//filefunction.cpp

void initialize_linklist();//��ʼ������
//Linklist.cpp

void import_all();//�����˻���Ϣ
void initialize();//��ʼ��׼��
void initialize_present();//��ʼ����ǰ�˻�
void initialize_window();//��ʼ����ʾ����

//initialize.cpp