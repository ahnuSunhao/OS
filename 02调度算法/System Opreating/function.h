typedef struct jc
{
	char name;//进程名 
	int arriveTime;//到达时间 
	int startTime;//开始时间 
	int serveTime;//服务时间 
	int waitTime;//等待时间 
	int endTime;//结束时间 
	int zhouzhuanTime;//周转时间
	double weightTime;//带权周转时间 
	int startFlag;//开始标志 
	double reflectRate;//响应比
}jc;

struct zgxyb{
	char name[10]; //作业名称
	float arrivetime;//到达时间
	float servicetime;//服务时间
	float starttime;//开始时间
	float finishtime;//完成时间
	float zztime;//周转时间
	float dqzztime;//平均周转时间
}; 

int readDate(jc x[]);//读取date.TXT文件中的数据 ,返回进程个数 

void showDate(jc x[], int n);//显示各进程相关数据 

void TimePian(jc x[] , int n);//时间片轮转算法 

int input(struct zgxyb *p);

void Print(struct zgxyb *p,float arrivetime,float servicetime,float starttime,float finishtime,float zztime,float dqzztime,int N);

void sort( struct zgxyb *p,int N);
 
void deal(struct zgxyb *p,float arrivetime,float servicetime,float starttime,float finishtime,float zztime,float dqzztime,int N);
 
void HHRN (struct zgxyb *p,int N);//高响应比优先调度算法 

