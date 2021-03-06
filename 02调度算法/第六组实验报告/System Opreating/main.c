#include "head.h"
#include "function.h"

typedef struct node   /*进程节点信息*/  
{  
	char name[20];   /*进程的名字*/  
	int prio;    /*进程的优先级*/  
	int round;    /*分配CPU的时间片*/  
	int cputime;   /*CPU执行时间*/  
	int needtime;   /*进程执行所需要的时间*/  
	char state;    /*进程的状态，W——就绪态，R——执行态，F——完成态*/  
	int count;    /*记录执行的次数*/  
	struct node *next;  /*链表指针*/  
}PCB;  
typedef struct Queue  /*多级就绪队列节点信息*/  
{  
	PCB *LinkPCB;   /*就绪队列中的进程队列指针*/  
	int prio;    /*本就绪队列的优先级*/  
	int round;    /*本就绪队列所分配的时间片*/  
	struct Queue *next;  /*指向下一个就绪队列的链表指针*/  
}ReadyQueue;  

PCB *run=NULL,*finish=NULL; /*定义三个队列，就绪队列，执行队列和完成队列*/  
ReadyQueue *Head = NULL; /*定义第一个就绪队列*/   
void Output();          /*进程信息输出函数*/  
void InsertFinish(PCB *in);       /*将进程插入到完成队列尾部*/  
void InsertPrio(ReadyQueue *in);     /*创建就绪队列，规定优先数越小，优先级越低*/  
void PrioCreate();         /*创建就绪队列输入函数*/  
void GetFirst(ReadyQueue *queue);     /*取得某一个就绪队列中的队头进程*/  
void InsertLast(PCB *in,ReadyQueue *queue);   /*将进程插入到就绪队列尾部*/  
void ProcessCreate();        /*进程创建函数*/  
void RoundRun(ReadyQueue *timechip);    /*时间片轮转调度算法*/  
void MultiDispatch();        /*多级调度算法，每次执行一个时间片*/  

void Output()  /*进程信息输出函数*/  
{  
	ReadyQueue *print = Head;  
	PCB *p;  
	printf("进程名\t优先级\t轮数\tcpu时间\t需要时间\t进程状态\t计数器\n");  
	while(print)  
	{  
		if(print ->LinkPCB != NULL)  
		{  
	    	p=print ->LinkPCB;  
	   		while(p)  
	   		{  
	    		printf("%s\t%d\t%d\t%d\t%d\t\t%c\t\t%d\n",p->name,p->prio,p->round,p->cputime,p->needtime,p->state,p->count);     
	    		p = p->next;  
	   		}  
	  	}  
	  	print = print->next;  
	}  
	p = finish;  
	while(p!=NULL)  
	{  
		printf("%s\t%d\t%d\t%d\t%d\t\t%c\t\t%d\n",p->name,p->prio,p->round,p->cputime,p->needtime,p->state,p->count);  
	    p = p->next;  
	}  
	p = run;  
	while(p!=NULL)  
	{  
	    printf("%s\t%d\t%d\t%d\t%d\t\t%c\t\t%d\n",p->name,p->prio,p->round,p->cputime,p->needtime,p->state,p->count);  
	    p = p->next;  
	}  
}  

void InsertFinish(PCB *in)  /*将进程插入到完成队列尾部*/  
{  
	PCB *fst;  
	fst = finish;  
	
	if(finish == NULL)  
	{  
		in->next = finish;  
	    finish = in;  
	}  
	else  
	{  
	    while(fst->next != NULL)  
	  	{  
	   		fst = fst->next;  
	  	}  
	  	in ->next = fst ->next;  
	  	fst ->next = in;  
	}  
}  

void InsertPrio(ReadyQueue *in)  /*创建就绪队列，规定优先数越小，优先级越低*/  
{  
	ReadyQueue *fst,*nxt;  
	fst = nxt = Head;  
	
	if(Head == NULL)    /*如果没有队列，则为第一个元素*/  
	{  
		in->next = Head;  
	    Head = in;  
	}  
	else       /*查到合适的位置进行插入*/  
	{  
	  	if(in ->prio >= fst ->prio)  /*比第一个还要大，则插入到队头*/  
	  	{  
	   		in->next = Head;  
	   		Head = in;  
	  	}	  
	  	else  
	  	{  
	   		while(fst->next != NULL)  /*移动指针查找第一个别它小的元素的位置进行插入*/  
	   		{  
	    		nxt = fst;  
	    		fst = fst->next;  
	   		}	  
	
	   		if(fst ->next == NULL)  /*已经搜索到队尾，则其优先级数最小，将其插入到队尾即可*/  
	   		{  
	    		in ->next = fst ->next;  
	    		fst ->next = in;  
	   		}	  
	   		else     /*插入到队列中*/  
	   		{  
	    		nxt = in;  
	    		in ->next = fst;  
	   		}  
	  }  
	}  
}  

void PrioCreate() /*创建就绪队列输入函数*/  
{  
	ReadyQueue *tmp;  
	int i,ReadyNum;  
	
	//文件输入
	FILE *fpRead=fopen("date1.txt","r");  
    if(fpRead==NULL)  //文件为空
    {  
        return ;  
    }
	fscanf(fpRead,"%d",&ReadyNum);
	 fclose(fpRead);//关闭文件夹
	
	printf("输入第一个就绪队列的CPU时间片：\n");
	if((tmp = (ReadyQueue *)malloc(sizeof(ReadyQueue)))==NULL)  
  	{  
  		perror("malloc");  
   		exit(1);  
  	}
  	scanf("%d",&(tmp->round));
  	tmp ->prio = 50 - tmp->round;  /*设置其优先级，时间片越高，其优先级越低*/  
  	tmp ->LinkPCB = NULL;    /*初始化其连接的进程队列为空*/  
  	tmp ->next = NULL;  
  	InsertPrio(tmp);     /*按照优先级从高到低，建立多个就绪队列*/  
	
	for(i = 1;i < ReadyNum; i++)  
	{  
  		if((tmp = (ReadyQueue *)malloc(sizeof(ReadyQueue)))==NULL)  
  		{  
  			perror("malloc");  
   			exit(1);  
  		}	  
  		tmp->round += tmp->round;//每一个时间片是上一个时间片的二倍 
  		tmp ->prio = 50 - tmp->round;  /*设置其优先级，时间片越高，其优先级越低*/  
  		tmp ->LinkPCB = NULL;    /*初始化其连接的进程队列为空*/  
  		tmp ->next = NULL;  
  		InsertPrio(tmp);     /*按照优先级从高到低，建立多个就绪队列*/  
	}  
}  

void GetFirst(ReadyQueue *queue)     /*取得某一个就绪队列中的队头进程*/  
{  
	run = queue ->LinkPCB;  
	if(queue ->LinkPCB != NULL)  
	{  
		run ->state = 'R';  
  		queue ->LinkPCB = queue ->LinkPCB ->next;  
  		run ->next = NULL;  
	}  
}  

void InsertLast(PCB *in,ReadyQueue *queue)  /*将进程插入到就绪队列尾部*/  
{  
	PCB *fst;  
	fst = queue->LinkPCB;  

	if( queue->LinkPCB == NULL)  
	{  
		in->next =  queue->LinkPCB;  
		queue->LinkPCB = in;  
	}  
	else  
	{  
		while(fst->next != NULL)  
  		{  
  			fst = fst->next;  
  		}  
  		in ->next = fst ->next;  
  		fst ->next = in;  
	}  
}  

void ProcessCreate() /*进程创建函数*/  
{  
	PCB *tmp;  
	int i,num;  
	//文件输入
	FILE *fpRead=fopen("date1.txt","r");  
    if(fpRead==NULL)  //文件为空
    {  
        return ;  
    }  
	fscanf(fpRead,"%d",&num);
	for(i=0;i<num;i++)
	{
		if((tmp = (PCB *)malloc(sizeof(PCB)))==NULL)  
		{  
   			perror("malloc");  
   			exit(1);  
	  	}  
		//读取数据
		fscanf(fpRead,"%s %d",tmp->name,&(tmp->needtime));
		tmp ->cputime = 0;  
	  	tmp ->state ='W';  
	  	tmp ->prio = 50 - tmp->needtime;  /*设置其优先级，需要的时间越多，优先级越低*/  
	  	tmp ->round = Head ->round;  
	  	tmp ->count = 0;  
	  	InsertLast(tmp,Head);      /*按照优先级从高到低，插入到就绪队列*/  
	}
	fclose(fpRead);//关闭文件夹 
}  

void RoundRun(ReadyQueue *timechip)    /*时间片轮转调度算法*/  
{  
	int flag = 1;  

	GetFirst(timechip);  
	while(run != NULL)  
	{  
  		while(flag)  
  		{  
   			run->count++;  
   			run->cputime++;  
   			run->needtime--;  
   			if(run->needtime == 0) /*进程执行完毕*/  
   			{  
    			run ->state = 'F';  
    			InsertFinish(run);  
    			flag = 0;  
   			}	  
   			else if(run->count == timechip ->round)/*时间片用完*/  
   			{  
			    run->state = 'W';  
			    run->count = 0;   /*计数器清零，为下次做准备*/  
			    InsertLast(run,timechip);  
				flag = 0;  
			}  
  		}  
  		flag = 1;  
  		GetFirst(timechip);  
	}  
}  

void MultiDispatch()   /*多级调度算法，每次执行一个时间片*/  
{  
	int flag = 1;  
	int k = 0;  
	
	ReadyQueue *point;  
 
	PrioCreate(); /*创建就绪队列*/  
	ProcessCreate();/*创建就绪进程队列*/  
	point = Head; 
	GetFirst(point);  
	while(run != NULL)  
	{  
  		Output();  
  		if(Head ->LinkPCB!=NULL)  
   			point = Head;  
  		while(flag)  
  		{  
   			run->count++;  
   			run->cputime++;  
   			run->needtime--;  
   			if(run->needtime == 0) /*进程执行完毕*/  
   			{  
    			run ->state = 'F';  
    			InsertFinish(run);  
    			flag = 0;  
   			}  
   			else if(run->count == run->round)/*时间片用完*/  
   			{  
    			run->state = 'W';  
    			run->count = 0;   /*计数器清零，为下次做准备*/  
	    		if(point ->next!=NULL)  
	    		{  
	     			run ->round = point->next ->round;/*设置其时间片是下一个就绪队列的时间片*/  
	     			InsertLast(run,point->next);  /*将进程插入到下一个就绪队列中*/  
	     			flag = 0;  
	    		}  
	    		else  
	    		{  
	    	 		RoundRun(point);   /*如果为最后一个就绪队列就调用时间片轮转算法*/  
	     			break;  
	    		}  
   			}  
   			++k;  
   			if(k == 3)  
   			{  
    			ProcessCreate();  
   			}  
  		}  
  		flag = 1;  
  		if(point ->LinkPCB == NULL)/*就绪队列指针下移*/  
   			point =point->next;  
  		if(point ->next ==NULL)  
  		{	  
   			RoundRun(point);  
   			break;  
  		}  
  		GetFirst(point);  
	} 
	Output();  /*输出最终的调度序列*/  
}  


int main()
{
	int n1,length;
	jc x[MAXN];
	struct zgxyb a[100]; //作业容器
	
	struct zgxyb *c;
	printf("*************************************\n");
	printf("**  1，进程初始化                  **\n");
	printf("**  2，显示初始化后进程的基本信息  **\n");
	printf("**  3，时间片轮转调度算法          **\n");
	printf("**  4，多级反馈队列调度算法        **\n");
	printf("**  5，高响应比优先调度算法        **\n");
	printf("**       别的数字退出程序          **\n");
	printf("*************************************\n");
	
	while(1){
		printf("请选择功能，输入数字："); 
		scanf("%d",&n1);
		switch(n1){
			case 1:
			{
				length = readDate(x);//读取文件数据 
				printf("\n");
				break;
			}
			case 2:
			{
				length = readDate(x);//读取文件数据 
				showDate(x,length);
				printf("\n");
				break;
			}
			case 3:
			{
				length = readDate(x);
				TimePian(x,length); 
				printf("\n");
				break;
			}
			case 4:
			{
				MultiDispatch(); 
				printf("\n");
				break;	
			}
			
			case 5:
			{
				length = input(a);
				c=a;	
				HHRN(c,length); 
				printf("\n");
				break;
			}
			default: 
			{
				return 0;
			}
		}
	} 

	return 0;
}
