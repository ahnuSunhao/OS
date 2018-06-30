#include "head.h"
#include "func.h"

void menu()
{
	printf("**************************************************************\n");
	printf("1.判断当前是否安全\n");
	printf("2.输入请求（格式：x a b c)\n");
	printf("   x是数字，表示第几个进程，a b c表示分别对A B C三类资源的请求\n");
	printf("3.非数字1或数字2退出程序\n");
	printf("**************************************************************\n"); 
}

void readData(pro p[] , int available[])
{
	int i , j;
	FILE *fp = fopen("data.txt","r");
	if(fp == NULL)
		return ;
	fscanf(fp,"%d",&n);//进程数 
	fscanf(fp,"%d",&m);//每个进程中有多少种资源 
	//读max矩阵 
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			fscanf(fp,"%d",&p[i].max[j]);
		
	//读allocation矩阵 
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			fscanf(fp,"%d",&p[i].allocation[j]);
			
	//读need矩阵 
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			fscanf(fp,"%d",&p[i].need[j]);
					
		}
		p[i].flag = 0;	
	}

	//读available矩阵 
	for(i = 0;i<m;i++)
		fscanf(fp,"%d",&available[i]);
	fclose(fp);
}

void isSafe(pro p[] , int available[])
{
	int i=0, j, t = 0, s = 0, r = -1;//t标记此时有多少个进程被满足 ,s表示此进程不能被满足 
	printf("进程\t  work \t      need \t allocation \t work+allocatioin \t finish\n");
	while(1)
	{
		if(p[i].flag!=1) 
		{//表明此时第i个进程还没有被满足 
			if(compare(p[i].need,available) == 1)
			{
				print(i,p,available);
				p[i].flag = 1;//表示此进程已经被满足，避免多次操作 
				t++; 
			}
			else
			{//表示请求资源数小于现有资源数 
				s++;
			} 
		}
		
		if(t==n)
		{
			printf("是安全状态\n");
			return;
		}
		i++;
		if(i==n)
		{
			if(r == t)
			{//表示把所有进程再次遍历，仍然没有进程可以被满足，即此状态不安全 
				printf("不是安全状态\n");
				return ;
			}
			r = t;
			i = 0;
			s = 0;
		}
	}
} 

void print(int i , pro p[] , int available[])
{
	int j;
	printf("%d\t  ",i+1);
	for(j = 0;j<m;j++)
		printf("%-2d ",available[j]);
	printf("|   ");
	
	for(j = 0;j<m;j++)
		printf("%-2d ",p[i].need[j]);
	printf("|   ");
		
	for(j = 0;j<m;j++)
		printf("%-2d ",p[i].allocation[j]);
	printf("|       ");
	
	for(j = 0;j<m;j++)
	{
		available[j] += p[i].allocation[j];
		printf("%-2d ",available[j]);
	}
	printf(" | \t  true \n");	

}

int compare(int a[] , int b[])
{//返回1表示数组a中对应的资源数都比b中对应的的资源数小 
	int i;
	for(i=0;i<m;i++)
	{
		if(a[i]>b[i])
		{
			return 0;
		}
	}
	return 1;
}

void judgeSafe(pro p[] , int available[])
{
	int i, input[M], j; 
	readData(p,available);
	printf("请输入数据：");
	scanf("%d ",&i);
	for(j=0;j<m;j++)
	{
		scanf("%d",&input[j]);
	}
	//先判断输入的数据对于此进程是否合法
	for(j = 0;j<m;j++)
	{
		if(input[j]>available[j] ||input[j]>p[i-1].need[j])
		{//请求资源数大于现有资源数,或者请求资源数大于需要的资源数，均是不合法的， 
			printf("请求不合法，不能满足\n");
			return; 
		}
		available[j] = available[j] - input[j];
		p[i-1].need[j] -= input[j];
		p[i-1].allocation[j] += input[j];
	}
	isSafe(p,available);
} 


