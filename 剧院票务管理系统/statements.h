#pragma once
//////////////////////////////////////静态全局变量\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

const int NAME = 15, PASSWORD = 12;


//////////////////////////////////////枚举类型定义\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

typedef enum {//定义剧目枚举类型
	PROGRAM_movie = 1,//电影
	PROGRAM_opera = 2,//歌剧
	PROGRAM_concert = 3//音乐会
}program_types;

typedef enum {//定义账户枚举类型
	USER_admin = 1,
	USER_manager = 2,
	USER_conductor = 3,
	USER_customer = 4,
	USER_unkown = 5,
}user_types;

typedef enum {//定义电影分级枚举类型
	RATING_child = 1,//儿童可观看
	RATING_teens = 2,//青少年可观看
	RATING_adult = 3//成人可观看
}program_ratings;

typedef enum {//定义座位情况枚举类型
	SEAT_none = 0,	//空位
	SEAT_available = 1,//有座位
	SEAT_private=2,//雅座
	SEAT_unrepaired = 9//损坏的座位
}seat_conditions;

typedef enum {
	TICKET_available=0,//代售
	TICKET_sold = 1,//已售
	TICKET_reserve = 2,//预留
}ticket_statuses;

typedef enum {
	SALE_sold=1,//卖票
	SALE_return=2,//退票
}sale_types;

//////////////////////////////////////结构定义\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

typedef struct {
	int year;
	int month;
	int day;
}date_status;//日期结构体

typedef struct {
	int hour;
	int minute;
}time_status;//时间结构体

//////////////////////////////////////实体数据域定义\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

typedef struct em{//剧目数据域
	int program_ID;//  剧目编号
	char program_name[NAME * 2 + 1];//15汉字    剧目名称
	program_types program_type;//剧目类型  参见enum program_types枚举定义
	program_ratings program_rating;//剧目等级 参见program_ratings枚举定义
	char director[NAME * 2 + 1];//15个汉字     导演
	char performer[2][NAME];//7个汉字      主演   两名
	date_status start_date; //上映日期   参见date_status结构体定义
	date_status end_date; //结束日期   参见date_status结构体定义
	int duration;//剧目时长       minute
	char  label[5];//剧目标签   比如  喜剧  动作   惊悚 
	char area[5];//地区   2个汉字
	char language[NAME];//语言
	int price;//票价
	int cost;//放映成本    （万元)
}data_program;

typedef struct emm {
	int studio_ID;//   放映厅编号
	char studio_name[NAME];//七个汉字    放映厅名称
	int seatx;
	int seaty;//放映厅座位 的行和列    固有属性   用来设置二维数组
}data_studio;

typedef struct emmm {//演出计划数据域
	int plan_ID;//演出计划编号
	int play_ID;//剧目编号
	int studio_ID;//放映厅编号
	date_status date; //演出日期   参见date_status结构体定义
	time_status time;//起止时间    参见time_status结构体定义  24小时制
}data_plan;

typedef struct emmmm {//账号数据域
	int UID;//账号编号   用于修改密码或找回密码
	char username[NAME];//用户名   4~14个字符/2~7个汉字
	char password[PASSWORD+1];//登录口令  6~12
	user_types user_type;//账号类型     参见enum user_types枚举定义
	long long contributions;//       业绩\购买额
}data_account;


////////////////////////////////////////实体定义\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


typedef struct linklist_program {//剧目
	data_program element;
	struct linklist_program *pre,*next;
}Program;

typedef struct linklist_studio {//放映厅
	data_studio element;
	struct linklist_studio *pre, *next;
}Studio;

typedef struct linklist_plan {//演出计划
	data_plan element;
	struct linklist_plan *pre, *next;
}Plan;

typedef struct linklist_account {//账号
	data_account element;
	struct linklist_account *pre, *next;
}Account;


typedef struct linklist_seat {
	int seat_ID;//座位编号
	int stduio_ID;//座位所在放映厅编号
	int seatx;//座位所在行
	int seaty;//座位所在列
	seat_conditions seat_condition;//座位状况   参见enum seat_conditions
	struct linklist_seat *pre, *next;
}Seat;

typedef struct linklist_ticket {
	int ticket_ID;//入场券编号
	int plan_ID;//演出计划编号
	int seat_ID;//座位编号
	int price;//票价    剧目决定
	ticket_statuses ticket_status;//票的状况     参见enum tickets_statuses
	struct linklist_ticket *pre, *next;
}Ticket;

typedef struct linklist_record{//销售记录
	long record_ID;//销售记录ID
	int conductor_ID;//售票员ID      会员账户
	int ticket_ID;//票ID
	date_status date;//处理日期
	time_status time;//处理时间
	int price;//票价
	sale_types sale_type;//交易类型
	struct linklist_record *pre, *next;
}Record;

typedef struct ctrl {//链表类型
	Program *program_head,*program_tail;
	Studio *studio_head,*studio_tail;
	Seat *seat_head,*seat_tail;
	Ticket *ticket_head, *ticket_tail;
	Plan *plan_head,*plan_tail;
	Record *record_head, *record_tail;
	Account *account_head,*account_tail;
}List;

////////////////////////////////////////全局变量\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

extern List list;
extern data_account PRESENT;


/////////////////////////////////////////函数\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

int choice_judge();//读取键盘事件  判断选择
void set_position(short x, short y);//设置光标位置
void SetColor(short foreColor, short backColor);//设置字体颜色
void hide_cursor();//隐藏光标
void catch_cursor();//显示光标

//window.cpp

void show_welcome();//欢迎界面
void show_main();//主界面

int screen_clear(int order,int i,int change);/*主界面的高亮控制  i表示当前高亮选项 默认为1
									   参数change表改变量  order表示界面的选择  函数返回当前选项编号*/

void show_sign();//登录界面
void show_bye();//再见界面
void show_customer();//顾客主界面

//welcom.cpp

void print_re();
void print_examinput();//非法输入报错
void go_on();//按任意键继续
void print_mallocX();//malloc报错

//friendly.cpp

void process_all();//程序入口
void process_sign();//登录过程
void process_admin();//管理员过程
void process_manager();//剧院经理过程
void process_conducter();//售票员过程
void process_customer();//顾客过程

void process_accountAppeal();//账号申诉过程
//process.cpp

char *username_get(int judge);//用户名的获取
int sign_judge();//登陆成功及账户类型的判断
char *password_get(int judge);//用户密码的获取

//sonfunction.cpp


void import_account();//读入账号信息
void import_program();//读入剧目信息
void import_studio_and_seat();//读入放映厅及座位信息
//filefunction.cpp

void initialize_linklist();//初始化链表
//Linklist.cpp

void import_all();//导入账户信息
void initialize();//初始化准备
void initialize_present();//初始化当前账户
void initialize_window();//初始化显示窗口

//initialize.cpp