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
	USER_frozen = 5,//����״̬
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
	TICKET_reserve = 2,//Ԥ��
}ticket_statuses;

typedef enum {
	SALE_sold=1,//��Ʊ
	SALE_return=2,//��Ʊ
}sale_types;

//////////////////////////////////////�ṹ����\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

typedef struct {
	int year;
	int month;
	int day;
}date_status;//���ڽṹ��

typedef struct {
	int hour;
	int minute;
}time_status;//ʱ��ṹ��

////////////////////////////////////////���ж���
typedef struct linklist_seat {
	int stduio_ID;//��λ���ڷ�ӳ�����
	int seatx;//��λ������
	int seaty;//��λ������
	seat_conditions seat_condition;//λ��״̬   �μ�enum seat_conditions
	struct linklist_seat *pre, *next;
}Seat;

typedef struct linklist_ticket {
	int ticket_ID;//�볡ȯ���
	//int plan_ID;//�ݳ��ƻ����
	int seatx;//��λ������
	int seaty;//��λ������
	int price;//Ʊ��    ��Ŀ����
	ticket_statuses ticket_status;//Ʊ��״̬     �μ�enum tickets_statuses
	struct linklist_ticket *pre, *next;
}Ticket;

typedef struct linklist_record{//���׼�¼
	long record_ID;//���׼�¼ID
	int conductor_ID;//��ƱԱID      ��Ա�˻�
	int plan_ID;//�ݳ��ƻ�ID
	int ticket_ID;//ƱID
	date_status date;//��������
	time_status time;//����ʱ��
	int price;//Ʊ��
	sale_types sale_type;//��������
	struct linklist_record *pre, *next;
}Record;

//////////////////////////////////////ʵ����������\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

typedef struct em{//��Ŀ������
	char program_ID[NAME/2];//��λ����  ��Ŀ���
	char program_name[NAME * 2 + 1];//15����    ��Ŀ����
	program_types program_type;//��Ŀ����  �μ�enum program_typesö�ٶ���
	program_ratings program_rating;//��Ŀ�ȼ� �μ�program_ratingsö�ٶ���
	char director[NAME];//7������     ����   ���ֻ�Ϊָ��
	char performer[2][NAME];//7������      ����   ����
	date_status start_date; //��ӳ����   �μ�date_status�ṹ�嶨��
	date_status end_date; //��������   �μ�date_status�ṹ�嶨��
	int duration;//��Ŀʱ��       minute   [1,600]
	char  label[5];//��Ŀ��ǩ   ����  ϲ��  ����   ��� 
	char area[5];//����   2������
	char language[NAME];//����
	int price;//Ʊ��   [5,100]
	int cost;//��ӳ�ɱ�    ����Ԫ)
}data_program;

typedef struct emm {
	char studio_ID[NAME/2];//�����λ����   ��ӳ�����
	char studio_name[NAME];//����߸�����    ��ӳ������
	int seatx;//5~12
	int seaty;//10~25  ��ӳ����λ ���к���    ��������   �������ö�ά����
	Seat *seat_head, *seat_tail;//������
}data_studio;

typedef struct emmm {//�ݳ��ƻ�������
	int plan_ID;//�ݳ��ƻ����
	int play_ID;//��Ŀ���
	int studio_ID;//��ӳ�����
	date_status date; //�ݳ�����   �μ�date_status�ṹ�嶨��
	time_status time;//��ʼʱ��    �μ�time_status�ṹ�嶨��  24Сʱ��
	Ticket *ticket_head, *ticket_tail;//������
}data_plan;

typedef struct emmmm {//�˺�������
	char UID[NAME-2];//�˺ű��   12λ   �����޸�������һ�����
	char username[NAME];//�û���   4~14���ַ�/2~7������
	char password[PASSWORD+1];//��¼����  6~12
	user_types user_type;//�˺�����     �μ�enum user_typesö�ٶ���
	long long contributions;//       ҵ��\�����
	Record *record_head, *record_tail;//���ۼ�¼�������¼������
}data_account;

/////��ȡ���ۼ�¼ʱ����ҵ��      �������ۼ�¼ʱʵʱ����     ��������ʱ�������¼���
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



typedef struct ctrl {//��������
	Program *program_head,*program_tail;
	Studio *studio_head,*studio_tail;
	Plan *plan_head,*plan_tail;
	Account *account_head,*account_tail;
}List;

////////////////////////////////////////ȫ�ֱ���\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

extern List list;
extern data_account PRESENT;


/////////////////////////////////////////����\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

int choice_judge(int i);//��ȡ�����¼�  �ж�ѡ��
void set_position(short x, short y);//���ù��λ��
void set_position(COORD position);//���ù��λ��
void SetColor(short foreColor, short backColor);//����������ɫ
void hide_cursor();//���ع��
void catch_cursor();//��ʾ���
POINT get_position();//�õ���ǰ���y����
int screen_clear(int order, int i, int change);/*������ĸ�������  i��ʾ��ǰ����ѡ�� Ĭ��Ϊ1
										����change��ı���  order��ʾ�����ѡ��  �������ص�ǰѡ����*/
int turn_page();//��ҳ��
int select_seat(Studio *p);//�б�λ��  �� -1   �� -2   �� 1    �� 2    ESC 0   �س�3  
void clear_seat(COORD position, char status);//�ı���λ��ʾ  COORD  ��ǰλ��   status ��λ״̬

//window.cpp

void show_welcome();//��ӭ����
void show_main();//������
void show_sign();//��¼����
void show_bye();//�ټ�����
void show_customer();//�˿�������
void show_manager();//��Ժ����������
void show_program();//��Ŀ��ѯ���������
void show_studio();//Ӱ����ѯ���������

void show_admin();//ϵͳ����Ա������
void show_account();//�˻��������
//welcom.cpp

void print_re();
void print_examinput();//�Ƿ����뱨��
void go_on();//�����������
void exam_mallocX(void *p);//malloc����
int enquiry(int i);//�ж��Ƿ���б��β���   i==1   enquiry   i==2 warnning
void print_ok(); //��ʾ�����ɹ�
void print_instruction(int i);//��ʾ����˵��
//friendly.cpp

void process_all();//�������
void process_sign();//��¼����
void process_admin();//����Ա����
void process_acount();//�˻��������

void process_manager();//��Ժ�������
void process_program();//��Ŀ��ѯ���������
void process_studio();//Ӱ����ѯ���������
void process_plan();//��ӳ�ƻ���ѯ���������

void process_conducter();//��ƱԱ����
void process_customer();//�˿͹���

void account_appeal();//�˺����߹���
//process.cpp

char *username_get(int judge);//�û����Ļ�ȡ
int sign_judge();//��½�ɹ����˻����͵��ж�
char *password_get(int judge);//�û�����Ļ�ȡ
char *get_string(int down, int up,int judge);//�ַ�����麯��    down~up   �ַ����ֽ�������
int get_num(int down, int up, int ndown, int nup);//��ȡ����    ���������   ��Χ[down,up]   λ��n[ndown,nup]
date_status get_date();//���ڵĻ�ȡ���ж�
time_status get_time();//ʱ��Ļ�ȡ���ж�
data_program get_program_infomation();//��ȡ��Ŀ��Ҫ��Ϣ  �����г�ʼ��
void program_viewer();//��Ŀ�����
void studio_viewer();//��ӳ���鿴��
void seat_changer(Studio *p);//���ӻ���λ�޸���

//sonfunction.cpp


void import_account();//�����˺���Ϣ
void import_program();//�����Ŀ��Ϣ
void import_studio_and_seat();//�����ӳ������λ��Ϣ


void save_program();//�����Ŀ��Ϣ���ļ�
void save_studio_and_seat();//�����ӳ������λ���ļ�
//filefunction.cpp

void initialize_linklist();//��ʼ������

Program *search_program(char *obj, int judge);//��ID�����Ʋ��Ҿ�Ŀ judge �����Ƿ�������Ʒ���
void add_program();//���Ӿ�Ŀ
void kill_program(Program *p);//����ID������ɾ����Ŀ
void print_program(Program *p , int i);////���ĳ��ӰƬ��Ϣ
void modify_program(Program *p);//�޸�ӰƬ��Ϣ

Studio *search_studio(char *obj, int judge);//��ID�����Ʋ��ҷ�ӳ��    judge �����Ƿ�������Ʒ���
void add_studio();//���ӷ�ӳ��
void print_studio(Studio *p);////��ӡ��ӳ������λ��Ϣ

//Seat *search_seat(char *obj);//���ݷ�ӳ����Ų�����λ
void delete_seat(Studio *k);//ɾ����ӳ��ʱɾ������λ
void kill_studio(Studio *p);//ɾ��ָ����ӳ��
void modify_studio(Studio *p);//�޸ķ�ӳ�����Ƽ���λ

void initialize_seat(Studio *p);//Ϊ�·�ӳ����ʼ����λ

//Linklist.cpp

void import_all();//�����˻���Ϣ
void initialize();//��ʼ��׼��
void initialize_present();//��ʼ����ǰ�˻�
void initialize_window();//��ʼ����ʾ����

//initialize.cpp