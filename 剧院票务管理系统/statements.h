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
	USER_frozen = 5,//冻结状态
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

////////////////////////////////////////先行定义
typedef struct linklist_seat {
	int stduio_ID;//座位所在放映厅编号
	int seatx;//座位所在行
	int seaty;//座位所在列
	seat_conditions seat_condition;//位置状态   参见enum seat_conditions
	struct linklist_seat *pre, *next;
}Seat;

typedef struct linklist_ticket {
	int ticket_ID;//入场券编号
	//int plan_ID;//演出计划编号
	int seatx;//座位所在行
	int seaty;//座位所在列
	int price;//票价    剧目决定
	ticket_statuses ticket_status;//票的状态     参见enum tickets_statuses
	struct linklist_ticket *pre, *next;
}Ticket;

typedef struct linklist_record{//交易记录
	long record_ID;//交易记录ID
	int conductor_ID;//售票员ID      会员账户
	int plan_ID;//演出计划ID
	int ticket_ID;//票ID
	date_status date;//处理日期
	time_status time;//处理时间
	int price;//票价
	sale_types sale_type;//交易类型
	struct linklist_record *pre, *next;
}Record;

//////////////////////////////////////实体数据域定义\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

typedef struct em{//剧目数据域
	char program_ID[NAME/2];//六位数字  剧目编号
	char program_name[NAME * 2 + 1];//15汉字    剧目名称
	program_types program_type;//剧目类型  参见enum program_types枚举定义
	program_ratings program_rating;//剧目等级 参见program_ratings枚举定义
	char director[NAME];//7个汉字     导演   音乐会为指挥
	char performer[2][NAME];//7个汉字      主演   两名
	date_status start_date; //上映日期   参见date_status结构体定义
	date_status end_date; //结束日期   参见date_status结构体定义
	int duration;//剧目时长       minute   [1,600]
	char  label[5];//剧目标签   比如  喜剧  动作   惊悚 
	char area[5];//地区   2个汉字
	char language[NAME];//语言
	int price;//票价   [5,100]
	int cost;//放映成本    （万元)
}data_program;

typedef struct emm {
	char studio_ID[NAME/2];//最多六位数字   放映厅编号
	char studio_name[NAME];//最多七个汉字    放映厅名称
	int seatx;//5~12
	int seaty;//10~25  放映厅座位 的行和列    固有属性   用来设置二维数组
	Seat *seat_head, *seat_tail;//次链表
}data_studio;

typedef struct emmm {//演出计划数据域
	int plan_ID;//演出计划编号
	int play_ID;//剧目编号
	int studio_ID;//放映厅编号
	date_status date; //演出日期   参见date_status结构体定义
	time_status time;//开始时间    参见time_status结构体定义  24小时制
	Ticket *ticket_head, *ticket_tail;//次链表
}data_plan;

typedef struct emmmm {//账号数据域
	char UID[NAME-2];//账号编号   12位   用于修改密码或找回密码
	char username[NAME];//用户名   4~14个字符/2~7个汉字
	char password[PASSWORD+1];//登录口令  6~12
	user_types user_type;//账号类型     参见enum user_types枚举定义
	long long contributions;//       业绩\购买额
	Record *record_head, *record_tail;//销售记录、购买记录次链表
}data_account;

/////读取销售记录时计算业绩      新增销售记录时实时更新     销售排名时不再重新计算
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



typedef struct ctrl {//链表类型
	Program *program_head,*program_tail;
	Studio *studio_head,*studio_tail;
	Plan *plan_head,*plan_tail;
	Account *account_head,*account_tail;
}List;

////////////////////////////////////////全局变量\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

extern List list;
extern data_account PRESENT;


/////////////////////////////////////////函数\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

int choice_judge(int i);//读取键盘事件  判断选择
void set_position(short x, short y);//设置光标位置
void set_position(COORD position);//设置光标位置
void SetColor(short foreColor, short backColor);//设置字体颜色
void hide_cursor();//隐藏光标
void catch_cursor();//显示光标
POINT get_position();//得到当前光标y坐标
int screen_clear(int order, int i, int change);/*主界面的高亮控制  i表示当前高亮选项 默认为1
										参数change表改变量  order表示界面的选择  函数返回当前选项编号*/
int turn_page();//翻页器
int select_seat(Studio *p);//判别位置  ↑ -1   ← -2   ↓ 1    → 2    ESC 0   回车3  
void clear_seat(COORD position, char status);//改变座位显示  COORD  当前位置   status 座位状态

//window.cpp

void show_welcome();//欢迎界面
void show_main();//主界面
void show_sign();//登录界面
void show_bye();//再见界面
void show_customer();//顾客主界面
void show_manager();//剧院经理主界面
void show_program();//剧目查询及管理界面
void show_studio();//影厅查询及管理界面

void show_admin();//系统管理员主界面
void show_account();//账户管理界面
//welcom.cpp

void print_re();
void print_examinput();//非法输入报错
void go_on();//按任意键继续
void exam_mallocX(void *p);//malloc报错
int enquiry(int i);//判断是否进行本次操作   i==1   enquiry   i==2 warnning
void print_ok(); //提示操作成功
void print_instruction(int i);//显示操作说明
//friendly.cpp

void process_all();//程序入口
void process_sign();//登录过程
void process_admin();//管理员过程
void process_acount();//账户管理过程

void process_manager();//剧院经理过程
void process_program();//剧目查询及管理过程
void process_studio();//影厅查询及管理过程
void process_plan();//放映计划查询及管理过程

void process_conducter();//售票员过程
void process_customer();//顾客过程

void account_appeal();//账号申诉过程
//process.cpp

char *username_get(int judge);//用户名的获取
int sign_judge();//登陆成功及账户类型的判断
char *password_get(int judge);//用户密码的获取
char *get_string(int down, int up,int judge);//字符串检查函数    down~up   字符串字节数限制
int get_num(int down, int up, int ndown, int nup);//读取数字    并检查输入   范围[down,up]   位数n[ndown,nup]
date_status get_date();//日期的获取及判断
time_status get_time();//时间的获取及判断
data_program get_program_infomation();//获取剧目主要信息  并进行初始化
void program_viewer();//剧目浏览器
void studio_viewer();//放映厅查看器
void seat_changer(Studio *p);//可视化座位修改器

//sonfunction.cpp


void import_account();//读入账号信息
void import_program();//读入剧目信息
void import_studio_and_seat();//读入放映厅及座位信息


void save_program();//保存剧目信息到文件
void save_studio_and_seat();//保存放映厅及座位到文件
//filefunction.cpp

void initialize_linklist();//初始化链表

Program *search_program(char *obj, int judge);//按ID或名称查找剧目 judge 控制是否进行相似反馈
void add_program();//增加剧目
void kill_program(Program *p);//按照ID或名字删除剧目
void print_program(Program *p , int i);////输出某个影片信息
void modify_program(Program *p);//修改影片信息

Studio *search_studio(char *obj, int judge);//按ID或名称查找放映厅    judge 控制是否进行相似反馈
void add_studio();//增加放映厅
void print_studio(Studio *p);////打印放映厅及座位信息

//Seat *search_seat(char *obj);//根据放映厅编号查找座位
void delete_seat(Studio *k);//删除放映厅时删除其座位
void kill_studio(Studio *p);//删除指定放映厅
void modify_studio(Studio *p);//修改放映厅名称及座位

void initialize_seat(Studio *p);//为新放映厅初始化座位

//Linklist.cpp

void import_all();//导入账户信息
void initialize();//初始化准备
void initialize_present();//初始化当前账户
void initialize_window();//初始化显示窗口

//initialize.cpp