#include "function.h"
#include "head.h"

int readDate(jc x[])
{
	int i, n; 
	FILE *fp =fopen("date.txt","r");
	if(fp == NULL)
		return 0;
	fscanf(fp,"%d",&n);
	for(i=0;i<n;i++)
	{
		fscanf(fp,"%d %c %d", &x[i].arriveTime,&x[i].name, &x[i].serveTime);
		x[i].startFlag = 0;
		x[i].endTime = 0;
	}
	fclose(fp);
	return n;
}

void showDate(jc x[],int n)
{
	int i;
	printf("进程的个数为：%d\n",n);
	for(i=0;i<n;i++)
	{
		printf("%c进程到达时间%d，服务时间%d\n",x[i].name, x[i].arriveTime, x[i].serveTime);
	}
} 

void TimePian(jc x[] , int n)
{
	int  length, i = 0, j, t = 0, flag = 0;
	int y[MAXN];
	for(j=0;j<n;j++)
	{
		y[j] = x[j].serveTime;
	}
	
	printf("请输入时间片长度：");
	scanf("%d",&length);
	
	printf("\n进程名  到达时间  开始时间  等待时间  还需服务时间\n");

	
	while(1)
	{
		if(x[i].endTime == 0)
		{
			if(x[i].startFlag == 0)//表示第一次执行该进程 
			{
				
				for(j=0;j<length;j++)
				{
					if(x[i].startFlag == 0) 
					{
						if(t>=x[i].arriveTime)
						{
							x[i].startTime = t;
							x[i].waitTime = t - x[i].arriveTime;
							x[i].serveTime -= 1;
							t ++;
						}
						else{//保证到达时间不是按顺序到达的 
							t++;
							break;
						}
						if(x[i].serveTime == 0)
						{//该进程结束 
							x[i].endTime = t;
							flag ++;
							break;
						}
					}
					else
					{
						x[i].serveTime -=  1;
						t ++;
						if(x[i].serveTime == 0)
						{//该进程结束 
							x[i].endTime = t;
							flag ++;
							break;
						}
					}
					x[i].startFlag = 1;
				}
			}
			else//不是第一次执行 
			{
				for(j=0;j<length;j++)
				{
					x[i].serveTime -=  1;
					t ++;
					if(x[i].serveTime == 0)
					{//该进程结束 
						x[i].endTime = t;
						flag ++;
						break;
					}
				}
			}
		}
		
		printf("%c\t  %d\t    %d\t     %d\t     \t%d\n",x[i].name, x[i].arriveTime, x[i].startTime, x[i].waitTime, x[i].serveTime);

		
		if(flag == n)
			break;
		i++;
		if(i==n)
		{
			i = 0;
			printf("-----------------------------------------\n");
		}
			
	}
	printf("\n进程名  到达时间  开始时间  等待时间  结束时间  周转时间  带权周转时间\n");

	for(i=0;i<n;i++)
	{
		x[i].zhouzhuanTime = x[i].endTime - x[i].arriveTime;
		x[i].weightTime = (double)x[i].zhouzhuanTime / (double)y[i];
		printf("%c\t    %d\t      %d\t\t%d\t %-2d\t   %d\t    %.2f\n",x[i].name, x[i].arriveTime, x[i].startTime, x[i].waitTime, x[i].endTime, x[i].zhouzhuanTime, x[i].weightTime);
	}	
}

//文件读入数据
int input(struct zgxyb *p)
{
	int i,n;
	//文件输入
	FILE *fpRead=fopen("date.txt","r");  
    if(fpRead==NULL)  //文件为空
    {  
        return ;  
    }  
	printf("从文件中读取信息：作业名称-到达时间-服务时间：\n");
	fscanf(fpRead,"%d",&n);
	for(i=0;i<n;i++)
	{
		//读取数据
		fscanf(fpRead," %f %s %f",&p[i].arrivetime,&p[i].name,&p[i].servicetime);
	}
	 fclose(fpRead);//关闭文件夹
	 return n;
}

void Print(struct zgxyb *p,float arrivetime,float servicetime,float starttime,float finishtime,float zztime,float dqzztime,int N)
{
	int k; 
	printf("作业完成先后顺序为：");
	printf("%s",p[0].name);
	for(k=1;k<N;k++) 
	{
		printf("-->%s",p[k].name);
	}
	
	printf("\n作业名称 到达时间 服务时间 开始时间  完成时间    周转时间     带权周转时间\n");
	for(k=0;k<=N-1;k++) {
		printf("%s\t   %-.2f\t   %-.2f\t     %-.2f\t%-.2f\t    %-.2f\t  %-.2f\t\n",p[k].name,p[k].arrivetime,p[k].servicetime,p[k].starttime,p[k].finishtime,p[k].zztime,p[k].dqzztime);
	}
}



//按到达时间排序
 void sort( struct zgxyb *p,int N){ 
	 int i,j; 
	 for(i=0;i<=N-1;i++)
		 for(j=0;j<=i;j++)
			 if(p[i].arrivetime<p[j].arrivetime)
			 { 
				 struct zgxyb temp;
				 temp=p[i];p[i]=p[j];
				 p[j]=temp;
			} 
 }

//运行阶段

 void deal(struct zgxyb *p,float arrivetime,float servicetime,float starttime,float finishtime,float zztime,float dqzztime,int N)
 { 
	 int k; 
	 for(k=0;k<=N-1;k++)
	 { 
		 if(k==0){ 
			 p[k].starttime=p[k].arrivetime;
			 p[k].finishtime=p[k].arrivetime+p[k].servicetime;
			}
		 else{
			 p[k].starttime=p[k-1].finishtime; p[k].finishtime=p[k-1].finishtime+p[k].servicetime;
			}
	 } 
	 //计算周转时间:完成时间减去开始时间
	 for(k=0;k<=N-1;k++)
	 { 
		 p[k].zztime=p[k].finishtime-p[k].arrivetime;
		 p[k].dqzztime=p[k].zztime/p[k].servicetime;
	 }
 }

void HHRN (struct zgxyb *p,int N){
	float arrivetime=0,servicetime=0,starttime=0,finishtime=0,zztime=0,dqzztime=0;
	int m,i,n,follow,k;
	float max; 
	float sum=0,sum1=0;//计算整体带权周转时间
	struct zgxyb temp;
	sort(p,N); 
	for(m=0;m<N-1;m++)
	{ 
		//特殊情况
		if(m==0) 
			p[m].finishtime=p[m].arrivetime+p[m].servicetime;
		else
			p[m].finishtime=p[m-1].finishtime+p[m].servicetime; 

		i=0; 
		
		//判断除了当前作业，还有多少作业在当前时间已经到达
		for(n=m+1;n<=N-1;n++)
		{ 
			if(p[n].arrivetime<=p[m].finishtime)
				i++;
		} 
		max=(p[m].finishtime-p[m+1].arrivetime+p[m+1].servicetime)/p[m+1].servicetime;

		follow=m+1; 


		for(k=m+1;k<m+i;k++)
		//从第二个开始排序
		{ 
			if(max<=(p[m].finishtime-p[k+1].arrivetime+p[k+1].servicetime)/p[k+1].servicetime) //判断优先级是否超过初值
			{ 
				max=(p[m].finishtime-p[k+1].arrivetime+p[k+1].servicetime)/p[k+1].servicetime;
				follow=k+1;//原因：从第二个开始比较
			}
		} 

		temp=p[m+1];
		p[m+1]=p[follow];
		p[follow]=temp;
	}
	deal(p,arrivetime,servicetime,starttime,finishtime,zztime,dqzztime,N);
	Print(p,arrivetime,servicetime,starttime,finishtime,zztime,dqzztime,N);//输出最终结果
	for(i=0;i<N;i++)
	{
		sum+=p[i].zztime;
		sum1+=p[i].servicetime;
	}
	printf("整体的平均带权周转时间为：%-.2f\n",sum/sum1);
}

