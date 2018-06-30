#include "head.h"
#include "func.h"

void menu()
{
	printf("**************************************************************\n");
	printf("1.�жϵ�ǰ�Ƿ�ȫ\n");
	printf("2.�������󣨸�ʽ��x a b c)\n");
	printf("   x�����֣���ʾ�ڼ������̣�a b c��ʾ�ֱ��A B C������Դ������\n");
	printf("3.������1������2�˳�����\n");
	printf("**************************************************************\n"); 
}

void readData(pro p[] , int available[])
{
	int i , j;
	FILE *fp = fopen("data.txt","r");
	if(fp == NULL)
		return ;
	fscanf(fp,"%d",&n);//������ 
	fscanf(fp,"%d",&m);//ÿ���������ж�������Դ 
	//��max���� 
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			fscanf(fp,"%d",&p[i].max[j]);
		
	//��allocation���� 
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			fscanf(fp,"%d",&p[i].allocation[j]);
			
	//��need���� 
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			fscanf(fp,"%d",&p[i].need[j]);
					
		}
		p[i].flag = 0;	
	}

	//��available���� 
	for(i = 0;i<m;i++)
		fscanf(fp,"%d",&available[i]);
	fclose(fp);
}

void isSafe(pro p[] , int available[])
{
	int i=0, j, t = 0, s = 0, r = -1;//t��Ǵ�ʱ�ж��ٸ����̱����� ,s��ʾ�˽��̲��ܱ����� 
	printf("����\t  work \t      need \t allocation \t work+allocatioin \t finish\n");
	while(1)
	{
		if(p[i].flag!=1) 
		{//������ʱ��i�����̻�û�б����� 
			if(compare(p[i].need,available) == 1)
			{
				print(i,p,available);
				p[i].flag = 1;//��ʾ�˽����Ѿ������㣬�����β��� 
				t++; 
			}
			else
			{//��ʾ������Դ��С��������Դ�� 
				s++;
			} 
		}
		
		if(t==n)
		{
			printf("�ǰ�ȫ״̬\n");
			return;
		}
		i++;
		if(i==n)
		{
			if(r == t)
			{//��ʾ�����н����ٴα�������Ȼû�н��̿��Ա����㣬����״̬����ȫ 
				printf("���ǰ�ȫ״̬\n");
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
{//����1��ʾ����a�ж�Ӧ����Դ������b�ж�Ӧ�ĵ���Դ��С 
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
	printf("���������ݣ�");
	scanf("%d ",&i);
	for(j=0;j<m;j++)
	{
		scanf("%d",&input[j]);
	}
	//���ж���������ݶ��ڴ˽����Ƿ�Ϸ�
	for(j = 0;j<m;j++)
	{
		if(input[j]>available[j] ||input[j]>p[i-1].need[j])
		{//������Դ������������Դ��,����������Դ��������Ҫ����Դ�������ǲ��Ϸ��ģ� 
			printf("���󲻺Ϸ�����������\n");
			return; 
		}
		available[j] = available[j] - input[j];
		p[i-1].need[j] -= input[j];
		p[i-1].allocation[j] += input[j];
	}
	isSafe(p,available);
} 


